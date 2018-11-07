/*
 * 
 * Copyright (c) 2003, Michael Carruth All rights reserved.
 * This file is a part of CrashRpt library.
 *
 * Copyright 2010 JiJie Shi
 *
 * This file is part of data_scrambler.
 * 

 * Redistributions in source code form must reproduce the above copyright notice, 
 * the following disclaimer in the documentation and/or other materials provided with the distribution.

 * data_scrambler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * data_scrambler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with data_scrambler.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef TEST_DATA_SENDER
#include "data_center_pch.h"
#else
#include "stdafx.h"
#endif //TEST_DATA_SENDER
#include "data_sender.h"
#include <map>
#include "Utility.h"
#include "md5_ex.h"
#include "zip.h"
#include "strconv.h"
#include "base64.h"
#include "HttpRequestSender.h"
#include "AssyncNotification.h"
#include "smtpclient.h"
#include "MailMsg.h"
#include "data_sender_common.h"

#pragma comment( lib, "Dbghelp.lib" )
#pragma comment( lib, "Version.lib" )
#pragma comment( lib, "Rpcrt4.lib" )
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "zlib.lib" )
#pragma comment( lib, "Dnsapi.lib" )
#pragma comment( lib, "minizip.lib" )
#pragma comment( lib, "Wininet.lib" )
#pragma comment( lib, "Psapi.lib" )

using namespace std; 

#define MAX_DATA_FILE_SIZE ( LONG64 )( 1024 * 1024 ) 

LONG64 WINAPI get_uncompressed_data_size(DataInfo& data_info)
{
	LONG64 lTotalSize = 0;
	std::vector<CString>::iterator it;
	HANDLE hFile = INVALID_HANDLE_VALUE;  
	CString sMsg;
	BOOL bGetSize = FALSE;
	LARGE_INTEGER lFileSize;

	for(it=data_info.m_FileItems.begin(); it!=data_info.m_FileItems.end(); it++)
	{   
		CString sFileName = it->GetBuffer(0); 
		hFile = CreateFile(sFileName, 
			GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
		if(hFile==INVALID_HANDLE_VALUE)
			continue;

		bGetSize = GetFileSizeEx(hFile, &lFileSize);
		if(!bGetSize)
		{
			CloseHandle(hFile);
			continue;
		}

		lTotalSize += lFileSize.QuadPart;
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}

	return lTotalSize;
}

// This method calculates an MD5 hash for the file
int calc_file_md5_hash(CString sFileName, CString& sMD5Hash)
{
	FILE* f = NULL;
	BYTE buff[512];
	MD5 md5;
	MD5_CTX md5_ctx;
	unsigned char md5_hash[16];
	int i;

	sMD5Hash.Empty();

#if _MSC_VER<1400
	f = _tfopen(sFileName.GetBuffer(0), _T("rb"));
#else
	_tfopen_s(&f, sFileName.GetBuffer(0), _T("rb"));
#endif

	if(f==NULL) 
		return -1;

	md5.MD5Init(&md5_ctx);

	while(!feof(f))
	{
		size_t count = fread(buff, 1, 512, f);
		if(count>0)
		{
			md5.MD5Update(&md5_ctx, buff, (unsigned int)count);
		}
	}

	fclose(f);
	md5.MD5Final(md5_hash, &md5_ctx);

	for(i=0; i<16; i++)
	{
		CString number;
		number.Format(_T("%02x"), md5_hash[i]);
		sMD5Hash += number;
	}

	return 0;
}

// This method compresses the files contained in the report and produces ZIP archive.
BOOL compress_data_files( DataInfo& data_info, LONG64 max_size )
{ 
	BOOL bStatus = FALSE;
	strconv_t strconv;
	zipFile hZip = NULL;
	CString sMsg;
	CString zip_file_Name; 
	LONG64 lTotalSize = 0;
	LONG64 lTotalCompressed = 0;
	BYTE buff[1024];
	DWORD dwBytesRead=0;
	HANDLE hFile = INVALID_HANDLE_VALUE;  
	std::vector<CString>::iterator it;
	FILE* f = NULL;
	CString sMD5Hash;

	lTotalSize = get_uncompressed_data_size(data_info);
	if( lTotalSize > max_size )
	{
		goto cleanup; 
	}

	zip_file_Name = data_info.m_sZipName; // + _T(".zip");  

	sMsg.Format(_T("Creating ZIP archive file %s"), zip_file_Name);

	hZip = zipOpen((const char*)zip_file_Name.GetBuffer(0), APPEND_STATUS_CREATE);
	if(hZip==NULL)
	{
		goto cleanup;
	}

	for(it=data_info.m_FileItems.begin(); it!=data_info.m_FileItems.end(); it++)
	{ 
		CString sDstFileName = it->GetBuffer(0);
		CString sFileName = it->GetBuffer(0);
		CString sDesc = L"";

		sMsg.Format(_T("Compressing file %s"), sDstFileName);

		hFile = CreateFile(sFileName, 
			GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
		if(hFile==INVALID_HANDLE_VALUE)
		{
			sMsg.Format(_T("Couldn't open file %s"), sFileName);
			continue;
		}

		BY_HANDLE_FILE_INFORMATION fi;
		GetFileInformationByHandle(hFile, &fi);

		SYSTEMTIME st;
		FileTimeToSystemTime(&fi.ftCreationTime, &st);

		zip_fileinfo info;
		info.dosDate = 0;
		info.tmz_date.tm_year = st.wYear;
		info.tmz_date.tm_mon = st.wMonth-1;
		info.tmz_date.tm_mday = st.wDay;
		info.tmz_date.tm_hour = st.wHour;
		info.tmz_date.tm_min = st.wMinute;
		info.tmz_date.tm_sec = st.wSecond;
		info.external_fa = FILE_ATTRIBUTE_NORMAL;
		info.internal_fa = FILE_ATTRIBUTE_NORMAL;

		int n = zipOpenNewFileInZip( hZip, (const char*)strconv.t2a(sDstFileName.GetBuffer(0)), &info,
			NULL, 0, NULL, 0, strconv.t2a(sDesc), Z_DEFLATED, Z_DEFAULT_COMPRESSION);
		if(n!=0)
		{
			sMsg.Format(_T("Couldn't compress file %s"), sDstFileName);
			continue;
		}

		for(;;)
		{
			BOOL bRead = ReadFile(hFile, buff, 1024, &dwBytesRead, NULL);
			if(!bRead || dwBytesRead==0)
				break;

			int res = zipWriteInFileInZip(hZip, buff, dwBytesRead);
			if(res!=0)
			{
				zipCloseFileInZip(hZip);
				sMsg.Format(_T("Couldn't write to compressed file %s"), sDstFileName);        
				break;
			}

			lTotalCompressed += dwBytesRead;

			float fProgress = 100.0f*lTotalCompressed/lTotalSize;
		}

		zipCloseFileInZip(hZip);
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}

	if(hZip!=NULL)
	{
		zipClose(hZip, NULL);
		hZip = NULL;
	}

	{
		sMsg.Format(_T("Calculating MD5 hash for file %s"), zip_file_Name);

		int nCalcMD5 = calc_file_md5_hash(zip_file_Name, sMD5Hash);
		if(nCalcMD5!=0)
		{
			sMsg.Format(_T("Couldn't calculate MD5 hash for file %s"), zip_file_Name);
			goto cleanup;
		}

#if _MSC_VER <1400
		f = _tfopen(zip_file_Name + _T(".md5"), _T("wt"));
#else
		_tfopen_s(&f, zip_file_Name + _T(".md5"), _T("wt"));
#endif
		if(f==NULL)
		{
			sMsg.Format(_T("Couldn't save MD5 hash for file %s"), zip_file_Name);
			goto cleanup;
		}

		_ftprintf(f, sMD5Hash);
		fclose(f);
		f = NULL;
	}

	if(lTotalSize==lTotalCompressed)
		bStatus = TRUE;

cleanup:

	if(hZip!=NULL)
		zipClose(hZip, NULL);

	if(hFile!=INVALID_HANDLE_VALUE)
		CloseHandle(hFile);

	if(f!=NULL)

	return bStatus;
}

int base64_encode_attachment(CString sFileName, 
										std::string& sEncodedFileData)
{
	strconv_t strconv;

	int uFileSize = 0;
	BYTE* uchFileData = NULL;  
	struct _stat st;  

	int nResult = _tstat(sFileName, &st);
	if(nResult != 0)
		return 1;  // File not found.

	// Allocate buffer of file size
	uFileSize = st.st_size;
	uchFileData = new BYTE[uFileSize];

	// Read file data to buffer.
	FILE* f = NULL;
#if _MSC_VER<1400
	f = _tfopen(sFileName, _T("rb"));
#else
	/*errno_t err = */_tfopen_s(&f, sFileName, _T("rb"));  
