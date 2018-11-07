#include "stdafx.h"
#include <mshtml.h>
#include <comutil.h>
#include <comdef.h>
#include <comdefsp.h>
#include <strsafe.h>
#import "msxml.tlb"
#include "mshtml_addition.h"
#define XPATH_CREATE
#include "html_xpath.h"
#include "markup.h"
#include "json/json.h"

LRESULT WINAPI parse_post_process_script(const wstring &json, std::string &command, std::string script)
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

#include <regex>
LRESULT WINAPI regex_process(const std::string input, const std::string& format, std::string &output)

{
	//"(\\d{1,2})(\\.|-|/)(\\d{1,2})(\\.|-|/)(\\d{4})"
	const std:: regex pattern(format);
	smatch result;

	output.clear(); 

	string::const_iterator iterStart = input.begin();
	string::const_iterator iterEnd = input.end();
	string temp;
	while (regex_search(iterStart, iterEnd, result, pattern))
	{
		temp = result[0]; 
		output = output + temp; 
		iterStart = result[0].second; 
	}

	return ERROR_SUCCESS; 
}

LRESULT WINAPI exec_post_process_script(const wstring text, const wstring &script, wstring &output )
{
	LRESULT ret = ERROR_SUCCESS; 
	string command; 
	string _script; 
	string _output; 
	
	do 
	{
		ret = parse_post_process_script( script, command, _script ); 
		if( ret != ERROR_SUCCESS )
		{
			break; 
		}

		ret = unicode_to_utf8_ex(output.c_str(), _output); 
		if( ERROR_SUCCESS != ret )
		{
			break; 
		}

		if( 0 == strcmp( "regex", command.c_str() ) )
		{
			regex_process( _output, _script, _output ); 
		}

		ret = utf8_to_unicode_ex(_output.c_str(), output); 
		if( ERROR_SUCCESS != ret )
		{
			break; 
		}
	} while ( FALSE ); 
	return ret; 
}

LRESULT WINAPI post_process_html_element( HTML_ELEMENT_ACTION *action )
{
	LRESULT ret = ERROR_SUCCESS; 
	wstring output; 
	
	do 
	{
		ASSERT(NULL != action ); 
		if( action->post_process.length() == 0 )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		if( 0 != wcscmp( HTML_ELEMENT_ACTION_OUTPUT, 
			action->action.c_str() )
			|| 0 != wcscmp( HTML_ELEMENT_ACTION_OUTPUT_PARAM_TEXT, 
			action->param.c_str() ) )
		{
			ret = ERROR_INVALID_PARAMETER; 
			break; 
		}

		if( action->outputs.size() == 0 )
		{
			break; 
		}

		output = action->outputs[0]; 
		if( output.length() == 0 )
		{
			break; 
		}

		ret = exec_post_process_script(output, action->post_process, output ); ; 
		if( ret != ERROR_SUCCESS )
		{
			break; 
		}
	} while ( FALSE ); 

	return ret; 
}