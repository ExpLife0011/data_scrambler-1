// post_process_dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "data_scrambler.h"
#include "post_process_dlg.h"


// post_process_dlg 對話方塊

IMPLEMENT_DYNAMIC(post_process_dlg, CDialog)

post_process_dlg::post_process_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(post_process_dlg::IDD, pParent)
{

}

post_process_dlg::~post_process_dlg()
{
}

void post_process_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(post_process_dlg, CDialog)
END_MESSAGE_MAP()

#include "json/json.h"

LRESULT post_process_dlg::set_script_json(wstring &json)
{
	LRESULT ret = ERROR_SUCCESS; 
	Json::Value root;
	Json::Value data;

	Json::Reader json_reader;
	
	do 
	{
		std::string utf8_string; 
	
		ret = unicode_to_utf8_ex(json.c_str(), utf8_string); 
		if( ret != ERROR_SUCCESS )
		{
			break; 
		}

		if(false == json_reader.parse(utf8_string, root, true) )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		if( false == root.isArray() 
			|| root.size() == 0 )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		data = root.get(Json::ArrayIndex(0), data); 

		command = data["command"].asString(); 
		script = data["script"].asString(); 
	} while (FALSE);
	return ret; 
}

void post_process_dlg::OnOK() 
{
	UpdateData(TRUE); 

	CString	command;
	CString script; 

	GetDlgItemText(IDC_EDIT_POST_PROCESS_COMMAND, command); 
	GetDlgItemText(IDC_EDIT_POST_PROCESS_SCRIPT, script); 

	LRESULT ret = ERROR_SUCCESS; 
	Json::Value root;
	Json::Value data;

	Json::FastWriter fw;

	do 
	{
		LRESULT ret; 
		std::string utf8_string; 

		ret = unicode_to_utf8_ex(command.GetBuffer(), utf8_string); 
		if( ret != ERROR_SUCCESS )
		{
			break; 
		}

		data["command"] = utf8_string;  

		ret = unicode_to_utf8_ex(script.GetBuffer(), utf8_string); 
		if( ret != ERROR_SUCCESS )
		{
			break; 
		}

		data["script"] = utf8_string; 

		root.append(data); 
		script_json = fw.write(root); 

		CDialog::OnOK(); 
	}while(FALSE); 
	return; 
}

// post_process_dlg 訊息處理常式
BOOL post_process_dlg::OnInitDialog()
{
	LRESULT ret; 
	CDialog::OnInitDialog();

	SetDlgItemTextA(GetSafeHwnd(), IDC_EDIT_POST_PROCESS_COMMAND, command.c_str() ); 
	SetDlgItemTextA(GetSafeHwnd(), IDC_EDIT_POST_PROCESS_SCRIPT, script.c_str() ); 
	return TRUE;  // return TRUE  unless you set the focus to a control
}
