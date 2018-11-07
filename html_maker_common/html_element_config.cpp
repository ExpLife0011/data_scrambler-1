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

#include "stdafx.h"
#include <strsafe.h>
#import "msxml.tlb"
#define XPATH_CREATE
#include "html_xpath.h"
#include "html_element_config.h"
//#include "data_scrambler.h"
#include "input_content.h"
#include "data_scramble.h"
//#include "capture_input_dlg.h"

LRESULT WINAPI save_scarmble_info( LPCWSTR file_name, 
								  HTML_LIST_ELEMENT_SCRAMBLE_INFO *scramble_info)
{
	LRESULT ret = ERROR_SUCCESS; 
	HRESULT hr; 
	MSXML::IXMLDOMDocumentPtr xml_dest_doc;
	MSXML::IXMLDOMElementPtr dest_element; 
	MSXML::IXMLDOMElementPtr sub_element; 

	MSXML::IXMLDOMTextPtr xml_text; 

	_bstr_t text; 
	LPCWSTR _text; 

	VARIANT_BOOL __ret; 

	do
	{
		ASSERT(NULL != file_name ); 
		ASSERT(NULL != scramble_info); 

		ret = make_config_file_exist( file_name, wcslen( file_name ) ); 
		if( ret != ERROR_SUCCESS )
		{
			break; 
		}

		hr = CoCreateInstance(__uuidof( MSXML::DOMDocument ), 
			NULL, 
			CLSCTX_INPROC_SERVER, 
			__uuidof( MSXML::IXMLDOMDocument ), 
			( void** )&xml_dest_doc ); 

		if( hr != S_OK)
		{
			dbg_print( MSG_IMPORTANT, "����KEY XML:��ʼ��XML�ĵ�����ʧ��, %08x", hr);
			ret = hr; 
			break; 
		}

		{
			_bstr_t temp_text; 
			_variant_t _file_name; 

			temp_text = file_name; 
			_file_name = temp_text.GetBSTR(); 

			__ret = xml_dest_doc->load( _file_name ); 
		}

		if( __ret != VARIANT_TRUE )
		{
			MSXML::IXMLDOMParseErrorPtr spParseError;
			_bstr_t bstrReason;

			spParseError = xml_dest_doc->parseError;

			bstrReason = spParseError->reason;

			_text = bstrReason.operator wchar_t*(); 

			if( NULL != _text )
			{
				dbg_print( DBG_MSG_AND_ERROR_OUT, "load xml error %ws(line%u:%u)\n", _text, 
					spParseError->line, 
					spParseError->linepos ); 
			}

			ASSERT( FALSE ); 
			ret = ERROR_INVALID_PARAMETER;
			break;
		}

		hr = xml_dest_doc->get_documentElement( &dest_element ); 
		if (hr != S_OK 
			|| NULL == dest_element )
		{
			ret = ERROR_INVALID_PARAMETER;
			break;
		}

		do
		{
			MSXML::IXMLDOMAttributePtr xml_attr; 

			xml_attr = xml_dest_doc->createAttribute( L"url" ); 
			if( NULL == xml_attr )
			{
				ret = ERROR_ERRORS_ENCOUNTERED; 
				break; 
			}

			text = scramble_info->url.c_str(); 

			xml_text = xml_dest_doc->createTextNode( text ); 
			if( NULL == xml_text )
			{
				ret = ERROR_ERRORS_ENCOUNTERED; 
				break; 
			}

			hr = xml_text->get_text( text.GetAddress() ); 
			if( hr != S_OK )
			{
				break; 
			}

			_text = text.operator const wchar_t*(); 

			if( _text == NULL )
			{
				break; 
			}

			xml_attr->appendChild( xml_text ); 

			dest_element->setAttributeNode( xml_attr ); 
		}while( FALSE ); 

		do
		{
			MSXML::IXMLDOMAttributePtr xml_attr; 

			xml_attr = xml_dest_doc->createAttribute( L"links_xpath" ); 
			if( NULL == xml_attr )
			{
				ret = ERROR_ERRORS_ENCOUNTERED; 
				break; 
			}

			text = scramble_info->link_list_xpath.c_str(); 

			xml_text = xml_dest_doc->createTextNode( text ); 
			if( NULL == xml_text )
			{
				ret = ERROR_ERRORS_ENCOUNTERED; 
				break; 
			}

			hr = xml_text->get_text( text.GetAddress() ); 
			if( hr != S_OK )
			{
				break; 
			}

			_text = text.operator const wchar_t*(); 

			if( _text == NULL )
			{
				break; 
			}

			xml_attr->appendChild( xml_text ); 

			dest_element->setAttributeNode( xml_attr ); 
		}while( FALSE ); 

		{
			MSXML::IXMLDOMAttributePtr xml_attr; 

			xml_attr = xml_dest_doc->createAttribute( L"next_link_xpath" ); 
			if( NULL == xml_attr )
			{
				ret = ERROR_ERRORS_ENCOUNTERED; 
				break; 
			}

			text = scramble_info->next_link_xpath.c_str(); 

			xml_text = xml_dest_doc->createTextNode( text ); 
			if( NULL == xml_text )
			{
				ret = ERROR_ERRORS_ENCOUNTERED; 
				break; 
			}

			hr = xml_text->get_text( text.GetAddress() ); 
			if( hr != S_OK )
			{
				break; 
			}

			_text = text.operator const wchar_t*(); 

			if( _text == NULL )
			{
				break; 
			}

			xml_attr->appendChild( xml_text ); 

			dest_element->setAttributeNode( xml_attr ); 
		}while( FALSE ); 


		HTML_ELEMENT_CONTENTS_ITERATOR it; 
		_variant_t value; 
		_bstr_t _value; 

		it = scramble_info->page_content.element_contents.begin(); 
		for( ; ; )
		{
			if( it == scramble_info->page_content.element_contents.end() )
			{
				break; 
			}

			ASSERT( ( *it ) != NULL ); 

			sub_element = xml_dest_doc->createElement( L"element" ); 
			if( NULL == sub_element )
			{
				break; 
			}

			{
				MSXML::IXMLDOMAttributePtr xml_attr; 

				xml_attr = xml_dest_doc->createAttribute( L"xpath" ); 
				if( NULL == xml_attr )
				{
					ret = ERROR_ERRORS_ENCOUNTERED; 
					break; 
				}

				text = ( *it )->xpath.c_str(); 

				xml_text = xml_dest_doc->createTextNode( text ); 
				if( NULL == xml_text )
				{
					ret = ERROR_ERRORS_ENCOUNTERED; 
					break; 
				}

				hr = xml_text->get_text( text.GetAddress() ); 
				if( hr != S_OK )
				{
					break; 
				}

				_text = text.operator const wchar_t*(); 

				if( _text == NULL )
				{
					break; 
				}

				xml_attr->appendChild( xml_text ); 

				sub_element->setAttributeNode( xml_attr ); 

				_value = ( *it )->name.c_str(); 

				value = _value.GetBSTR(); 
				sub_element->setAttribute( L"name", value.GetVARIANT() );

				dest_element->appendChild( sub_element ); 
			}while( FALSE ); 

			it ++; 
		}

		{
			_bstr_t temp_text; 
			_variant_t _file_name; 

			temp_text = file_name; 
			_file_name = temp_text.GetBSTR(); 

			hr = xml_dest_doc->save( _file_name.GetVARIANT() ); 
			if( FAILED(hr))
			{
				ret = hr; 
				break; 
			}
		}

	}while( FALSE );

	return ret; 
}

