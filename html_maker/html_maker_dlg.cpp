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

// NetWorkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <strsafe.h>
#include <mshtml.h>
#include <comutil.h>
#include <comdef.h>
#include <comdefsp.h>
#include "ie_auto.h"
#include "html_maker_app.h"
#include "html_maker_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <map> 

typedef map< wstring, wstring > XPATH_PARAMS; 
typedef XPATH_PARAMS::iterator XPATH_PARAM_ITERATOR; 
typedef pair< wstring, wstring > XPATH_PARAM_PAIR; 


HTML_WEB_SITE_INFOS target_html_sites; 

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// html_maker_dlg �Ի���

html_maker_dlg::html_maker_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(html_maker_dlg::IDD, pParent)
	, config_file_name( _T("") )
{
	HRESULT hr; 
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hr = CoInitializeEx( NULL, COINIT_SPEED_OVER_MEMORY | COINIT_MULTITHREADED ); 
	if( FAILED( hr ) )
	{
		com_inited = FALSE; 
	}
	else
	{
		com_inited = TRUE; 
	}

	init_ie_auto(); 
}

html_maker_dlg::~html_maker_dlg()
{
	uninit_ie_auto(); 

	if( TRUE == com_inited )
	{
		CoUninitialize(); 
	}
}

void html_maker_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONFIG_FILE_NAME, config_file_name );
	DDX_Control(pDX, IDC_LIST_HTML_PAGE, html_page_list);
}

BEGIN_MESSAGE_MAP(html_maker_dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_AUTO_RUN, &html_maker_dlg::OnBnClickedButtonAutoRun)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &html_maker_dlg::OnBnClickedButtonOpenFile)
	
END_MESSAGE_MAP()


// html_maker_dlg ��Ϣ�������

LRESULT html_maker_dlg::auto_run_on_html()
{
	LRESULT ret = ERROR_SUCCESS; 
	INT32 item_count; 
	INT32 i; 
	ULONG item_index; 
	HTML_WEB_SITE_INFOS select_html_configs; 

	do 
	{
		item_count = html_page_list.GetItemCount(); 

		for( i = 0; i < item_count; i ++ )
		{
			do 
			{

				if( FALSE == html_page_list.GetCheck( i ) )
				//if( LVIS_SELECTED != html_page_list.GetItemState( i, LVIS_SELECTED ) )
				{
					break; 
				}

				item_index = html_page_list.GetItemData( i ); 

#define INVALID_HTML_CONFIG_INDEX ( ULONG )( -1 ) 

				if( item_index == INVALID_HTML_CONFIG_INDEX )
				{
					break; 
				}

				if( item_index >= target_html_sites.size() )
				{
					break; 
				}

				select_html_configs.push_back( target_html_sites[ item_index ] ); 
			}while( FALSE ); 
		}

		ret = ie_auto_execute_on_sites( &select_html_configs ); 
		if( ret != ERROR_SUCCESS )
		{
			break; 
		}

		//if the work thread is not exit, then can't delete the site informations.
	}while( FALSE );

	return ret; 
}

LRESULT html_maker_dlg::init_html_config_ui()
{
	LRESULT ret = ERROR_SUCCESS; 
	INT32 _ret; 
	ULONG colume_index = 0; 

	do
	{
		_ret = html_page_list.InsertColumn( colume_index ++, _T("����"), LVCFMT_LEFT, 120);
		if( _ret < 0 )
		{
			SAFE_SET_ERROR_CODE( ret ); 
		}

		_ret = html_page_list.InsertColumn( colume_index ++, _T("����"), LVCFMT_LEFT, 100);
		if( _ret < 0 )
		{
			SAFE_SET_ERROR_CODE( ret ); 
		}

		html_page_list.SendMessage( LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP | LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES|LVS_SHOWSELALWAYS);
	}while( FALSE ); 
	return ret; 
}

