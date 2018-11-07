/************************************************************************************* 
This file is a part of CrashRpt library.

Copyright (c) 2003, Michael Carruth
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this 
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

* Neither the name of the author nor the names of its contributors 
may be used to endorse or promote products derived from this software without 
specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************************/

// File: CrashInfoReader.cpp
// Description: Retrieves crash information passed from CrashRpt.dll in form of XML files.
// Authors: zexspectrum
// Date: 2010

#include "stdafx.h"
#include "CrashRpt.h"
#include "DataReader.h"
#include "strconv.h"
#include "tinyxml.h"
#include "Utility.h"

// Define global CDataReader object
CDataReader g_DataInfo;

int CDataReader::Init(LPCTSTR szFileMappingName)
{ 
    strconv_t strconv;

    BOOL bCreateFolder = Utility::CreateFolder(m_sUnsentCrashReportsFolder);
    if(!bCreateFolder)
        return 3;

    //m_sINIFile = m_sUnsentCrashReportsFolder + _T("\\~CrashRpt.ini"); 

	// Unblock the parent process
	//CString sEventName;
	//HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, sEventName);
	//if(hEvent!=NULL)
	//	SetEvent(hEvent);

    return 0;
}

DataInfo& CDataReader::GetReport(int nIndex)
{ 
	ATLASSERT(nIndex>=0 && nIndex<(int)m_DataFiles.size());
	
    return m_DataFiles[nIndex]; 
}

int CDataReader::GetReportCount()
{ 
    return (int)m_DataFiles.size(); 
}

void CDataReader::DeleteReport(int nIndex)
{
	ATLASSERT(nIndex>=0 && nIndex<(int)m_DataFiles.size());

	// Delete report files
	Utility::RecycleFile(m_DataFiles[nIndex].m_sDataDirName, TRUE);

	// Delete from list
	m_DataFiles[nIndex].m_DeliveryStatus = DELETED;
}

void CDataReader::DeleteAllReports()
{
	int i;
	for(i=0; i<(int)m_DataFiles.size(); i++)
	{
		// Delete report files
		Utility::RecycleFile(m_DataFiles[i].m_sDataDirName, TRUE);

		m_DataFiles[i].m_DeliveryStatus = DELETED;
	}	
}

LONG64 CDataReader::GetUncompressedReportSize(DataInfo& eri)
{
    LONG64 lTotalSize = 0;
    std::map<CString, DataFileItem>::iterator it;
    HANDLE hFile = INVALID_HANDLE_VALUE;  
    CString sMsg;
    BOOL bGetSize = FALSE;
    LARGE_INTEGER lFileSize;

    for(it=eri.m_FileItems.begin(); it!=eri.m_FileItems.end(); it++)
    {   
        CString sFileName = it->second.m_sSrcFile.GetBuffer(0);
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

HICON CDataReader::GetCustomIcon()
{
    if(!g_DataInfo.m_sCustomSenderIcon.IsEmpty())
    {
        CString sResourceFile;
        CString sIconIndex;
        int nIconIndex = 0;

        int nComma = g_DataInfo.m_sCustomSenderIcon.ReverseFind(',');    
        if(nComma>=0)
        {
            sResourceFile = g_DataInfo.m_sCustomSenderIcon.Left(nComma);      
            sIconIndex = g_DataInfo.m_sCustomSenderIcon.Mid(nComma+1);
            sIconIndex.TrimLeft();
            sIconIndex.TrimRight();
            nIconIndex = _ttoi(sIconIndex);      
        }
        else
        {
            sResourceFile = g_DataInfo.m_sCustomSenderIcon;
        }

        sResourceFile.TrimRight();        

        if(nIconIndex==-1)
        {      
            return NULL;
        }

        // Check that custom icon can be loaded
        HICON hIcon = ExtractIcon(NULL, sResourceFile, nIconIndex);
        if(hIcon==NULL || hIcon==(HICON)1)
        { 
            return NULL;
        }

        return hIcon;
    }

    return NULL;
}