LRESULT WINAPI load_scramble_info_from_file( LPCWSTR file_name, HTML_LIST_ELEMENT_SCRAMBLE_INFO *scramble_info)
{
	LRESULT ret = ERROR_SUCCESS; 
	HRESULT hr; 
	MSXML::IXMLDOMDocumentPtr xml_dest_doc;
	MSXML::IXMLDOMElementPtr dest_element; 
	MSXML::IXMLDOMElementPtr sub_element; 
	MSXML::IXMLDOMNamedNodeMapPtr xml_attrs; 
	MSXML::IXMLDOMAttributePtr xml_attr; 
	MSXML::IXMLDOMNodeListPtr xml_node_list; 
	MSXML::IXMLDOMNodePtr _xml_node; 
	MSXML::IXMLDOMTextPtr xml_text; 

	LONG node_count; 
	LONG i; 
	_variant_t node_value; 
	_bstr_t text; 
	LPCWSTR _text; 

	VARIANT_BOOL __ret; 

	do
	{
		ASSERT(NULL != file_name ); 
		ASSERT(NULL != scramble_info); 

		hr = CoCreateInstance(__uuidof( MSXML::DOMDocument ), 
			NULL, 
			CLSCTX_INPROC_SERVER, 
			__uuidof( MSXML::IXMLDOMDocument ), 
			( void** )&xml_dest_doc ); 

		if( hr != S_OK)
		{
			dbg_print( MSG_IMPORTANT, "����KEY XML:��ʼ��XML�ĵ�����ʧ��, %08x", hr);
			ret = hr; 
			break; 
		}

		{
			_bstr_t temp_text; 
			_variant_t _file_name; 

			temp_text = file_name; 
			_file_name = temp_text.GetBSTR(); 

			__ret = xml_dest_doc->load( _file_name ); 
		}

		if( __ret != VARIANT_TRUE )
		{
			MSXML::IXMLDOMParseErrorPtr spParseError;
			_bstr_t bstrReason;

			spParseError = xml_dest_doc->parseError;

			bstrReason = spParseError->reason;

			_text = bstrReason.operator wchar_t*(); 

			if( NULL != _text )
			{
				dbg_print( DBG_MSG_AND_ERROR_OUT, "load xml error %ws(line%u:%u)\n", _text, 
					spParseError->line, 
					spParseError->linepos ); 
			}

			ASSERT( FALSE ); 
			ret = ERROR_INVALID_PARAMETER;
			break;
		}

		hr = xml_dest_doc->get_documentElement( &dest_element ); 
		if (hr != S_OK 
			|| NULL == dest_element )
		{
			ret = ERROR_INVALID_PARAMETER;
			break;
		}

		hr = dest_element->get_attributes( &xml_attrs ); 
		if( S_OK != hr )
		{
			break; 
		}

		text = L"url"; 
		xml_attr = xml_attrs->getNamedItem( text.GetBSTR() ); 
		if( NULL == xml_attr )
		{
			break; 
		}

		hr = xml_attr->get_nodeValue( node_value.GetAddress() ); 
		if( S_OK != hr )
		{
			break; 
		}

		if( node_value.vt != VT_BSTR )
		{
			hr = E_UNEXPECTED; 
			break; 
		}

		text = node_value.bstrVal; 
		_text = text.operator wchar_t*(); 

		if( NULL == _text )
		{
			hr = E_UNEXPECTED; 
			break; 
		}

		scramble_info->url = _text; 

		text = L"links_xpath"; 
		xml_attr = xml_attrs->getNamedItem( text.GetBSTR() ); 
		if( NULL == xml_attr )
		{
			break; 
		}

		hr = xml_attr->get_nodeValue( node_value.GetAddress() ); 
		if( S_OK != hr )
		{
			break; 
		}

		if( node_value.vt != VT_BSTR )
		{
			hr = E_UNEXPECTED; 
			break; 
		}

		text = node_value.bstrVal; 
		_text = text.operator wchar_t*(); 

		if( NULL == _text )
		{
			hr = E_UNEXPECTED; 
			break; 
		}

		scramble_info->link_list_xpath = _text; 

		text = L"next_link_xpath"; 
		xml_attr = xml_attrs->getNamedItem( text.GetBSTR() ); 
		if( NULL == xml_attr )
		{
			break; 
		}

		hr = xml_attr->get_nodeValue( node_value.GetAddress() ); 
		if( S_OK != hr )
		{
			break; 
		}

		if( node_value.vt != VT_BSTR )
		{
			hr = E_UNEXPECTED; 
			break; 
		}

		text = node_value.bstrVal; 
		_text = text.operator wchar_t*(); 

		if( NULL == _text )
		{
			hr = E_UNEXPECTED; 
			break; 
		}

		scramble_info->next_link_xpath = _text; 

		hr = dest_element->get_childNodes( &xml_node_list ); 
		if( S_OK != hr )
		{
			break; 
		}

		hr = xml_node_list->get_length( &node_count ); 
		if( S_OK != hr )
		{
			ret = hr; 
			break; 
		}

		HTML_ELEMENT_CONTENT *element_content = NULL; 
		element_content = new HTML_ELEMENT_CONTENT(); 
		if( NULL == element_content )
		{
			break; 
		}

		element_content->name = L"URL"; 
		scramble_info->page_content.element_contents.push_back( element_content ); 
		element_content = NULL; 

		for( i = 0; i < node_count; i ++ )
		{
			do 
			{
				element_content = new HTML_ELEMENT_CONTENT(); 
				if( NULL == element_content )
				{
					break; 
				}

				hr = xml_node_list->get_item( i, &_xml_node ); 
				if( S_OK != hr )
				{
					break; 
				}

				hr = _xml_node->get_attributes( &xml_attrs ); 
				if( S_OK != hr )
				{
					break; 
				}

				text = L"xpath"; 

				xml_attr = xml_attrs->getNamedItem( text.GetBSTR() ); 
				if( NULL == xml_attr )
				{
					break; 
				}

				hr = xml_attr->get_nodeValue( &node_value ); 
				if( S_OK != hr )
				{
					break; 
				}

				text  = node_value.bstrVal; 

				_text = text.operator wchar_t*(); 

				if( NULL == _text )
				{
					break; 
				}

				element_content->xpath = _text; 

				text = L"name"; 
				xml_attr = xml_attrs->getNamedItem( text.GetBSTR() ); 
				if( NULL == xml_attr )
				{
					break; 
				}

				hr = xml_attr->get_nodeValue( &node_value ); 
				if( S_OK != hr )
				{
					break; 
				}

				text = node_value.bstrVal; 

				_text = text .operator const wchar_t*(); 

				if( NULL == _text )
				{
					break; 
				}

				element_content->name = _text; 
				scramble_info->page_content.element_contents.push_back( element_content ); 
				element_content = NULL; 

			}while( FALSE );
		
			if( NULL != element_content )
			{
				delete element_content; 
			}
		}
	}while( FALSE ); 

	return ret; 
}

