/*
 * 
 * Copyright (c) 2003, Michael Carruth All rights reserved.
 * This file is a part of CrashRpt library.
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

#ifndef __EXTERNAL_LINK_H__
#define __EXTERNAL_LINK_H__

#include "webbrowser2.h"
#include "data_scramble.h"

typedef enum _CLIENT_REQUEST_COMMAND
{
	REQUEST_SCRAMBLE_CONFIG, 
	RESPONSE_SCRABLED_DATA, 
	MAX_CLIENT_REQUEST_COMMAND, 
} CLIENT_REQUEST_COMMAND, *PCLIENT_REQUEST_COMMAND; 

#define HTML_NEXT_LINK_NEED_CLICK L"click:"
#define HTML_ELEMENT_REQUEST_NEXT_ACTION L"next_action"
#define HTML_ELEMENT_REQUEST_NEXT_ACTION_A "next_action"

LRESULT WINAPI init_scramble_info( HTML_LIST_ELEMENT_SCRAMBLE_INFO *scramble_info); 
LRESULT WINAPI uninit_page_content_info( HTML_PAGE_CONTENT *page_content ); 
LRESULT WINAPI uninit_scramble_info(HTML_LIST_ELEMENT_SCRAMBLE_INFO *scramble_info); 
LRESULT WINAPI uninit_scramble_infos(); 
LRESULT WINAPI load_scramble_infos(); 
LRESULT WINAPI _load_scramble_info_from_file( LPCWSTR file_name ); 
LRESULT WINAPI load_scramble_info_from_file( LPCWSTR file_name, 
											HTML_LIST_ELEMENT_SCRAMBLE_INFO *scramble_info); 
LRESULT WINAPI select_scramble_info( LPCWSTR url, HTML_LIST_ELEMENT_SCRAMBLE_INFO **info ); 
LRESULT WINAPI save_scarmble_info( LPCWSTR file_name, 
								  HTML_LIST_ELEMENT_SCRAMBLE_INFO *scramble_info); 

/***************************************************************************
HTML�����1�汾��
1.��һ����ҳ��ץȡ��ҳ��������е����ӡ�
2.��������Ҫ�����Ӵ򿪡�
3.���򿪺����ҳ����ȷ����Ҫ����ץȡ����������ԭʼ���ݡ�
4.��ĳ����ʽ����ѭ����
5.�����е��������ض��ĸ�ʽ����������

***************************************************************************/
HRESULT WINAPI scramble_web_page_content_work(IHTMLDocument2 *page, 
								  HTML_PAGE_CONTENT *contents ); 

HRESULT WINAPI scramble_external_links( IHTMLDocument2 *page, 
									   EXTERMAL_LINK_INFO *link_info, 
									   LINK_LIST *links, 
									   BOOLEAN analyze_xpath); 

HRESULT WINAPI html_scramble( CWebBrowser2 *browser, HTML_LIST_ELEMENT_SCRAMBLE_INFO *scramble_info ); 

HRESULT WINAPI html_scramble_ex( CWebBrowser2 *browser, 
								LPCWSTR url ); 

HRESULT WINAPI locate_to_url( CWebBrowser2 *browser, 
								 LPCWSTR url ); 
HRESULT WINAPI html_scramble_click_next( CWebBrowser2 *browser, HTML_LIST_ELEMENT_SCRAMBLE_INFO *scramble_info ); 
HRESULT WINAPI scramble_web_page_content_ex(CWebBrowser2 *browser, 
											LPCWSTR url ); 

HRESULT WINAPI _scramble_web_page_content(CWebBrowser2 *browser, 
										 HTML_PAGE_CONTENT *contents ); 

HRESULT WINAPI scramble_web_page_content(CWebBrowser2 *browser, HTML_PAGE_CONTENT *contents ); 

HRESULT WINAPI get_children_image_element( IHTMLElement *element, HTML_ELEMENT_GROUP *group_out ); 

LRESULT WINAPI _get_children_image_element( HTML_ELEMENT_GROUP *group, HTML_ELEMENT_GROUP *group_out ); 

ULONG CALLBACK web_page_work( PVOID param ); 

#define HTML_ACTION_WORK_RUN_ACTION 0
#define HTML_ACTION_WORK_LOCATE_TO_PAGE 6

HRESULT WINAPI locate_to_url( CWebBrowser2 *browser, 
							 LPCWSTR url ); 

HRESULT WINAPI start_worker( PVOID param ); 

LRESULT WINAPI get_image_file_name_url( LPCWSTR url, 
									   LPWSTR file_name, 
									   ULONG cc_buf_len, 
									   ULONG *cc_ret_len ); 

LRESULT WINAPI save_list_scrambled( LPCWSTR file_name, vector< wstring > &url_list ); 

HRESULT WINAPI is_effective_html_element( IHTMLElement *html_element, BOOLEAN *is_valid ); 

HRESULT WINAPI click_next_link_button( IHTMLElement *html_element ); 

HRESULT WINAPI get_html_element_image_files(IHTMLElement *html_element, vector<wstring> &image_urls, LPCWSTR file_name_pattern );

HRESULT WINAPI get_html_element_image_file(IHTMLElement *html_element, wstring &image_url, LPCWSTR file_name_pattern);

LRESULT WINAPI save_ie_cache_file(LPCWSTR url); 

LRESULT WINAPI get_image_file_name_url(LPCWSTR url,
    LPWSTR file_name,
    ULONG cc_buf_len,
    ULONG *cc_ret_len); 

#endif //__EXTERNAL_LINK_H__