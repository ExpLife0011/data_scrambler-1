// File: AssyncNotification.h
// Description: Provides a way to communicate between sender thread and the main thread.
// Authors: zexspectrum
// Date: 2009

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

#pragma once
#ifdef TEST_DATA_SENDER
#include "data_center_pch.h"
#else
#include "stdafx.h"
#endif //TEST_DATA_SENDER

struct AssyncNotification
{
    /* Constructor */
    AssyncNotification();  

    // Resets the event
    void Reset();

    // Sets the progress message and percent completed
    void SetProgress(CString sStatusMsg, int percentCompleted, bool bRelative=true);

    // Sets the percent completed
    void SetProgress(int percentCompleted, bool bRelative=true);

    // Returns the current assynchronious operation progress
    void GetProgress(int& nProgressPct, std::vector<CString>& msg_log);

    // Notifies about assynchronious operation completion
    void SetCompleted(int nCompletionStatus);

    // Blocks until assynchronious operation is completed
    int WaitForCompletion();

    // Cancels the assynchronious operation
    void Cancel();

    // Determines if the assynchronious operation was cancelled
    bool IsCancelled();

    // Waits until the feedback is received
    void WaitForFeedback(int &code);

    // Notifies about feedback is ready to be received
    void FeedbackReady(int code);

private:

    CComAutoCriticalSection m_cs; // Protects internal state
    int m_nCompletionStatus;      // Completion status of the assync operation
    HANDLE m_hCompletionEvent;    // Completion event
    HANDLE m_hCancelEvent;        // Cancel event
    HANDLE m_hFeedbackEvent;      // Feddback event
    int m_nPercentCompleted;      // Percent completed
    std::vector<CString> m_statusLog; // Status log
};