LRESULT WINAPI find_page_group_config( LPCWSTR file_name, 
									  LPCWSTR domain_name, 
									  MSXML::IXMLDOMDocument **xml_doc_out, 
									  MSXML::IXMLDOMElement **site_element_out )
{
	LRESULT ret = ERROR_SUCCESS; 
	HRESULT hr; 
	MSXML::IXMLDOMDocumentPtr _xml_doc; 
	MSXML::IXMLDOMProcessingInstructionPtr xml_instruction; 
	MSXML::IXMLDOMElementPtr xml_root_element = NULL; 
	MSXML::IXMLDOMNodeListPtr xml_node_list = NULL; 
	MSXML::IXMLDOMElementPtr xml_element = NULL; 
	MSXML::IXMLDOMNodePtr xml_node; 
	MSXML::IXMLDOMNodePtr xml_attr; 
	MSXML::IXMLDOMNamedNodeMapPtr xml_attrs; 
	INT32 i; 

	LONG node_count; 
	VARIANT_BOOL __ret; 

	_bstr_t temp_text; 
	LPCWSTR _temp_text; 

	_variant_t node_value; 
	BOOLEAN node_found = FALSE; 

	do
	{
		ASSERT( NULL != file_name ); 
		ASSERT( NULL != domain_name ); 
		ASSERT( NULL != xml_doc_out ); 
		ASSERT( NULL != site_element_out ); 

		*xml_doc_out = NULL; 
		*site_element_out = NULL; 

		hr = CoCreateInstance(__uuidof( MSXML::DOMDocument ), 
			NULL, 
			CLSCTX_INPROC_SERVER, 
			__uuidof( MSXML::IXMLDOMDocument ), 
			( void** )&_xml_doc ); 
		if( hr != S_OK)
		{
			dbg_print( MSG_IMPORTANT, "create xml document error %08x", hr);
			ret = hr; 
			break; 
		}

		__ret = _xml_doc->load( ( WCHAR* )file_name ); 

		if( __ret != VARIANT_TRUE )
		{
			MSXML::IXMLDOMParseErrorPtr spParseError;
			_bstr_t bstrReason;

			spParseError = _xml_doc->parseError;

			bstrReason = spParseError->reason;

			_temp_text = bstrReason.operator wchar_t*(); 

			if( NULL != _temp_text )
			{
				dbg_print( DBG_MSG_AND_ERROR_OUT, "load xml error %ws\n", _temp_text ); 
			}

			ret = ERROR_INVALID_PARAMETER; 
			break; 		
		}

		xml_root_element = _xml_doc->documentElement; 
		if( xml_root_element == NULL ) 
		{
			ret = ERROR_INVALID_PARAMETER; 
			log_trace_ex( MSG_IMPORTANT, " documentElement invalid\n" );
			break; 
		}

		//�Ƿ����ֱ��ʹ��XPATHֱ�Ӳ�ѯ���Խ��ж�λ
		hr = xml_root_element->get_childNodes( &xml_node_list ); 
		if( S_OK != hr )
		{
			break; 
		}

		hr = xml_node_list->get_length( &node_count ); 
		if( S_OK != hr )
		{
			ret = hr; 
			break; 
		}

		for( i = 0; i < node_count; i ++ )
		{
			do 
			{
				hr = xml_node_list->get_item( i, &xml_node ); 
				if( S_OK != hr )
				{
					break; 
				}

				hr = xml_node->get_attributes( &xml_attrs ); 
				if( S_OK != hr )
				{
					break; 
				}

				temp_text = domain_name; 

				xml_attr = xml_attrs->getNamedItem( temp_text.GetBSTR() ); 
				if( NULL == xml_attr )
				{
					break; 
				}

				hr = xml_attr->get_nodeValue( &node_value ); 
				if( S_OK != hr )
				{
					break; 
				}

				temp_text = node_value.bstrVal; 

				_temp_text = temp_text.operator const wchar_t*(); 

				if( NULL == _temp_text )
				{
					break; 
				}

				if( 0 == _wcsicmp( _temp_text, domain_name ) )
				{
					hr = xml_node->QueryInterface( IID_IXMLDOMElement, ( PVOID* )&xml_element ); 
					if( hr != S_OK )
					{
						break; 
					}

					node_found = TRUE; 
					break; 
				}
			}while( FALSE );

			if( TRUE == node_found )
			{
				break; 
			}
		}

		if( TRUE == node_found )
		{
			break; 
		}

		xml_element = _xml_doc->createElement( L"site" ); 

		if( NULL == xml_element )
		{
			log_trace_ex( MSG_IMPORTANT, "create the root element of the document error 0x%0.8x\n", hr ); ;
			ret = hr; 
			break; 
		}

		temp_text = domain_name; 
		xml_element->setAttribute( L"url", temp_text );

		xml_root_element->appendChild( xml_element );

		_xml_doc->AddRef(); 
		xml_element->AddRef(); 

		*xml_doc_out = _xml_doc; 
		*site_element_out = xml_element; 

	}while( FALSE ); 

	return ret; 
}

LRESULT WINAPI add_page_config( MSXML::IXMLDOMDocument *xml_doc, 
	LPCWSTR url, 
	MSXML::IXMLDOMElement *site_node, 
	MSXML::IXMLDOMElement **page_node )
{
	LRESULT ret = ERROR_SUCCESS; 
	MSXML::IXMLDOMElementPtr xml_node = NULL; 

	_bstr_t temp_text; 

	do
	{
		ASSERT( NULL != url ); 
		ASSERT( NULL != xml_doc ); 
		ASSERT( NULL != site_node );
		ASSERT( NULL != page_node ); 

		*page_node = NULL; 

		xml_node = xml_doc->createElement( L"page" ); 

		if( NULL == xml_node )
		{
			log_trace_ex( MSG_IMPORTANT, "����KEY XML:����XML���ڵ�ʧ��");
			ret = ERROR_ERRORS_ENCOUNTERED; 
			break; 
		}

		site_node->raw_appendChild( xml_node, NULL );

		temp_text = url; 

		xml_node->setAttribute( L"url", temp_text);

		xml_node->AddRef(); 
		*page_node = xml_node; 
	}while( FALSE ); 

	return ret; 
}

