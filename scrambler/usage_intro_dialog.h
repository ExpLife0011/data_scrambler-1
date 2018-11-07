/*
 *
 * Copyright 2010 JiJie Shi
 *
 * This file is part of data_scrambler.
 *
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

#include "resource.h"

class usage_intro_dialog : public CDialog
{
	DECLARE_DYNAMIC(usage_intro_dialog)

public:
	usage_intro_dialog(CWnd* pParent = NULL); 
	virtual ~usage_intro_dialog();

	enum { IDD = IDD_DIALOG_USAGE_INTRO };

protected:
	wstring user_name; 
	CFont font; 

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual void OnCancel(); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGetAccess();
};