#endif 

	if(!f || fread(uchFileData, uFileSize, 1, f)!=1)
	{
		delete [] uchFileData;
		uchFileData = NULL;
		return 2; // Coudln't read file data.
	}

	fclose(f);

	sEncodedFileData = base64_encode(uchFileData, uFileSize);

	delete [] uchFileData;

	// OK.
	return 0;
}

BOOL WINAPI send_over_http( DataInfo &data_info )
{  
	strconv_t strconv;
	CHttpRequestSender http_sender; 
	AssyncNotification assync; 

	if(data_info.m_uPriorities[CR_HTTP]==CR_NEGATIVE_PRIORITY)
	{
		return FALSE;
	}

	if(data_info.m_sUrl.IsEmpty())
	{
		return FALSE;
	}

	CHttpRequest request;
	request.m_sUrl = data_info.m_sUrl;  

	request.m_aInTextFields[_T("appname")] = strconv.t2a(data_info.m_sAppName);
	request.m_aInTextFields[_T("appversion")] = strconv.t2a(data_info.m_sAppVersion);
	request.m_aInTextFields[_T("emailfrom")] = strconv.t2a(data_info.m_sEmailFrom);
	request.m_aInTextFields[_T("emailsubject")] = strconv.t2a(data_info.m_sEmailSubject);
	request.m_aInTextFields[_T("description")] = strconv.t2a(data_info.m_sDescription);

	CString sMD5Hash;
	calc_file_md5_hash(data_info.m_sZipName, sMD5Hash);
	request.m_aInTextFields[_T("md5")] = strconv.t2a(sMD5Hash);

	if(data_info.m_bHttpBinaryEncoding)
	{
		CHttpRequestFile f;
		f.m_sSrcFileName = data_info.m_sZipName;
		f.m_sContentType = _T("application/zip");  
		request.m_aIncludedFiles[_T("datafile")] = f;  
	}
	else
	{
		std::string sEncodedData;
		int nRet = base64_encode_attachment(data_info.m_sZipName, sEncodedData);
		if(nRet!=0)
		{
			return FALSE;
		}
		request.m_aInTextFields[_T("datafile")] = sEncodedData;
	}

	
	BOOL bSend = http_sender.Send(request, &assync);  
	return bSend;
}