LRESULT WINAPI insert_node_by_text(MSXML::IXMLDOMDocument *xml_src_doc, MSXML::IXMLDOMElement *dest_node)
{
	LRESULT ret = ERROR_SUCCESS;
	HRESULT hr; 
	_bstr_t temp_text;

	MSXML::IXMLDOMElementPtr xml_element; 
	MSXML::IXMLDOMNodeListPtr child_nodes; 
	MSXML::IXMLDOMNamedNodeMapPtr node_attrs; 
	MSXML::IXMLDOMNodePtr attr; 
	MSXML::IXMLDOMElementPtr parent_node; 

	LONG atrr_count; 
	LONG i; 

	do
	{
		ASSERT(NULL != xml_src_doc);
		ASSERT(NULL != dest_node);

		hr = dest_node->get_nodeName( temp_text.GetAddress() );
		if (S_OK != hr)
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		hr = xml_src_doc->raw_createElement( temp_text.GetBSTR(), &xml_element ); 
		if( S_OK != hr )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		hr = xml_src_doc->get_documentElement( &parent_node ); 
		if( S_OK != hr )
		{
			break; 
		}

		if( NULL == parent_node )
		{
			hr = E_UNEXPECTED; 
			break; 
		}


		hr = dest_node->get_attributes( &node_attrs ); 
		if( S_OK != hr )
		{
			break; 
		}

		hr = node_attrs->get_length( &atrr_count ); 
		if( S_OK != hr )
		{
			ret = hr; 
			break; 
		}

		if( atrr_count == 0 )
		{
			ret = ERROR_ERRORS_ENCOUNTERED; 
			break; 
		}

		_variant_t attr_value; 
		for( i = 0; i < atrr_count; i ++ )
		{
			do 
			{
				hr = node_attrs->get_item( i, &attr ); 
				if( S_OK != hr )
				{
					ret = hr; 
					break; 
				}

				hr = attr->get_nodeName( temp_text.GetAddress() ); 
				if( S_OK != hr )
				{
					ret = hr; 
					break; 
				}

				hr = attr->get_nodeValue( attr_value.GetAddress() ); 
				if( S_OK != hr )
				{
					ret = hr; 
					break; 
				}

				hr = xml_element->setAttribute( temp_text.GetBSTR(), attr_value.GetVARIANT() ); 
				if( S_OK != hr )
				{
					ret = hr; 
					break; 
				}
			}while( FALSE );

		}

		hr = parent_node->appendChild( xml_element ); 
		if( FAILED( hr ) )
		{
			ret = hr; 
			break; 
		}
	} while (FALSE);

	return ret;
}

LRESULT WINAPI inert_xml_text(LPCWSTR src_xml, LPCWSTR dest_xml, LPCWSTR node_xpath, LPWSTR xml_out, ULONG cc_buf_len)
{
	LRESULT ret = ERROR_SUCCESS;
	HRESULT hr;
	MSXML::IXMLDOMDocumentPtr xml_src_doc;
	MSXML::IXMLDOMDocumentPtr xml_dest_doc;

	MSXML::IXMLDOMNodeListPtr node_list;
	MSXML::IXMLDOMNodePtr node;
	MSXML::IXMLDOMNodePtr parent_node;
	MSXML::IXMLDOMElementPtr dest_node;

	MSXML::IXMLDOMElementPtr root_element;

	_bstr_t dest_text;
	_bstr_t temp_text;
	LPCWSTR _temp_text;
	LONG node_count;

	VARIANT_BOOL __ret; 

	do
	{
		ASSERT(NULL != src_xml);
		ASSERT(NULL != dest_xml);
		ASSERT(NULL != node_xpath);

		hr = CoCreateInstance(__uuidof( MSXML::DOMDocument ), 
			NULL, 
			CLSCTX_INPROC_SERVER, 
			__uuidof( MSXML::IXMLDOMDocument ), 
			( void** )&xml_src_doc ); 

		if( hr != S_OK)
		{
			dbg_print( MSG_IMPORTANT, "����KEY XML:��ʼ��XML�ĵ�����ʧ��, %08x", hr);
			ret = hr; 
			break; 
		}

		hr = CoCreateInstance(__uuidof( MSXML::DOMDocument ), 
			NULL, 
			CLSCTX_INPROC_SERVER, 
			__uuidof( MSXML::IXMLDOMDocument ), 
			( void** )&xml_dest_doc ); 

		if( hr != S_OK)
		{
			dbg_print( MSG_IMPORTANT, "����KEY XML:��ʼ��XML�ĵ�����ʧ��, %08x", hr);
			ret = hr; 
			break; 
		}

		__ret = xml_dest_doc->loadXML( ( WCHAR* )dest_xml ); 

		if( __ret != VARIANT_TRUE )
		{
			MSXML::IXMLDOMParseErrorPtr spParseError;
			_bstr_t bstrReason;

			spParseError = xml_dest_doc->parseError;

			bstrReason = spParseError->reason;

			_temp_text = bstrReason.operator wchar_t*(); 

			if( NULL != _temp_text )
			{
				dbg_print( DBG_MSG_AND_ERROR_OUT, "load xml error %ws\n", _temp_text ); 
			}

			ret = ERROR_INVALID_PARAMETER;
			break;
		}

		hr = xml_dest_doc->get_documentElement( &dest_node ); 
		if (hr != S_OK 
			|| NULL == dest_node )
		{
			ret = ERROR_INVALID_PARAMETER;
			break;
		}


		__ret = xml_src_doc->loadXML( ( WCHAR* )dest_xml ); 

		if( __ret != VARIANT_TRUE )
		{
			MSXML::IXMLDOMParseErrorPtr spParseError;
			_bstr_t bstrReason;

			spParseError = xml_src_doc->parseError;

			bstrReason = spParseError->reason;

			_temp_text = bstrReason.operator wchar_t*(); 

			if( NULL != _temp_text )
			{
				dbg_print( DBG_MSG_AND_ERROR_OUT, "load xml error %ws\n", _temp_text ); 
			}

			ret = ERROR_INVALID_PARAMETER;
			break;
		}

		hr = xml_src_doc->get_documentElement(&root_element);
		if (hr != S_OK)
		{
			ret = ERROR_ERRORS_ENCOUNTERED;
			break;
		}

		do
		{
			node_list = root_element->selectNodes( node_xpath );
			if( NULL != node_list )
			{
				parent_node = root_element;
			}

			hr = node_list->get_length(&node_count);
			if (S_OK != hr)
			{
				parent_node = root_element;
			}

			if( node_count <= 0 )
			{
				break; 
			}

			hr = node_list->get_item(node_count - 1, &node);
			if (S_OK != hr)
			{
				ret = ERROR_ERRORS_ENCOUNTERED;
				break;
			}

			hr = node->get_parentNode(&parent_node);

			if (S_OK != hr)
			{
				ret = ERROR_ERRORS_ENCOUNTERED;
				break;
			}
		} while (FALSE);

		if (parent_node == NULL)
		{
			ret = ERROR_ERRORS_ENCOUNTERED;
			break;
		}

		ret = insert_node_by_text(xml_src_doc, dest_node);
		if (ERROR_SUCCESS != ret)
		{
			break;
		}
	} while (FALSE);

	return ret;
}

