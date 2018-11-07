#pragma once


// post_process_dlg 對話方塊

class post_process_dlg : public CDialog
{
	DECLARE_DYNAMIC(post_process_dlg)

public:
	post_process_dlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~post_process_dlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_POST_PROCESS };

	virtual void OnOK(); 
	virtual BOOL OnInitDialog(); 

	LRESULT set_script_json(wstring &json); 

	string get_script_json()
	{
		return script_json; 
	}

private:
	string script_json; 
	string command; 
	string script; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
};