// This method formats the E-mail message text
CString format_email_text( DataInfo data_info )
{
	CString sFileTitle = data_info.m_sZipName;
	sFileTitle.Replace('/', '\\');
	int pos = sFileTitle.ReverseFind('\\');
	if(pos>=0)
		sFileTitle = sFileTitle.Mid(pos+1);

	CString sText;

	sText += _T("This is the error report from ") + data_info.m_sAppName + 
		_T(" ") + data_info.m_sAppVersion+_T(".\n\n");

	if(!data_info.m_sEmailFrom.IsEmpty())
	{
		sText += _T("This error report was sent by ") + data_info.m_sEmailFrom + _T(".\n");
		sText += _T("If you need additional info about the problem, you may want to contact this user again.\n\n");
	}     

	if(!data_info.m_sEmailFrom.IsEmpty())
	{
		sText += _T("The user has provided the following problem description:\n<<< ") + 
			data_info.m_sDescription + _T(" >>>\n\n");    
	}

	sText += _T("You may find detailed information about the error in files attached to this message:\n\n");
	sText += sFileTitle + _T(" is a ZIP archive which contains crash description XML (crashrpt.xml), crash minidump (crashdump.dmp) ");
	sText += _T("and possibly other files that your application added to the crash report.\n\n");

	sText += sFileTitle + _T(".md5 file contains MD5 hash for the ZIP archive. You might want to use this file to check integrity of the error report.\n\n");

	sText += _T("For additional information, see FAQ http://code.google.com/p/crashrpt/wiki/FAQ\n");

	return sText;
}