LRESULT WINAPI add_html_element_config_from_text(  MSXML::IXMLDOMDocument *xml_doc, 
												 LPCWSTR url, 
												 MSXML::IXMLDOMNode *page_node, 
												 IHTMLElement *html_element ) 
{
	LRESULT ret = ERROR_SUCCESS; 
	HRESULT hr; 
	MSXML::IXMLDOMDocumentPtr _xml_doc; 
	MSXML::IXMLDOMElementPtr xml_element = NULL;  // ���ڵ�
	BOOLEAN com_inited = FALSE; 
	_bstr_t text; 

	do 
	{
		ASSERT( url != NULL ); 
		ASSERT( html_element != NULL ); 
		ASSERT( NULL != xml_doc ); 

		_xml_doc = xml_doc; 

		hr = html_element->get_outerText( text.GetAddress() ); 
		if( hr != S_OK )
		{
			ret = hr; 
			break; 
		}
	}while( FALSE );

	return ret; 
}

LRESULT WINAPI format_html_text( wstring html_text, wstring &html_text_out, IHTMLElement *html_element )
{
	LRESULT ret = ERROR_SUCCESS; 
	wstring _html_text; 
	wstring last_attr_name; 

	do 
	{
		if( html_text.length() <= 0 )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		do 
		{
			wstring word; 
			HTML_TEXT_STATE text_state; 
			HTML_WORD_STATE word_state; 
			LONG attr_value_begin; 
			LONG word_begin_pos; 
			LPWSTR _param = NULL; 
			HTML_WORDS tags; 
			HTML_WORDS bug_tags; 
			HTML_WORD_INFORMATION *word_info = NULL;  
			LONG i; 

			do 
			{
				_param = ( LPWSTR )malloc( ( html_text.length() + 1 ) << 1 ); 
				if( NULL == _param )
				{
					ret = ERROR_NOT_ENOUGH_MEMORY; 
					break; 
				}

				memcpy( _param, html_text.c_str(), ( ( html_text.length() + 1 ) << 1 ) ); 

				text_state = HTML_TEXT_BEGIN; 

				word_begin_pos = -1; 
				i = 0; 

				for( ; ; )
				{
					if( i >= ( LONG )html_text.length() )
					{
						if( text_state != HTML_TEXT_BEGIN )
						{
							ret = ERROR_INVALID_PARAMETER; 
						}
						break; 
					}

					switch( _param[ i ] )
					{
					case L'/':
						{
							switch( text_state )
							{
							case HTML_TAG_BEGIN: 
								ASSERT( i >= word_begin_pos ); 
								word_state = HTML_TAG_RIGHT; 
								break; 
							case HTML_ATTIBUTE_STRING_VALUE_BEGIN: 
								break; 
							case HTML_TEXT_BEGIN: 
							case HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END: 
							case HTML_ATTIBUTE_VALUE_OR_NAME_BEGIN: 
							default:
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 
							}
						}
						break; 
					case L'<':
						{
							switch( text_state )
							{
							case HTML_TEXT_BEGIN: 
								ASSERT( i >= word_begin_pos ); 

								text_state = HTML_TAG_BEGIN; 
								word_state = HTML_TAG_LEFT; 

								word_begin_pos = i + 1; 
								_html_text += html_text.at( i ); 
								break; 
							case HTML_TAG_BEGIN: 

								word = html_text.substr( word_begin_pos, i - word_begin_pos ); 
								if( 0 == wcsnicmp( word.c_str(), L"!--", CONST_STR_LEN( L"!--" ) ) )
								{
									LPCWSTR comment_end; 
								
									comment_end = wcsstr( html_text.c_str() + word_begin_pos, L"-->" ); 
									if( comment_end == NULL )
									{
										ret = ERROR_INVALID_PARAMETER; 
										break; 
									}

									_html_text += html_text.substr( word_begin_pos, comment_end - html_text.c_str() - word_begin_pos + 1 ); 
									word_begin_pos = comment_end - html_text.c_str() + 1; 
								
									text_state = HTML_TEXT_BEGIN; 
								}

								break; 
							case HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END: 
							case HTML_ATTIBUTE_VALUE_OR_NAME_BEGIN: 
							case HTML_ATTIBUTE_STRING_VALUE_BEGIN: 
							default:
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 
							}
						}
						break; 
					case L'>':
						{
							switch( text_state )
							{
							case HTML_TAG_BEGIN:  
								//<A a1=1 a2=2 > can receive the entire string in the element now. (A a1=1 a2=2)
								ASSERT( word_begin_pos >= 0 ); 
								ASSERT( i >= word_begin_pos );  

								//TAG
								word = html_text.substr( word_begin_pos, i - word_begin_pos ); 
								_html_text += word; 

								switch( word_state )
								{
								case HTML_TAG_LEFT: 
									{
										word_info = new HTML_WORD_INFORMATION(); 

										if( NULL == word_info )
										{
											ret = ERROR_NOT_ENOUGH_MEMORY; 
											break; 
										}

										word_info->word = word; 
										word_info->word_end = _html_text.length(); 
										word_info->left_end = _html_text.length() + 1; 

										tags.push_back( word_info ); 
										word_info = NULL; 
									}
									break; 

								case HTML_TAG_RIGHT:
									{
										/******************************
										<a><br><c></a>
										******************************/

										word = word.substr( 1, word.length() - 1 ); 

										ret = fix_html_tag_end( word, &tags, &bug_tags ); 
										if( ret != ERROR_SUCCESS )
										{
											dbg_print( MSG_FATAL_ERROR, "check the tag end error %u\n", ret ); 
										}
									}
									break; 
								default:
									ASSERT( FALSE ); 
									break; 
								}

								_html_text += html_text.at( i ); 

								word_begin_pos = i + 1; 
								text_state = HTML_TEXT_BEGIN; 
								break; 

							case HTML_ATTIBUTE_STRING_VALUE_BEGIN: 
							case HTML_ATTIBUTE_VALUE_OR_NAME_BEGIN: 
								ASSERT( word_begin_pos >= 0 ); 
								ASSERT( i >= word_begin_pos ); 

								//<a a=b c d >
								word = html_text.substr( word_begin_pos, i - word_begin_pos ); 
								ret = fix_html_attribute_format( word, word ); 

								_html_text += word; 

								{
									HTML_WORD_ITERATOR it; 

									it = tags.end() - 1; 

									( *it )->left_end = _html_text.length(); 
								}

								_html_text += html_text.at( i ); 

								word_begin_pos = i + 1; 
								text_state = HTML_TEXT_BEGIN; 
								break; 
							case HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END: 

								{
									HTML_WORD_ITERATOR it; 

									it = tags.end() - 1; 

									( *it )->left_end = _html_text.length(); 

									_html_text += html_text.at( i ); 

									word_begin_pos = i + 1; 
									text_state = HTML_TEXT_BEGIN; 
								}
								break; 
							case HTML_TEXT_BEGIN: 
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 
							default:
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 
							}
						}
						break; 
					case L'=':
						{
							switch( text_state )
							{
							case HTML_TAG_BEGIN:  
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 

							case HTML_ATTIBUTE_VALUE_OR_NAME_BEGIN: 
								ASSERT( word_begin_pos >= 0 ); 
								ASSERT( i >= word_begin_pos );  

								{
									ASSERT( word_begin_pos >= 0 ); 
									ASSERT( i >= word_begin_pos );  

									if( i < word_begin_pos )
									{
										ASSERT( FALSE ); 
										log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
										ret = ERROR_ERRORS_ENCOUNTERED; 
										break; 
									}
									else if( i == word_begin_pos )
									{
										ret = ERROR_ERRORS_ENCOUNTERED; 
										break; 
									}
									else if( i - word_begin_pos )
									{
										ASSERT( attr_value_begin >= 0 ); 

										if( word_begin_pos < attr_value_begin )
										{
											ASSERT( FALSE ); 
											ret = ERROR_ERRORS_ENCOUNTERED; 
											break; 
										}
										else if( word_begin_pos == attr_value_begin )
										{
											ASSERT( FALSE ); 
											ret = ERROR_ERRORS_ENCOUNTERED; 
											break; 
										}

										ASSERT( word_begin_pos >= attr_value_begin + 1 ); 

										word = html_text.substr( attr_value_begin, word_begin_pos - attr_value_begin - 1 ); 

										do
										{
											_bstr_t attr_name; 
											_variant_t attr_value; 
											LPCWSTR _text; 
											HRESULT hr; 
											BOOLEAN invalid_type; 

											if( html_element == NULL )
											{
												break; 
											}

											if( last_attr_name.length() == 0 )
											{
												ASSERT( FALSE ); 
												break; 
											}

											attr_name = last_attr_name.c_str(); 

											hr = html_element->getAttribute( attr_name, 2, attr_value.GetAddress() ); 

											if( hr != S_OK )
											{
												break; 
											}
										
											invalid_type = FALSE; 
											switch( attr_value.vt ) 
											{
											case VT_BSTR:
												{
													attr_name = attr_value.bstrVal;
												}
												break; 
											case VT_INT:
											case VT_I4:
												{
													CString text_fmt; 

													text_fmt.Format( L"%d", attr_value.intVal ); 

													attr_name = text_fmt.GetBuffer(); 
												}
												break; 
											case VT_UINT:
											case VT_UI4:
												{
													CString text_fmt; 

													text_fmt.Format( L"%u", attr_value.intVal ); 

													attr_name = text_fmt.GetBuffer(); 
												}
												break; 
											case VT_NULL:
												break; 
											default:
												invalid_type = TRUE; 
												break; 
											}
 
											if( TRUE == invalid_type )
											{
												ASSERT( FALSE ); 
												break; 
											}

											_text = attr_name.operator const wchar_t*(); 
											if( NULL == _text )
											{
												break; 
											}

											if( 0 != wcscmp( _text, word.c_str() ) )
											{
												word = _text; 
											}
										}while( FALSE ); 
										
										ret = fix_html_attribute_format( word, word ); 
										if( ret = ERROR_SUCCESS )
										{
											break; 
										}

										_html_text += word; 

										if( L' ' != _html_text.at( _html_text.length() - 1 ) )
										{
											_html_text += L' '; 
										}

										word = html_text.substr( word_begin_pos, i - word_begin_pos ); 

										wstring_tolower( word ); 
										last_attr_name = word; 

										_html_text += word; 
										_html_text += html_text.at( i ); 
										word_begin_pos = i + 1; 
										attr_value_begin = i + 1; 

										text_state = HTML_ATTIBUTE_VALUE_OR_NAME_BEGIN; 
									}
								}
								break; 
							case HTML_TEXT_BEGIN: 
								// = 
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 
							case HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END: 
								//<A a1=
								{
									ASSERT( word_begin_pos >= 0 ); 
									ASSERT( i >= word_begin_pos );  

									if( L' ' != _html_text.at( _html_text.length() - 1 ) )
									{
										_html_text += L' '; 
									}

									word = html_text.substr( word_begin_pos, i - word_begin_pos ); 
									wstring_tolower( word ); 
									last_attr_name = word; 

									_html_text += word; 
									_html_text += html_text.at( i ); 
									word_begin_pos = i + 1; 
									attr_value_begin = i + 1; 

									text_state = HTML_ATTIBUTE_VALUE_OR_NAME_BEGIN; 
								}
								break; 
							case HTML_ATTIBUTE_STRING_VALUE_BEGIN: 
								if( i < word_begin_pos )
								{
									ASSERT( FALSE ); 
									log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
									ret = ERROR_ERRORS_ENCOUNTERED; 
									break; 
								}

								break; 
							default:
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 
							}
						}
						break; 
					case L' ':
						{
							switch( text_state )
							{
							case HTML_TEXT_BEGIN:  
								word_begin_pos = i + 1; 
								break; 

							case HTML_ATTIBUTE_VALUE_OR_NAME_BEGIN: 
								{
									if( i < word_begin_pos )
									{
										ASSERT( FALSE ); 
										log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
										ret = ERROR_ERRORS_ENCOUNTERED; 
										break; 
									}
									else if( i == word_begin_pos )
									{
										word_begin_pos = i + 1; 
									}
									else if( i - word_begin_pos )
									{
										ASSERT( word_begin_pos >= 0 ); 
										ASSERT( i >= word_begin_pos );  

										word_begin_pos = i + 1; 
										text_state = HTML_ATTIBUTE_VALUE_OR_NAME_BEGIN; 
									}
								}
								break; 
							case HTML_TAG_BEGIN: 
								if( i < word_begin_pos )
								{
									ASSERT( FALSE ); 
									log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
									ret = ERROR_ERRORS_ENCOUNTERED; 
									break; 
								}
								else if( i == word_begin_pos )
								{
									word_begin_pos = i + 1; 
								}
								else if( i - word_begin_pos )
								{
									ASSERT( word_begin_pos >= 0 ); 
									ASSERT( i >= word_begin_pos );  

									//TAG
									word = html_text.substr( word_begin_pos, i - word_begin_pos ); 

									_html_text += word; 

									_html_text += html_text.at( i ); 

									word_begin_pos = i + 1; 
									text_state = HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END; 

									switch( word_state )
									{
									case HTML_TAG_LEFT: 
										{
											word_info = new HTML_WORD_INFORMATION(); 
											
											if( NULL == word_info )
											{
												ret = ERROR_NOT_ENOUGH_MEMORY; 
												break; 
											}

											word_info->word = word; 
											word_info->word_end = _html_text.length(); 
											word_info->left_end = -1; 

											tags.push_back( word_info ); 
											word_info = NULL; 
										}
										break; 

									case HTML_TAG_RIGHT: 
									default:
										ASSERT( FALSE ); 
										break; 
									}
								}

								break; 
							case HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END: 
								{
									if( i < word_begin_pos )
									{
										ASSERT( FALSE ); 
										log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
										ret = ERROR_ERRORS_ENCOUNTERED; 
										break; 
									}
									else if( i == word_begin_pos )
									{
										word_begin_pos = i + 1; 
									}
									else if( i - word_begin_pos )
									{
										ASSERT( word_begin_pos >= 0 ); 
										ASSERT( i >= word_begin_pos );  

										_html_text += html_text.substr( word_begin_pos, i - word_begin_pos ); 

										_html_text += html_text.at( i ); 

										word_begin_pos = i + 1; 
										text_state = HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END; 
									}
								}
								break; 
							case HTML_ATTIBUTE_STRING_VALUE_BEGIN: 
								if( i < word_begin_pos )
								{
									ASSERT( FALSE ); 
									log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
									ret = ERROR_ERRORS_ENCOUNTERED; 
									break; 
								}
								else if( i == word_begin_pos )
								{
									word_begin_pos = i + 1; 
								}
								break; 
							default:
								ret = ERROR_INVALID_PARAMETER; 
								break; 
							}
							break; 
					case L'\"':
						{
							switch( text_state )
							{
							case HTML_TEXT_BEGIN:  
								//   "
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 

							case HTML_ATTIBUTE_VALUE_OR_NAME_BEGIN: 
								_html_text += html_text.at( i ); 
								word_begin_pos = i + 1; 
								text_state = HTML_ATTIBUTE_STRING_VALUE_BEGIN; 
								break; 
							case HTML_TAG_BEGIN: 
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 
							case HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END: 
								{
									log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
									ret = ERROR_INVALID_PARAMETER; 
									break; 
								}
								break; 
							case HTML_ATTIBUTE_STRING_VALUE_BEGIN: 
								if( i < word_begin_pos )
								{
									ASSERT( FALSE ); 
									log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
									ret = ERROR_ERRORS_ENCOUNTERED; 
									break; 
								}
								else if( i == word_begin_pos )
								{
									ASSERT( word_begin_pos >= 0 ); 
									ASSERT( i >= word_begin_pos );  

									_html_text += html_text.at( i ); 

									word_begin_pos = i + 1; 
									text_state = HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END; 
								}
								else if( i - word_begin_pos )
								{
									ASSERT( word_begin_pos >= 0 ); 
									ASSERT( i >= word_begin_pos );  

									_html_text += html_text.substr( word_begin_pos, i - word_begin_pos ); 

									_html_text += html_text.at( i ); 

									word_begin_pos = i + 1; 
									text_state = HTML_ATTIBUTE_NAME_BEGIN_OR_TAG_END; 
								}
								break; 
							default:
								log_trace_ex( MSG_FATAL_ERROR, "format html text error\n" ); 
								ret = ERROR_INVALID_PARAMETER; 
								break; 
							}
						}
						break; 
					default:
						break; 
						}

						if( ret != ERROR_SUCCESS )
						{
							break; 
						}
					}

					if( ret != ERROR_SUCCESS )
					{
						break; 
					}

					i ++; 
				}
			}while( FALSE ); 

			if( NULL != _param)
			{
				free( _param ); 
			}

			{
				HTML_WORD_ITERATOR it; 

				if( ret != ERROR_SUCCESS )
				{
					//partial fixing, that's meaningless.
					break; 
				}

				for( it = bug_tags.begin(); it != bug_tags.end(); it ++ )
				{
					if( ( *it )->left_end < 0 )
					{
						ASSERT( FALSE ); 
						break; 
					}

					ASSERT( ( *it )->left_end < ( LONG )_html_text.length() ); 

					_html_text.insert( _html_text.begin() + ( *it )->left_end, L'/' ); 
				}

				//<A a1="1"> <B b1="1"></B> the A will remain.
				for( it = tags.begin(); it != tags.end(); it ++ )
				{
					do 
					{
						if( ( *it )->left_end < 0 )
						{
							ASSERT( FALSE ); 
							break; 
						}

						ASSERT( ( *it )->left_end < ( LONG )_html_text.length() ); 

						_html_text.insert( _html_text.begin() + ( *it )->left_end, L'/' ); 
					}while( FALSE );
				}
			}
		}while( FALSE ); 


		html_text_out = _html_text; 
	}while( FALSE );

	return ret; 
}

