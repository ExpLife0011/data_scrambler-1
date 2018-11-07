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
#include "AssyncNotification.h"

AssyncNotification::AssyncNotification()
{
    // Init variables
    m_hCompletionEvent = CreateEvent(0, FALSE, FALSE, 0);
    m_hCancelEvent = CreateEvent(0, FALSE, FALSE, 0);
    m_hFeedbackEvent = CreateEvent(0, FALSE, FALSE, 0);

    Reset();
}

void AssyncNotification::Reset()
{ 
    // Reset the event

    m_cs.Lock(); // Acquire lock

    m_nCompletionStatus = -1;    
    m_nPercentCompleted = 0;
    m_statusLog.clear();

    ResetEvent(m_hCancelEvent);
    ResetEvent(m_hCompletionEvent);
    ResetEvent(m_hFeedbackEvent);

    m_cs.Unlock(); // Free lock
}

void AssyncNotification::SetProgress(CString sStatusMsg, int percentCompleted, bool bRelative)
{
    m_cs.Lock(); // Acquire lock

    m_statusLog.push_back(sStatusMsg);

    if(bRelative) // Update progress relatively to its previous value
    {
        m_nPercentCompleted += percentCompleted;
        if(m_nPercentCompleted>100)
            m_nPercentCompleted = 100;      
    }
    else // Update progress relatively to zero
    {
        m_nPercentCompleted = percentCompleted;
    }

    m_cs.Unlock(); // Free lock
}

void AssyncNotification::SetProgress(int percentCompleted, bool bRelative)
{
    m_cs.Lock(); // Acquire lock

    if(bRelative) // Update progress relatively to its previous value
    {
        m_nPercentCompleted += percentCompleted;
        if(m_nPercentCompleted>100)
            m_nPercentCompleted = 100;      
    }
    else // Update progress relatively to zero
    {
        m_nPercentCompleted = percentCompleted;
    }

    m_cs.Unlock(); // Free lock
}

void AssyncNotification::GetProgress(int& nProgressPct, std::vector<CString>& msg_log)
{
    msg_log.clear(); // Init message log (clear it)

    m_cs.Lock(); // Acquire lock

    nProgressPct = m_nPercentCompleted;
    msg_log = m_statusLog;
    m_statusLog.clear();

    m_cs.Unlock(); // Free lock
}

void AssyncNotification::SetCompleted(int nCompletionStatus)
{
    // Notifies about assynchronious operation completion
    m_cs.Lock(); // Acquire lock
    m_nCompletionStatus = nCompletionStatus;
    m_cs.Unlock(); // Free lock
    SetEvent(m_hCompletionEvent); // Set event
}

int AssyncNotification::WaitForCompletion()
{
    // Blocks until assynchronous operation is completed
    WaitForSingleObject(m_hCompletionEvent, INFINITE);

    // Get completion status
    int status = -1;
    m_cs.Lock(); // Acquire lock
    status = m_nCompletionStatus;
    m_cs.Unlock(); // Free lock

    return status;
}

void AssyncNotification::Cancel()
{
    // Cansels the assync operation
    SetProgress(_T("[cancelled_by_user]"), 0);
    SetEvent(m_hCancelEvent);
}

bool AssyncNotification::IsCancelled()
{
    // Determines if the assync operation is cancelled or not
    DWORD dwWaitResult = WaitForSingleObject(m_hCancelEvent, 0);
    if(dwWaitResult==WAIT_OBJECT_0)
    {
        SetEvent(m_hCancelEvent);      
        return true;
    }

    return false;
}

void AssyncNotification::WaitForFeedback(int &code)
{
    // Waits until the main thread's signal
    ResetEvent(m_hFeedbackEvent);      
    WaitForSingleObject(m_hFeedbackEvent, INFINITE);
    m_cs.Lock();
    code = m_nCompletionStatus;
    m_cs.Unlock();
}

void AssyncNotification::FeedbackReady(int code)
{
    // Sends signal to the waiting thread
    m_cs.Lock();
    m_nCompletionStatus = code;
    m_cs.Unlock();
    SetEvent(m_hFeedbackEvent);      
}