// This method sends the report over SMTP 
BOOL WINAPI send_over_smtp( DataInfo &data_info)
{  
	strconv_t strconv;
	CEmailMessage email_msg; 
	CSmtpClient smtp_client; 
	AssyncNotification assync; 

	if(data_info.m_uPriorities[CR_SMTP]==CR_NEGATIVE_PRIORITY)
	{
		return FALSE;
	}

	if(data_info.m_sEmailTo.IsEmpty())
	{
		return FALSE;
	}

	email_msg.m_sFrom = (!data_info.m_sEmailFrom.IsEmpty()) ?
		data_info.m_sEmailFrom : data_info.m_sEmailTo; 

	email_msg.m_sTo = data_info.m_sEmailTo;
	email_msg.m_nRecipientPort = data_info.m_nSmtpPort;
	email_msg.m_sSubject = data_info.m_sEmailSubject;

	if(data_info.m_sEmailText.IsEmpty())
		email_msg.m_sText = format_email_text( data_info );
	else
		email_msg.m_sText = data_info.m_sEmailText;

	email_msg.m_aAttachments.clear();

	email_msg.m_aAttachments.insert(data_info.m_sZipName);  

	// Create and attach MD5 hash file
	CString file_hash;
	calc_file_md5_hash(data_info.m_sZipName, file_hash);
	CString sFileTitle = data_info.m_sZipName;
	
	sFileTitle.Replace('/', '\\');
	int pos = sFileTitle.ReverseFind('\\');
	if(pos>=0)
		sFileTitle = sFileTitle.Mid(pos+1);
	sFileTitle += _T(".md5");
	CString sTempDir;
	Utility::getTempDirectory(sTempDir);
	CString sTmpFileName = sTempDir +_T("\\")+ sFileTitle;
	FILE* f = NULL;
	_TFOPEN_S(f, sTmpFileName, _T("wt"));
	if(f!=NULL)
	{   
		LPCSTR szErrorRptHash = strconv.t2a(file_hash.GetBuffer(0));
		fwrite(szErrorRptHash, strlen(szErrorRptHash), 1, f);
		fclose(f);
		email_msg.m_aAttachments.insert(sTmpFileName);  
	}

	// Set SMTP proxy server (if specified)
	if ( !data_info.m_sSmtpProxyServer.IsEmpty())
		smtp_client.SetSmtpProxy( data_info.m_sSmtpProxyServer, data_info.m_nSmtpProxyPort);

	// Send mail
	int res = smtp_client.SendEmailAssync(&email_msg, &assync); 
	return (res==0);
}

