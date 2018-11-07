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

// File: httpsend.h
// Description: Sends error report over HTTP connection.
// Authors: zexspectrum
// Date: 2009

#pragma once
#ifdef TEST_DATA_SENDER
#include "data_center_pch.h"
#else
#include "stdafx.h"
#endif //TEST_DATA_SENDER
#include "AssyncNotification.h"
#include <WinInet.h>
#include <map>

struct CHttpRequestFile
{  
    CString m_sSrcFileName;  // Name of the file attachment.
    CString m_sContentType;  // Content type.
};

// HTTP request information
class CHttpRequest
{
public:
    CString m_sUrl;      // Script URL  
    std::map<CString, std::string> m_aInTextFields;    // Array of text fields to include into POST data
	std::map<CString, CHttpRequestFile> m_aIncludedFiles; // Array of binary files to include into POST data
	std::map<CString, std::string> m_aOutTextFields;    // Array of text fields to include into POST data
};

// Sends HTTP request
// See also: RFC 1867 - Form-based File Upload in HTML (http://www.ietf.org/rfc/rfc1867.txt)
class CHttpRequestSender
{
public:

    CHttpRequestSender();

	BOOL Send(CHttpRequest& Request, AssyncNotification* an); 
    // Sends HTTP request assynchroniously
    BOOL SendAssync(CHttpRequest& Request, AssyncNotification* an);

private:

    // Worker thread procedure
    static DWORD WINAPI WorkerThread(VOID* pParam);  

    BOOL InternalSend();

    // Used to calculate summary size of the request
    BOOL CalcRequestSize(LONGLONG& lSize);
    BOOL FormatTextPartHeader(CString sName, CString& sText);
    BOOL FormatTextPartFooter(CString sName, CString& sText);  
    BOOL FormatAttachmentPartHeader(CString sName, CString& sText);
    BOOL FormatAttachmentPartFooter(CString sName, CString& sText);
    BOOL FormatTrailingBoundary(CString& sBoundary);
    BOOL CalcTextPartSize(CString sFileName, LONGLONG& lSize);
    BOOL CalcAttachmentPartSize(CString sFileName, LONGLONG& lSize);
    BOOL WriteTextPart(HINTERNET hRequest, CString sName);
    BOOL WriteAttachmentPart(HINTERNET hRequest, CString sName);
    BOOL WriteTrailingBoundary(HINTERNET hRequest);
    void UploadProgress(DWORD dwBytesWritten);

    // This helper function is used to split URL into several parts
    void ParseURL(LPCTSTR szURL, LPTSTR szProtocol, UINT cbProtocol,
        LPTSTR szAddress, UINT cbAddress, DWORD &dwPort, LPTSTR szURI, UINT cbURI);

    CHttpRequest m_Request;       // HTTP request being sent
    AssyncNotification* m_Assync; // Used to communicate with the main thread  

    CString m_sFilePartHeaderFmt;
    CString m_sFilePartFooterFmt;
    CString m_sTextPartHeaderFmt;
    CString m_sTextPartFooterFmt;
    CString m_sBoundary;
    DWORD m_dwPostSize;
    DWORD m_dwUploaded;
};


