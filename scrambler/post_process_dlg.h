#pragma once


// post_process_dlg ��Ԓ���K

class post_process_dlg : public CDialog
{
	DECLARE_DYNAMIC(post_process_dlg)

public:
	post_process_dlg(CWnd* pParent = NULL);   // �˜ʽ�����ʽ
	virtual ~post_process_dlg();

// ��Ԓ���K�Y��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧Ԯ

	DECLARE_MESSAGE_MAP()
};