// This method sends the report over Simple MAPI
BOOL WINAPI send_over_mapi( DataInfo &data_info )
{  
	strconv_t strconv;
	CMailMsg m_MapiSender; 

	if(data_info.m_uPriorities[CR_SMAPI]==CR_NEGATIVE_PRIORITY)
	{
		return FALSE;
	}

	if(data_info.m_sEmailTo.IsEmpty())
	{
		return FALSE;
	}

	if(data_info.m_bSilentMode)
	{
		return FALSE;
	}

	BOOL bMAPIInit = m_MapiSender.MAPIInitialize();
	if(!bMAPIInit)
	{
		return FALSE;
	}

	CString msg;
	CString sMailClientName;
	m_MapiSender.DetectMailClient(sMailClientName);

	msg.Format(_T("Launching the default email client (%s)"), sMailClientName);

	m_MapiSender.SetFrom(data_info.m_sEmailFrom);
	m_MapiSender.SetTo(data_info.m_sEmailTo);
	m_MapiSender.SetSubject(data_info.m_sEmailSubject);
	CString sFileTitle = data_info.m_sZipName;
	sFileTitle.Replace('/', '\\');
	int pos = sFileTitle.ReverseFind('\\');
	if(pos>=0)
		sFileTitle = sFileTitle.Mid(pos+1);

	if(data_info.m_sEmailText.IsEmpty())
		m_MapiSender.SetMessage(format_email_text(data_info));
	else
		m_MapiSender.SetMessage(data_info.m_sEmailText);
	m_MapiSender.AddAttachment(data_info.m_sZipName, sFileTitle);

	// Create and attach MD5 hash file
	CString file_hash;
	calc_file_md5_hash(data_info.m_sZipName, file_hash);
	sFileTitle += _T(".md5");
	CString sTempDir;
	Utility::getTempDirectory(sTempDir);
	CString sTmpFileName = sTempDir +_T("\\")+ sFileTitle;
	FILE* f = NULL;
	_TFOPEN_S(f, sTmpFileName, _T("wt"));
	if(f!=NULL)
	{ 
		LPCSTR _file_hash = strconv.t2a(file_hash.GetBuffer(0));
		fwrite(_file_hash, strlen(_file_hash), 1, f);
		fclose(f);
		m_MapiSender.AddAttachment(sTmpFileName, sFileTitle);  
	}

	BOOL bSend = m_MapiSender.Send();

	return bSend;
}

// This method sends the error report over the Internet
BOOL WINAPI send_data( DataInfo &data_info )
{
	INT32 status = 1; 
	INT32 _ret; 
	INT32 send_attempt = 0; 

	std::multimap<int, int> order;

	std::pair<int, int> pair3(data_info.m_uPriorities[CR_SMAPI], CR_SMAPI);
	order.insert(pair3);

	std::pair<int, int> pair2(data_info.m_uPriorities[CR_SMTP], CR_SMTP);
	order.insert(pair2);

	std::pair<int, int> pair1(data_info.m_uPriorities[CR_HTTP], CR_HTTP);
	order.insert(pair1);

	_ret = send_over_http( data_info );    


	// Remove compressed ZIP file and MD5 file
	Utility::RecycleFile(data_info.m_sZipName, true);
	Utility::RecycleFile(data_info.m_sZipName+_T(".md5"), true);

	if(status==0)
	{
		data_info.m_DeliveryStatus = DELIVERED;
		// Delete report files
		Utility::RecycleFile(data_info.m_sDataDirName, true);    
	}
	else
	{
		data_info.m_DeliveryStatus = FAILED;    

		// Check if we should store files for later delivery or we should remove them
		if(!data_info.m_bQueueEnabled)
		{
			// Delete report files
			Utility::RecycleFile(data_info.m_sDataDirName, true);    
		}
	}

	return 0;
}

#define PATH_DELIM_CH L'\\'