/****************************************************************************************
<IFRAME tabIndex="2" id="e_iframe" class="pt" hideFocus style="HEIGHT: 400px" frameBorder="0"></IFRAME/>
add third character index for the attribute value begin, 
<BODY spellcheck="false" contentEditable="true" style="BORDER-TOP: 0px; HEIGHT: 400px; BORDER-RIGHT: 0px; BORDER-BOTTOM: 0px; BORDER-LEFT: 0px"></BODY/>
****************************************************************************************/

typedef vector<HTML_WORD_INFORMATION*> HTML_WORDS; 
typedef vector<HTML_WORD_INFORMATION*>::iterator HTML_WORD_ITERATOR; 
typedef vector<HTML_WORD_INFORMATION*>::reverse_iterator HTML_WORD_REVERSE_ITERATOR; 

/************************************************************************
fix tag end process:
check the right tag whether is match top tag, if is then the format is 
regular:
<a><b></b></a>
is not then it's not regular:
<a><b></a>
then record the skipped words, appending it a '/'
and pop the word from the stack.
************************************************************************/


/**********************************************************************************
bug html text: 
<INPUT id="u_login_cookie CHECKED" type="checkbox" value="2" name="CookieDate"/> CHECKED???
//*[@id="u_login_cookie"]
<input type="checkbox" id="u_login_cookie" name="CookieDate" value="2">
**********************************************************************************/

