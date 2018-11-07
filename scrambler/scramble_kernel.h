#ifndef __SCRAMBLE_KERNEL_H__
#define __SCRAMBLE_KERNEL_H__

typedef struct _RETURN_INFO
{
	LRESULT return_code; 
	wstring message; 
} RETURN_INFO, *PRETURN_INFO; 

#define ERROR_NEXT_HTML_ACTION_NOT_FOUND                  0xe1038021

#define LOCATE_TO_NONE 0x00000000
#define LOCATE_TO_FIRST_SIBLING_ITEM 0x00000001
#define LOCATE_TO_FIRST_SUB_ITEM 0x00000002
#define LOCATE_TO_NEXT_SIBLING_ITEM 0x00000003
#define LOCATE_TO_JUMP_TO_ITEM 0x00000004
#define LOCATE_TO_PARENT_NEXT_SIBLING_ITEM 0x00000005
#define NEXT_HTML_ACTION_DELAY 20

#define INVALID_JUMP_TO_ID 0xffffffff

LRESULT WINAPI locate_html_element_from_xpath( HTML_ELEMENT_GROUP *element_group, 
	XPATH_PARAMS *xpaths[], 
	ULONG xpath_count, 
	HTML_ELEMENT_GROUP *group, 
	LPCWSTR target_xpath, 
	HWND notify_wnd ); 

LRESULT WINAPI get_html_elements_from_xpath( LPCWSTR xpath, 
	IHTMLDocument2 *html_doc, 
	HTML_ELEMENT_GROUP *group, 
	BOOLEAN xpath_trace ); 

LRESULT WINAPI get_target_html_elements( HTML_PAGE_INFO *page, 
	IHTMLDocument2 *html_doc, 
	BOOLEAN analyze_xpath); 

LRESULT CALLBACK _analyze_html_element_action_response( HTML_ELEMENT_ACTION *action, 
	HTML_ACTION_CONTEXT *action_context, 
	PVOID data_in, 
	ULONG data_in_size, 
	RETURN_INFO *return_info ); 

LRESULT CALLBACK analyze_html_element_action_response( HTML_ELEMENT_ACTION *root, 
	HTML_ELEMENT_ACTION *action, 
	HTML_ACTION_CONTEXT *action_context, 
	PVOID data_in, 
	ULONG data_in_size, 
	RETURN_INFO *return_info ); 

LRESULT WINAPI execute_web_broswer_manage_command( PVOID data, ULONG data_size ); 
LRESULT WINAPI get_open_page_url_from_source(HTML_ELEMENT_ACTION *action, wstring &string); 

#endif //__SCRAMBLE_KERNEL_H__