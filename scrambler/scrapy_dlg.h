#pragma once
#include <afxcmn.h>
#include "OleRichEditCtrl.h"


// scrapy_dlg ��Ԓ���K

class scrapy_dlg : public CDialog
{
	DECLARE_DYNAMIC(scrapy_dlg)

public:
	scrapy_dlg(CWnd* pParent = NULL);   // �˜ʽ�����ʽ
	virtual ~scrapy_dlg();

// ��Ԓ���K�Y��
	enum { IDD = IDD_SCRAPY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧Ԯ

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();

public:
    COleRichEditCtrl edit_script;

public:
    LRESULT open_script_file(LPCWSTR file_name); 
    LRESULT set_target_html_element_info(PVOID html_element, LPCWSTR xpath, LPCWSTR std_xpath); 
    LRESULT save_script_file(); 
    afx_msg void OnBnClickedButtonCopy();
    afx_msg void OnBnClickedButtonOpen();
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
    CString script_file_name; 
public:
    afx_msg void OnBnClickedButtonSave();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};