/********************************************************************************
reference:
HtmlAgilityPack
JDOM
SgmlReader
XHTML 
EfTidy
Winista.Htmlparser
LibXml2
document.evaluate( ��count(//a[@href])��, document, null, XPathResult.NUMBER_TYPE, null).getNumberValue();
********************************************************************************/
/*******************************************************************************
createDocumentFromUrl
documentElement
execCommand
IHTMLDocument2::elementFromPoint
GetIDsOfNames
*******************************************************************************/

LRESULT WINAPI get_html_element_input_value( IHTMLElement *html_element, wstring &input_value, BOOLEAN &is_input )
{
	LRESULT ret = ERROR_SUCCESS; 
	HRESULT hr; 
	_bstr_t text; 
	LPCWSTR _text; 
	HTML_ELEMENT_TYPE element_type; 

	do 
	{
		ASSERT( NULL != html_element ); 

		input_value = L""; 

		hr = html_element->get_tagName( text.GetAddress() ); 
		if( S_OK != hr )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		_text = text.operator const wchar_t*(); 
		if( NULL == _text )
		{
			ret = ERROR_ERRORS_ENCOUNTERED; 
			break; 
		}

		element_type = get_html_element_type_from_tag( _text ); 

		is_input = FALSE; 
		switch( element_type )
		{
		case HTML_INPUT_ELEMENT: 
			{
				IHTMLInputTextElementPtr input_text_element; 
				IHTMLInputElementPtr input_element; 

				hr = html_element->QueryInterface( IID_IHTMLInputElement, ( PVOID* )&input_element ); 
				if( S_OK != hr )
				{
					break; 
				}

				if( NULL == input_element )
				{
					break; 
				}

				do 
				{
					VARIANT_BOOL checked; 
					hr = input_element->get_type( text.GetAddress() ); 

					if( FAILED( hr ) )
					{
						break; 
					}

					_text = text.operator const wchar_t*(); 
					if( NULL == _text )
					{
						break; 
					}

					if( 0 != _wcsicmp( _text, L"checkbox" ) )
					{
						break; 
					}

					input_value = L""; 

					hr = input_element->get_checked( &checked ); 

					if( FAILED( hr ) )
					{
						break; 
					}

					if( checked == VARIANT_TRUE )
					{
						input_value = L"checked"; 
					}

				}while( FALSE );

				hr = html_element->QueryInterface( IID_IHTMLInputTextElement, ( PVOID* )&input_text_element ); 
				if( S_OK != hr )
				{
					break; 
				}

				if( NULL == input_text_element )
				{
					break; 
				}

				is_input = TRUE; 
				input_text_element->get_value( text.GetAddress() ); 

				_text = text.operator const wchar_t*(); 
				if( NULL == _text )
				{
					break; 
				}

				input_value = _text; 
			}
			break; 
		case HTML_BUTTON_ELEMENT: 
			break; 
		case HTML_A_ELEMENT: 
			break; 
		case HTML_BODY_ELEMENT: 
			{
				MSXML::IXMLDOMAttributePtr xml_attr; 

				is_input = TRUE; 
				hr = html_element->get_innerHTML( text.GetAddress() ); 
				if( S_OK != hr )
				{
					break; 
				}

				_text = text.operator const wchar_t*(); 
				if( NULL == _text )
				{
					break; 
				}

				input_value = _text; 
			}
			break; 
		case HTML_DIV_ELEMENT:
			{
				is_input = TRUE; 

				hr = html_element->get_innerText( text.GetAddress() ); 
				if( S_OK != hr )
				{
					break; 
				}

				_text = text.operator const wchar_t*(); 
				if( NULL == _text )
				{
					break; 
				}

			}
			break; 
		case HTML_TEXT_AREA_ELEMENT:
			{
				is_input = TRUE; 

				hr = html_element->get_innerText( text.GetAddress() ); 
				if( S_OK != hr )
				{
					break; 
				}

				_text = text.operator const wchar_t*(); 
				if( NULL == _text )
				{
					break; 
				}

			}
			break; 
		case HTML_SELECT_ELEMENT:
			{

			}
			break; 
		default:
			ASSERT( FALSE ); 
			log_trace_ex( MSG_IMPORTANT, "unknown HTML element: %s\n", _text ); 
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		if( ret != ERROR_SUCCESS )
		{
			break; 
		}
	}while( FALSE );

	return ret; 
}

LRESULT WINAPI make_config_file_exist( LPCWSTR config_file_path, ULONG cc_path_len )
{
	LRESULT ret = ERROR_SUCCESS; 
	HANDLE file_handle = INVALID_HANDLE_VALUE; 

	do 
	{
		ASSERT( config_file_path != NULL ); 

		ret = check_file_exist( config_file_path ); 
		if( ret != ERROR_SUCCESS )
		{
			ret = ERROR_SUCCESS; 

			file_handle = CreateFileW( config_file_path, 
				GENERIC_READ | GENERIC_WRITE, 
				FILE_SHARE_READ, 
				NULL, 
				OPEN_ALWAYS, 
				0, 
				NULL ); 

			if( file_handle == INVALID_HANDLE_VALUE )
			{
				ret = GetLastError(); 
				break; 
			}

            CloseHandle(file_handle); 

			ret = create_config_file( config_file_path ); 

		}
	}while( FALSE ); 

	return ret; 
}

LRESULT WINAPI create_config_file( LPCWSTR config_file_name )
{
	LRESULT ret = ERROR_SUCCESS; 
	HRESULT hr; 
	MSXML::IXMLDOMDocumentPtr xml_doc; 
	MSXML::IXMLDOMProcessingInstructionPtr xml_instruction; 
	MSXML::IXMLDOMElementPtr xml_element; 
	_bstr_t text; 

	do
	{
		hr = CoCreateInstance(__uuidof( MSXML::DOMDocument ), 
			NULL, 
			CLSCTX_INPROC_SERVER, 
			__uuidof( MSXML::IXMLDOMDocument ), 
			( void** )&xml_doc ); 
		if( hr != S_OK)
		{
			log_trace_ex( MSG_IMPORTANT, "create xml document error %08x", hr);
			ret = hr; 
			break; 
		}

		// ����Xml����
		hr = xml_doc->raw_createProcessingInstruction( L"xml", L"version=\"1.0\" encoding=\"utf-8\"", &xml_instruction );

		if( S_OK != hr )
		{
			log_trace_ex( MSG_IMPORTANT, "����KEY XML:����XML����ʧ��" );
			ret = hr; 
			break; 
		}

		hr = xml_doc->raw_appendChild( xml_instruction, NULL );
		if( S_OK != hr )
		{
			ret = hr; 
			break; 
		}

		text = HTML_SCRIPT_ROOT_ELEMENT_NAME; 
		xml_element = xml_doc->createElement( text ); 

		if( NULL == xml_element )
		{
			ret = ERROR_ERRORS_ENCOUNTERED; 
			break; 
		}

		hr = xml_doc->appendChild( xml_element ); 
		if( FAILED( hr ) )
		{
			ret = hr; 
			//break; 
		}

        try
		{

			_variant_t save_file_name; 

			text = config_file_name; 
			save_file_name = text; 			
			hr = xml_doc->save( save_file_name ); 

			if( hr != S_OK )
			{
				ret = hr; 
			}
		}
        catch (...)
        {
            ret = ERROR_ERRORS_ENCOUNTERED; 
            break; 
        }

	}while( FALSE ); 

	return ret; 
}