LRESULT WINAPI _get_app_path( LPWSTR FileName, 
							ULONG ccBufferLength, 
							ULONG *ccReturnLength )
{
	INT32 Ret = ERROR_SUCCESS; 
	ULONG _Ret; 
	LPWSTR PathDelim; 

	if( FileName == NULL )
	{
		Ret = ERROR_INVALID_PARAMETER; 
		goto _return; 
	}

	if( ccBufferLength == 0 )
	{
		Ret = ERROR_INVALID_PARAMETER; 
		goto _return; 
	}

	if( ccReturnLength == NULL )
	{
		Ret = ERROR_INVALID_PARAMETER; 
		goto _return; 
	}

	*ccReturnLength = 0; 

	_Ret = GetModuleFileName( NULL, FileName, ccBufferLength ); 
	if( _Ret >= ccBufferLength )
	{
		Ret = ERROR_ERRORS_ENCOUNTERED; 
		goto _return; 
	}
	else if( _Ret == 0 )
	{
		Ret = ERROR_ERRORS_ENCOUNTERED; 
		goto _return; 
	}

	PathDelim = wcsrchr( FileName, PATH_DELIM_CH ); 

	if( PathDelim == NULL )
	{
		Ret = ERROR_NOT_FOUND; 
		goto _return; 
	}

	if( ( ULONG )( PathDelim - FileName ) + 2 > ccBufferLength )
	{
		Ret = ERROR_ERRORS_ENCOUNTERED; 
		goto _return; 
	}

	PathDelim[ 1 ] = L'\0'; 

	*ccReturnLength = ( ULONG )( ULONG_PTR )( PathDelim - FileName + 1 ); 

_return: 
	return Ret; 
}

#define CODEREBA_WEBKITS_ULOAD_DATA_URL L"http://www.simpai.net/webkits/data_upload.php" 

INT32 WINAPI send_data_file(LPCTSTR url, LPTSTR data_file_name )
{ 
	INT32 ret = 1; 
	INT32 _ret; 
	DataInfo data_info; 

	do 
	{

		data_info.m_bHttpBinaryEncoding = TRUE; 
		data_info.m_bSilentMode = TRUE; 
		data_info.m_DeliveryStatus = PENDING; 
		data_info.m_bQueueEnabled = TRUE; 
		data_info.m_nSmtpPort = 0; 
		data_info.m_nSmtpProxyPort = 0; 
		data_info.m_sAppName = L"webkits"; 
		data_info.m_sAppVersion = L"0.9.1.1"; 

		do
		{
			LRESULT ret = ERROR_SUCCESS; 
			ULONG cc_ret_len; 
			WCHAR app_path[ MAX_PATH ];
			ret = _get_app_path( app_path, ARRAYSIZE( app_path), &cc_ret_len ); 
			if( ret != ERROR_SUCCESS )
			{
				break; 
			}

			data_info.m_sDataDirName = app_path; 
			data_info.m_sDescription = L""; 

			Utility::GetSystemTimeUTC(data_info.m_sSystemTimeUTC); 
		}while( FALSE ); 

		data_info.m_sUrl = url; 
		data_info.m_sZipName = data_info.m_sDataDirName; 
		data_info.m_sZipName += L"output.zip"; 

		data_info.m_uPriorities[ CR_HTTP ] = 2; 
		data_info.m_uPriorities[ CR_SMTP ] = 1; 
		data_info.m_uPriorities [ CR_SMAPI ] = 0; 


		{
			data_info.m_FileItems.push_back( data_file_name ); 
		}

		do 
		{
			_ret = compress_data_files( data_info, MAX_DATA_FILE_SIZE ); 
			if( FALSE == _ret )
			{
				break; 
			}

			_ret = send_data( data_info ); 
			if( FALSE == _ret )
			{
				break; 
			}
		} while ( FALSE ); 

	}while( FALSE );

	return ret;
}

LRESULT WINAPI parse_user_info_variable( LPCWSTR value_text, 
										DATA_ITEM *data_item )
{
	LRESULT ret = ERROR_SUCCESS; 
	LPWSTR param_begin; 
	LPWSTR param_end; 
	LPWSTR _param = NULL; 
	ULONG param_len; 

	do 
	{
		ATLASSERT( NULL != value_text ); 
		ATLASSERT( NULL != data_item ); 

#define USER_INFO_VALUE_EQUAL_SIGN L"="

		param_len = wcslen( value_text ); 
		if( param_len == 0 )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		_param = ( LPWSTR )malloc( ( param_len + 1 ) << 1 ); 

		if( NULL == _param )
		{
			ret = ERROR_NOT_ENOUGH_MEMORY; 
			break; 
		}

		memcpy( _param, value_text, ( ( param_len + 1 ) << 1 ) ); 

		param_begin = _param; 


		param_end = wcsstr( param_begin, USER_INFO_VALUE_EQUAL_SIGN ); 
		if( NULL == param_end )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		*param_end = L'\0'; 
		data_item->name = param_begin; 
		*param_end = L'='; 

		param_begin = param_end + 1; 
		data_item->data_text = param_begin; 

	}while( FALSE );

	if( NULL != _param )
	{
		free( _param ); 
	}

	return ret; 
}

