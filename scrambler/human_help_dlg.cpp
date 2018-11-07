// human_help_dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "data_scrambler.h"
#include "human_help_dlg.h"


// human_help_dlg �Ի���

IMPLEMENT_DYNAMIC(human_help_dlg, CDialog)

human_help_dlg::human_help_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_HELP, pParent)
{

}

human_help_dlg::~human_help_dlg()
{
}

void human_help_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(human_help_dlg, CDialog)
    ON_STN_CLICKED(IDC_STATIC_BUY_LINK1, &human_help_dlg::OnStnClickedStaticBuyLink1)
    ON_STN_CLICKED(IDC_STATIC_BUY_LINK2, &human_help_dlg::OnStnClickedStaticBuyLink2)
END_MESSAGE_MAP()


// human_help_dlg ��Ϣ�������


#define PUSH_LINK L"http://www.zhihuiup.com/toGoodsPage/spread?platform=ZQH&code=+Y2j/gRAhSXoHBY1CvDIOY03RIaslIZyLey96qIio4ertbYFqRxKxRJ+HDpumEd3GNEbtvq3GkRFOQlFJj6RSi5ejiKR3KI1JR3Pxn+YPsc7mbCtj2uaoHdoqiOsynN+62k66jpvQG+jx4ISK493NaEUoLOwL8xtzMFrVStFwf8BfNubCvY14A=="
#define PUSH_LINK2 L"http://www.zhihuiup.com/toGoodsPage/spread?platform=ZQH&code=+Y2j/gRAhSVKXsbzT3n9Wezxeher/rGoUMOgyXyL7LWsQWhKr+1P8cvg6nlGBxHBYRnqqUuEU0v7t8p6pfZqsSH62ZxhYhgnnA4OQaFyK4DSXa/C5jgzNWTdYNEWzbjccM3WHiXhWrzqw/QBGt61SPB9j9G6wg66JGoOg+/RxPriYl5a59jwqw=="

void human_help_dlg::OnStnClickedStaticBuyLink1()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������

    ::ShellExecute(NULL, NULL, PUSH_LINK, NULL, NULL, SW_SHOWNORMAL);
}


void human_help_dlg::OnStnClickedStaticBuyLink2()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������

    ::ShellExecute(NULL, NULL, PUSH_LINK2, NULL, NULL, SW_SHOWNORMAL);
}


BOOL human_help_dlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    CString text; 

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    GetDlgItemText(IDC_STATIC_BUY_LINK1, text);

    text += L"<a style='color:#df3434; font-weight:bold;'></a>";

    push_link.SubclassDlgItem(IDC_STATIC_BUY_LINK1, this);
    push_link.SetText(text);

    GetDlgItemText(IDC_STATIC_BUY_LINK2, text);

    text += L"<a style='color:#df3434; font-weight:bold;'></a>";

    push_link2.SubclassDlgItem(IDC_STATIC_BUY_LINK2, this);
    push_link2.SetText(text);
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // �쳣: OCX ����ҳӦ���� FALSE
}
