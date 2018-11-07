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


///////////////////////////////////////////////////////////////////////////////
//
//  Module: MailMsg.h
//
//    Desc: This class encapsulates the MAPI and CMC mail functions.
//
// Copyright (c) 2003 Michael Carruth
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MAILMSG_H_
#define _MAILMSG_H_

#ifdef TEST_DATA_SENDER
#include "data_center_pch.h"
#else
#include "stdafx.h"
#endif //TEST_DATA_SENDER
#include <XCMC.h>
#include <MAPI.h>
#include <map>
typedef std::map<std::string, std::string> TStrStrMap;

//
// Define CMC entry points
//
typedef CMC_return_code (FAR PASCAL *LPCMCLOGON) \
(CMC_string, CMC_string, CMC_string, CMC_object_identifier, \
 CMC_ui_id, CMC_uint16, CMC_flags, CMC_session_id FAR*, \
 CMC_extension FAR*);

typedef CMC_return_code (FAR PASCAL *LPCMCSEND) \
(CMC_session_id, CMC_message FAR*, CMC_flags, \
 CMC_ui_id, CMC_extension FAR*);

typedef CMC_return_code (FAR PASCAL *LPCMCLOGOFF) \
(CMC_session_id, CMC_ui_id, CMC_flags, CMC_extension FAR*);

typedef CMC_return_code (FAR PASCAL *LPCMCQUERY) \
(CMC_session_id, CMC_enum, CMC_buffer, CMC_extension FAR*);


////////////////////////////// Class Definitions /////////////////////////////

// ===========================================================================
// CMailMsg
// 
// See the module comment at top of file.
//
class CMailMsg  
{
public:

    // Construction/destruction
    CMailMsg();
    virtual ~CMailMsg();

    // Operations
    void SetTo(CString sAddress);
    void SetFrom(CString sAddress);
    void SetSubject(CString sSubject);
    void SetMessage(CString sMessage);
    void AddAttachment(CString sAttachment, CString sTitle = _T(""));

    BOOL MAPIInitialize();
    void MAPIFinalize();

    static BOOL DetectMailClient(CString& sMailClientName);
    CString GetEmailClientName();
    BOOL Send();
    BOOL MAPISend();   
    BOOL CMCSend();
    CString GetLastErrorMsg(){ return m_sErrorMsg; }

protected:

    std::string    m_from;                       // From <address,name>
    std::string    m_to;                         // To <address,name>
    TStrStrMap     m_attachments;                // Attachment <file,title>
    std::string    m_sSubject;                   // EMail subject
    std::string    m_sMessage;                   // EMail message

    HMODULE        m_hMapi;                      // Handle to MAPI32.DLL
    LPCMCQUERY     m_lpCmcQueryConfiguration;    // Cmc func pointer
    LPCMCLOGON     m_lpCmcLogon;                 // Cmc func pointer
    LPCMCSEND      m_lpCmcSend;                  // Cmc func pointer
    LPCMCLOGOFF    m_lpCmcLogoff;                // Cmc func pointer
    LPMAPILOGON    m_lpMapiLogon;                // Mapi func pointer
    LPMAPISENDMAIL m_lpMapiSendMail;             // Mapi func pointer
    LPMAPILOGOFF   m_lpMapiLogoff;               // Mapi func pointer

    BOOL           m_bReady;                     // MAPI is loaded
    CString        m_sEmailClientName;

    CString        m_sErrorMsg;
};

#endif	// _MAILMSG_H_
