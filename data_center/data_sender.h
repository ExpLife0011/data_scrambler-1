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

#ifndef __DATA_SENDER_H__
#define __DATA_SENDER_H__

// Array indices for CR_INSTALL_INFO::uPriorities.
#define CR_HTTP 0  //!< Send error report via HTTP (or HTTPS) connection.
#define CR_SMTP 1  //!< Send error report via SMTP connection.
#define CR_SMAPI 2 //!< Send error report via simple MAPI (using default mail client).

//! Special priority constant that allows to skip certain delivery method.
#define CR_NEGATIVE_PRIORITY ((UINT)-1)

// The structure describing a file item.
struct DataFileItem
{
	DataFileItem()
	{
		m_bMakeCopy = FALSE;
	}

	CString m_sDestFile;  // Destination file name (not including directory name).
	CString m_sSrcFile;   // Absolute source file path.
	CString m_sDesc;      // File description.
	BOOL m_bMakeCopy;     // Should we copy source file to temporary folder?
	CString m_sErrorStatus; // Empty if OK, non-empty if error occurred.
};

// Error report delivery status
enum DELIVERY_STATUS
{  
	PENDING    = 0,  // Status pending  
	DELIVERED  = 1,  // Error report was delivered ok
	FAILED     = 2,  // Error report delivery failed
	DELETED    = 3   // Error report was deleted by user
};

struct DataInfo
{
	DataInfo()
	{
		//m_bSelected = TRUE;
		m_DeliveryStatus = PENDING;    
		m_uTotalSize = 0;
	}

	CString     m_sAppName;            // Application name.
	CString     m_sAppVersion;         // Application version.
	CString     m_sDataDirName; // Name of the directory where error report files are located.
	CString     m_sUrl; 
	CString     m_sSmtpProxyServer; 
	INT32       m_nSmtpProxyPort; 
	CString     m_sEmailFrom;          // E-mail sender address.
	CString     m_sEmailTo;          // E-mail sender address.
	CString     m_sEmailText; 
	INT32       m_nSmtpPort;
	CString     m_sEmailSubject;
	CString     m_sDescription;        // User-provided problem description.
	CString     m_sSystemTimeUTC;      // The time when crash occurred (UTC).
	CString     m_sGeoLocation;        // Geographic location.
	ULONG64     m_uTotalSize;          // Summary size of this (uncompressed) report.
	//BOOL        m_bSelected;           // Is this report selected for delivery.
	UINT        m_uPriorities[3];       // Delivery priorities
	CString     m_sZipName; 
	DELIVERY_STATUS m_DeliveryStatus;  // Delivery status.
	BOOLEAN     m_bSilentMode; 
	BOOLEAN     m_bHttpBinaryEncoding; 
	BOOLEAN     m_bQueueEnabled; 

	std::vector< CString > m_FileItems; 
	//std::map<CString, DataFileItem>  m_FileItems; // The list of files that are included into this report.
	//std::map<CString, CString> m_Props;   // The list of custom properties
};

LONG64 WINAPI get_uncompressed_data_size(DataInfo& data_info); 

// This method calculates an MD5 hash for the file
int calc_file_md5_hash(CString sFileName, CString& sMD5Hash); 

// This method compresses the files contained in the report and produces ZIP archive.
BOOL compress_data_files( DataInfo& data_info ); 

int base64_encode_attachment(CString sFileName, 
						   std::string& sEncodedFileData); 

BOOL WINAPI send_over_http( DataInfo &data_info ); 
CString format_email_text( DataInfo data_info ); 
BOOL WINAPI send_over_smtp( DataInfo &data_info); 
BOOL WINAPI send_over_mapi( DataInfo &data_info ); 
BOOL WINAPI send_data( DataInfo &data_info ); 
INT32 WINAPI send_data_file(LPCTSTR url, LPTSTR data_file_name ); 

#include <string>
using namespace std; 

typedef struct _DATA_ITEM
{
	wstring name; 
	wstring data_text; 
} DATA_ITEM, *PDATA_ITEM; 

typedef vector< DATA_ITEM* > DATA_ITEMS; 

LRESULT WINAPI send_data_over_http( LPCWSTR url, 
								   DATA_ITEMS *data_input, 
								   DATA_ITEMS *data_output ); 

#define INLINE __inline 
INLINE LRESULT WINAPI release_data_items( DATA_ITEMS *data_items )
{
	LRESULT ret = ERROR_SUCCESS; 
	
	do 
	{
		ATLASSERT( NULL != data_items ); 
		for( DATA_ITEMS::iterator it = data_items->begin(); 
			it != data_items->end(); 
			it ++ )
		{
			delete ( *it ); 
		}

		data_items->clear(); 
	}while( FALSE );

	return ret; 
}

#endif //__DATA_SENDER_H__