LRESULT WINAPI parse_user_info_response( LPCWSTR response, 
									   DATA_ITEMS *data_items )
{
	LRESULT ret = ERROR_SUCCESS; 
	LRESULT _ret; 
	LPWSTR param_begin; 
	LPWSTR param_end; 
	LPWSTR _param = NULL; 
	ULONG param_len; 
	DATA_ITEM *item = NULL; 

	do 
	{
		ATLASSERT( NULL != response ); 
		ATLASSERT( NULL != data_items ); 

#define USER_INFO_VALUE_DELIM_CHAR L";"

		param_len = wcslen( response ); 
		if( param_len == 0 )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		_param = ( LPWSTR )malloc( ( param_len + 1 ) << 1 ); 

		if( NULL == _param )
		{
			ret = ERROR_NOT_ENOUGH_MEMORY; 
			break; 
		}

		memcpy( _param, response, ( ( param_len + 1 ) << 1 ) ); 

		param_begin = _param; 

		for( ; ; )
		{
			item = NULL; 
			param_end = wcsstr( param_begin, USER_INFO_VALUE_DELIM_CHAR ); 
			if( NULL == param_end )
			{
				item = new DATA_ITEM(); 
				if( NULL == item )
				{
					ret = ERROR_NOT_ENOUGH_MEMORY; 
					break; 
				}

				_ret = parse_user_info_variable( param_begin, item ); 
				if( ERROR_SUCCESS != _ret )
				{
					delete item; 
					ret = _ret; 
					break; 
				}

				data_items->push_back( item ); 
				break; 
			}

			do 
			{
				*param_end = L'\0'; 
				item = new DATA_ITEM(); 
				if( NULL == item )
				{
					ret = ERROR_NOT_ENOUGH_MEMORY; 
					break; 
				}

				_ret = parse_user_info_variable( param_begin, item ); 
				if( ERROR_SUCCESS != _ret )
				{
					ret = _ret; 
					break; 
				}

				data_items->push_back( item ); 
				item = NULL; 
			}while( FALSE ); 
			if( NULL != item )
			{
				delete item; 
			}

			param_begin = param_end + 1; 
		}
	}while( FALSE );

	if( NULL != _param )
	{
		free( _param ); 
	}

	return ret; 
}


LRESULT WINAPI send_data_over_http( LPCWSTR url, 
								   DATA_ITEMS *data_input, 
								   DATA_ITEMS *data_output )
{ 
	LRESULT ret = ERROR_SUCCESS; 
	LRESULT _ret; 
	strconv_t strconv;
	CHttpRequestSender http_sender; 
	AssyncNotification assync; 
	CHttpRequest request; 
	BOOL bSend  = FALSE; 
	DATA_ITEM *data_item; 

	do 
	{
		ATLASSERT( data_input != NULL ); 
		ATLASSERT( data_output != NULL ); 

		if( NULL == url 
			|| *url == L'\0' )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		request.m_sUrl = url;  

		for( DATA_ITEMS::iterator it = data_input->begin(); 
			it != data_input->end(); 
			it ++ )
		{
			do 
			{
				if( ( *it )->name.length() == 0 
					|| ( *it )->data_text.length() == 0 )
				{
					break; 
				}

				request.m_aInTextFields[ ( *it )->name.c_str() ] = strconv.t2a(( *it )->data_text.c_str() );
			}while( FALSE );
		}

		bSend = http_sender.Send(request, &assync); 
		if( bSend == FALSE )
		{

		}

		data_item = NULL; 

		if( request.m_aOutTextFields.size() == 0 )
		{
			ret = ERROR_ERRORS_ENCOUNTERED; 
			break; 
		}

		{
			wstring _text; 
			_text = strconv.utf82w( ( *request.m_aOutTextFields.begin() ).second.c_str() ); 
			
			_ret = parse_user_info_response( _text.c_str(), 
				data_output ); 
			if( _ret != ERROR_SUCCESS )
			{
				break; 
			}
		}

	}while( FALSE );

	return ret;
}