LRESULT html_maker_dlg::load_html_config_files_from_work_dir()
{
	LRESULT ret = ERROR_SUCCESS; 
	UINT32 _ret; 
	WCHAR file_name[ MAX_PATH ]; 
	WCHAR app_path[ MAX_PATH ]; 

	ULONG app_path_len; 
	INT32 Ret = 0; 
	HANDLE hFindHandle = INVALID_HANDLE_VALUE; 
	LPWIN32_FIND_DATAW FindData = NULL; 
	LPWSTR ScanFilePath = NULL; 
	DWORD PathLength; 

	do 
	{
		//_ret = GetDlgItemTextW( IDC_EDIT_CONFIG_FILE_NAME, file_name, ARRAYSIZE( file_name ) ); 
		//if( _ret == 0 
		//	|| _ret >= ARRAYSIZE( file_name ) )
		//{
		//	break; 
		//}

		ret = get_app_path( app_path, ARRAYSIZE( app_path ), &app_path_len ); 
		if( ret != ERROR_SUCCESS )
		{
		}

		PathLength = wcslen( app_path ); 

		if( PathLength == 0 
			|| PathLength >= MAX_PATH )
		{
			Ret = ERROR_INVALID_PARAMETER; 
			goto _return; 
		}

			ScanFilePath = ( LPWSTR )malloc( ( MAX_PATH << 1 ) );
			if( ScanFilePath == NULL )
			{
				Ret = ERROR_NOT_ENOUGH_MEMORY; 
				goto _return; 
			}

			memset( ScanFilePath, 0, ( MAX_PATH << 1 ) ); 

			FindData = ( LPWIN32_FIND_DATAW )malloc( sizeof( WIN32_FIND_DATAW ) ); 
			if( FindData == NULL ) 
			{
				Ret = ERROR_NOT_ENOUGH_MEMORY; 
				goto _return; 
			}

			//memset( FindData, 0, sizeof( WIN32_FIND_DATAW ) ); 
			hFindHandle = FindFirstFileW( app_path, FindData ); 

			if( hFindHandle == INVALID_HANDLE_VALUE )
			{
				Ret = ERROR_ERRORS_ENCOUNTERED; 
				goto _return; 
			}

			for (;;)
			{
				if( FindData->dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT )
				{
					goto _find_next_file; 
				}

				if( FindData->cFileName[ 0 ] != L'.' )
				{
					memcpy( ScanFilePath, app_path, ( ( PathLength - 1 ) << 1 ) ); 
					ScanFilePath[ PathLength - 1 ] = L'\0'; 

					if( wcslen( FindData->cFileName ) + wcslen( ScanFilePath ) + 6 > MAX_PATH )
					{
						goto _find_next_file; 
					}

					if( FindData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
					{
						//wcscat_s( ScanFilePath, MAX_PATH, FindData->cFileName ); 
						//wcscat_s( ScanFilePath, MAX_PATH, L"\\" ); 
						//wcscat_s( ScanFilePath, MAX_PATH, L"*" ); 
						//wcscat_s(ScanFilePath,MAX_PATH,L"\0");
					}
					else
					{
						memcpy( ScanFilePath, app_path, ( ( PathLength - 1 ) << 1 ) ); 
						ScanFilePath[ PathLength - 1 ] = L'\0'; 

						wcscat_s( ScanFilePath, MAX_PATH, FindData->cFileName ); 
						wcscat_s(ScanFilePath,MAX_PATH,L"\0");

						ret = load_html_site_infos( &target_html_sites, file_name ); 
						if( ret != ERROR_SUCCESS )
						{
							break; 
						}
					}
				}
				else
				{
					if( !( FindData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
					{
						memcpy( ScanFilePath, app_path, ( ( PathLength - 1 ) << 1 ) ); 
						ScanFilePath[ PathLength - 1 ] = L'\0'; 

						wcscat_s( ScanFilePath, MAX_PATH, FindData->cFileName ); 
						wcscat_s(ScanFilePath,MAX_PATH,L"\0");

						ret = load_html_site_infos( &target_html_sites, file_name ); 
						if( ret != ERROR_SUCCESS )
						{
							break; 
						}
					}
				}

_find_next_file:
				memset( FindData, 0, sizeof( WIN32_FIND_DATAW ) ); 
				if( FindNextFileW( hFindHandle, FindData ) == FALSE ) 
				{
					break;
				}
			}
_return: 		

		if( hFindHandle != INVALID_HANDLE_VALUE )
		{
			FindClose( hFindHandle );
		}

		if( ScanFilePath != NULL )
		{
			free ( ScanFilePath ); 
		}

		if( FindData != NULL )
		{
			free( FindData ); 
		}

	}while( FALSE ); 

	return ret; 
}

LRESULT html_maker_dlg::load_html_config_files_from_record()
{
	LRESULT ret = ERROR_SUCCESS; 
	UINT32 _ret; 
	WCHAR file_name[ MAX_PATH ]; 
	WCHAR app_path[ MAX_PATH ]; 
	ULONG app_path_len; 

	do 
	{
		//_ret = GetDlgItemTextW( IDC_EDIT_CONFIG_FILE_NAME, file_name, ARRAYSIZE( file_name ) ); 
		//if( _ret == 0 
		//	|| _ret >= ARRAYSIZE( file_name ) )
		//{
		//	break; 
		//}

		ret = get_app_path( app_path, ARRAYSIZE( app_path ), &app_path_len ); 
		if( ret != ERROR_SUCCESS )
		{
		}

		//GetPrivateProfileStringW()
	}while( FALSE ); 

	return ret; 
}

BOOL html_maker_dlg::OnInitDialog()
{
	LRESULT ret; 
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ret = init_html_config_ui(); 

	//{
	//	ret = load_html_config_files(); 
	//}

//#ifdef _DEBUG
//	SetDlgItemTextW( IDC_EDIT_CONFIG_FILE_NAME, L"N:\\work\\html_maker\\Debug\\html_page_config\\http___dzh.mop.com_subject_add" ); 
//	load_html_auto_config_file( L"N:\\work\\html_maker\\Debug\\html_page_config\\http___dzh.mop.com_subject_add" ); 
//	OnBnClickedButtonAutoRun(); 
//#endif //_DEBUG

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void html_maker_dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void html_maker_dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR html_maker_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void html_maker_dlg::OnBnClickedButtonAutoRun()
{
	LRESULT ret; 
	HRESULT hr; 
	//BOOLEAN com_inited = FALSE; 

	do 
	{
		UpdateData( TRUE );

		if( config_file_name.IsEmpty() )	
		{
			::MessageBox( GetSafeHwnd(), TEXT( "������HTML�Զ��������ļ�·��" ), NULL, 0 ); 

			break; 
		}

		com_inited = TRUE; 

		ret = html_auto_on_web_site(); 

		if( ERROR_SUCCESS != ret )
		{
			break; 
		}
	}while( FALSE ); 

	//if( TRUE == com_inited )
	//{
	//	CoUninitialize(); 
	//}
}

/**************************************************************************
html�Զ������������������:
1.Ԫ��A
2.Ԫ��INPUT
3.Ԫ��BUTTON
һ������ϵͳ������HTML��ͨ�Ź��̡�

ʹ��HTTP POST�ķ�����������Ӧ��ҳԪ�صı仯�����ջ�����Ҫ��ҳԪ�صĽ������ܡ�

HTTP�����Զ������̣�
1.IE��һ����ҳ
2.���ҵ�INPUTԪ�أ�������������
2.���ҵ�AԪ�أ��ҳ���HREFĿ����ҳ�������Ŀ����ҳ��·������λ��Ŀ����ҳ
3.���ҵ�BUTTONԪ�أ�������е��������
**************************************************************************/
LRESULT html_maker_dlg::html_auto_on_web_site()
{
	LRESULT ret = ERROR_SUCCESS; 
	//UINT32 _ret; 

	do 
	{
		if( 0 == target_html_sites.size() )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		ret = auto_run_on_html(); 

	}while( FALSE );

	return ret; 
}

//LRESULT WINAPI filter_html_element_from_page_info( IHTMLElementCollection *elements, 
//												  HTML_PAGE_INFO *page, 
//												  HTML_ELEMENT_GROUP *group )
//{
//	LRESULT ret = ERROR_SUCCESS; 
//	HRESULT hr; 
//	HTML_ELEMENT_INFO_ITERATOR it; 
//	IDispatchPtr sub_element_disp; 
//	IHTMLElementCollectionPtr sub_elements; 
//	IHTMLElementPtr sub_element; 
//
//	_bstr_t text; 
//	_variant_t name; 
//	_variant_t index; 
//
//	BOOLEAN element_located = FALSE; 
//
//	do 
//	{
//		ASSERT( NULL != elements ); 
//		ASSERT( NULL != page ); 
//		ASSERT( NULL != group ); 
//
//		/************************************************************************
//		���ٶ�λԪ�ع��˷�������:
//		1.��Ԫ�ص��ܷ�Χ�������ƣ�ͨ��NAME��PATH��С��Χ��
//		1.�ж��Ƿ����е�Ԫ����Ϣ������ID��NAME
//		2.��������������е���Ϣʹ��ITEM�����е�INDEX�������й���
//		3.�����Ԫ�ز���������ͨ��·�����й���
//		4.�����Ԫ�ز�����������·�������Խ��о�ȷ���ˣ���������Ϲ���Ԫ������
//		
//		************************************************************************/
//		for( it = page->elements.begin(); 
//			it != page->elements.end(); 
//			it ++ )
//		{
//			do 
//			{
//				if( ( *it )->id.length() != 0 ) 
//				{
//					text = ( *it )->id.c_str(); 
//					name = text.GetBSTR(); 
//				}
//
//				if( ( *it )->name.length() != 0 )
//				{
//					text = ( *it )->name.c_str(); 
//					name = text.GetBSTR(); 
//				}
//
//				element_located = TRUE; 
//
//				V_VT( &index ) = VT_I4;
//				V_I4( &index ) = 0; 
//
//				hr = elements->item( name, index, &sub_element_disp ); 
//				if( S_OK != hr )
//				{
//					ret = ERROR_ERRORS_ENCOUNTERED; 
//					break; 
//				}
//
//				hr = sub_element_disp->QueryInterface( IID_IHTMLElementCollection, ( PVOID* )&sub_elements ); 
//				if( S_OK != hr 
//					|| sub_elements == NULL )
//				{
//
//					hr = sub_element_disp->QueryInterface( IID_IHTMLElement, ( PVOID* )&sub_element ); 
//					if( S_OK != hr 
//						|| sub_element == NULL )
//					{
//						ret = ERROR_ERRORS_ENCOUNTERED; 
//						break; 
//					}
//				}
//
//				if( NULL != sub_element )
//				{
//					sub_element.AddRef(); 
//					group->push_back( sub_element ); 
//				}
//				else if( NULL != sub_elements )
//				{
//					LONG sub_element_count; 
//					LONG i; 
//
//					hr = sub_elements->get_length( &sub_element_count ); 
//					if( FAILED( hr ) ) 
//					{
//						ret = ERROR_ERRORS_ENCOUNTERED; 
//						break; 
//					}
//
//					for( i = 0; i < sub_element_count; i ++ )
//					{
//						do 
//						{
//							V_VT( &name ) = VT_I4;
//							V_I4( &name ) = i; 
//
//							//comment it.
//							V_VT( &index ) = VT_I4;
//							V_I4( &index ) = 0; 
//
//							hr = elements->item( name, index, &sub_element_disp ); 
//							if( S_OK != hr )
//							{
//								ret = ERROR_ERRORS_ENCOUNTERED; 
//								break; 
//							}
//
//							hr = sub_element_disp->QueryInterface( IID_IHTMLElement, ( PVOID* )&sub_element ); 
//							if( S_OK != hr 
//								|| sub_element == NULL )
//							{
//								ret = ERROR_ERRORS_ENCOUNTERED; 
//								break; 
//							}
//
//							sub_element.AddRef(); 
//							group->push_back( sub_element ); 
//						}while( FALSE ); 
//					}
//				}
//			}while( FALSE ); 
//
//			if( TRUE == element_located )
//			{
//				break; 
//			}
//
//			if( ( *it )->xpath.length() == 0 )
//			{
//				break; 
//			}
//
//			do 
//			{
//				IHTMLElementCollectionPtr _sub_elements; 
//				hr = sub_element_disp->QueryInterface( IID_IHTMLElementCollection, ( PVOID* )&_sub_elements ); 
//				if( FAILED( hr ) )
//				{
//					break; 
//				}
//			
//				if( NULL == _sub_elements )
//				{
//					break; 
//				}
//
//				ret = locate_html_element_from_xpath( _sub_elements, ( *it )->xpath.c_str(), group ); 
//				if( ret != ERROR_SUCCESS )
//				{
//					dbg_print( MSG_IMPORTANT, "locate_elements_from_xpath error %u\n", ret ); 
//				}
//			}while( FALSE ); 
//		}
//
//	}while( FALSE );
//
//	return ret; 
//}

LRESULT html_maker_dlg::load_html_auto_config_file( LPCWSTR file_name )
{
	LRESULT ret = ERROR_SUCCESS; 
	INT32 list_item_index; 
	HTML_WEB_SITE_INFO_ITERATOR it; 

	do 
	{
		ASSERT( NULL != file_name ); 
		ret = load_html_site_infos( &target_html_sites, file_name ); 
		if( ret != ERROR_SUCCESS )
		{
			break; 
		}

		html_page_list.DeleteAllItems(); 

		for( it = target_html_sites.begin(); it != target_html_sites.end(); it ++ )
		{
			list_item_index = html_page_list.InsertItem( 0, ( *it )->site_url.c_str(), -1 ); 

			html_page_list.SetItemText(list_item_index,1,( *it )->site_desc.c_str()); 
			html_page_list.SetItemText(list_item_index,2,( *it )->site_desc.c_str()); 

			html_page_list.SetItemData( list_item_index, ( DWORD_PTR )( it - target_html_sites.begin() ) ); 
		}
	}while( FALSE );

	return ret; 
}

void html_maker_dlg::OnBnClickedButtonOpenFile()
{
	// TODO: Add your control notification handler code here

	LRESULT ret; 
	WCHAR file_name[ MAX_PATH ]; 
	WCHAR app_path[ MAX_PATH ]; 
	ULONG cc_ret_len; 

	do 
	{
		ret = get_app_path( app_path, ARRAYSIZE( app_path ), &cc_ret_len ); 
		if( ret != ERROR_SUCCESS )
		{
			break; 
		}

		app_path[ cc_ret_len - 1 ] = L'\0'; 

		*file_name = _T( '\0' ); 

		//_ret = SetCurrentDirectoryW( app_path ); 
		//if( FALSE == _ret )
		//{

		//}

		ret = open_file_dlg( TRUE, NULL, file_name, NULL, app_path ); 
		if( ret < 0 )
		{
			break; 
		}

		if( *file_name != L'\0' )
		{
			SetDlgItemTextW( IDC_EDIT_CONFIG_FILE_NAME, file_name ); 
		}

		ret = load_html_auto_config_file( file_name ); 

	}while( FALSE );

}
