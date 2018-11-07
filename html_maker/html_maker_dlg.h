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

// html_maker_dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

// html_maker_dlg �Ի���
class html_maker_dlg : public CDialog
{
// ����
public:
	html_maker_dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~html_maker_dlg(); 

// �Ի�������
	enum { IDD = IDD_HTML_MAKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	BOOL bReady;				 //�ж�yahoo����ҳ���Ƿ���ȫ��


// ʵ��

protected: 
	LRESULT html_auto_on_web_site(); 

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonAutoRun(); 
	afx_msg void OnBnClickedButtonOpenFile(); 
	DECLARE_MESSAGE_MAP()

protected:
	LRESULT init_html_config_ui(); 
	LRESULT auto_run_on_html(); 
	LRESULT load_html_config_files_from_record(); 
	LRESULT load_html_config_files_from_work_dir(); 
	LRESULT load_html_auto_config_file( LPCWSTR file_name ); 

protected: 
	CString config_file_name; 
	BOOLEAN com_inited; 
public:
	CListCtrl html_page_list;
};