#if TEST_DATA_SENDER
WTL::CAppModule _Module; 

INT32 WINAPI Run(LPTSTR /*lpstrCmdLine*/ = NULL, int /*nCmdShow*/ = SW_SHOWDEFAULT)
{ 
	INT32 ret = 1; 
	INT32 _ret; 
	LPCWSTR szCommandLine = GetCommandLineW();
	DataInfo data_info; 
	INT32 i; 

	do 
	{
		// Split command line
		int argc = 0;
		LPWSTR* argv = CommandLineToArgvW( szCommandLine, &argc ); 

		if( argc < 2 )
		{
			break; // No arguments passed
		}

		data_info.m_bHttpBinaryEncoding = TRUE; 
		data_info.m_bSilentMode = TRUE; 
		data_info.m_DeliveryStatus = PENDING; 
		data_info.m_bQueueEnabled = TRUE; 
		data_info.m_nSmtpPort = 0; 
		data_info.m_nSmtpProxyPort = 0; 
		data_info.m_sAppName = L"webkits"; 
		data_info.m_sAppVersion = L"0.9.1.1"; 

		do
		{
			LRESULT ret = ERROR_SUCCESS; 
			ULONG cc_ret_len; 
			WCHAR app_path[ MAX_PATH ];
			ret = _get_app_path( app_path, ARRAYSIZE( app_path), &cc_ret_len ); 
			if( ret != ERROR_SUCCESS )
			{
				break; 
			}

			data_info.m_sDataDirName = app_path; 
			data_info.m_sDescription = L""; 
			
			Utility::GetSystemTimeUTC(data_info.m_sSystemTimeUTC); 
		}while( FALSE ); 

		data_info.m_sUrl = argv[ 1 ]; 
		data_info.m_sZipName = data_info.m_sDataDirName; 
		data_info.m_sZipName += L"output.zip"; 
		
		data_info.m_uPriorities[ CR_HTTP ] = 2; 
		data_info.m_uPriorities[ CR_SMTP ] = 1; 
		data_info.m_uPriorities [ CR_SMAPI ] = 0; 
		
		for( i = 1; i < argc; i ++ )
		{
			data_info.m_FileItems.push_back( argv[ i ] ); 
		}

		// Check window mirroring settings 

		//CMessageLoop theLoop;
		//_Module.AddMessageLoop(&theLoop);

		do 
		{
			// Process window messages
			//_ret = theLoop.Run();

			data_info.m_sUrl = CODEREBA_WEBKITS_ULOAD_DATA_URL; 

			_ret = compress_data_files( data_info, MAX_DATA_FILE_SIZE ); 
			if( FALSE == _ret )
			{
				break; 
			}

			_ret = send_data( data_info ); 
			if( FALSE == _ret )
			{
				break; 
			}
		} while ( FALSE ); 

		// Wait until the worker thread is exited  
		//g_DataSender.WaitForCompletion();
		//nRet = g_DataSender.GetGlobalStatus();

		// Remove temporary files we might create and perform other finalizing work
		//g_DataSender.Finalize();

		//_Module.RemoveMessageLoop();
	}while( FALSE );

	return ret;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{  
	HRESULT hRes = ::CoInitialize(NULL);
	// If you are running on NT 4.0 or higher you can use the following call instead to 
	// make the EXE free threaded. This means that calls come in on a random RPC thread.
	//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run( lpstrCmdLine, nCmdShow );

	_Module.Term();
	::CoUninitialize();

	return nRet;
}

#endif //TEST_DATA_SENDER