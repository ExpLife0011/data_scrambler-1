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
#include <mshtml.h>
#include <comutil.h>
#include <comdef.h>
#include <comdefsp.h>
#include <strsafe.h>
#import "msxml.tlb"
//#import "mshtml.tlb"
#include "mshtml_addition.h"
#define XPATH_CREATE
#include "html_xpath.h"
#include "markup.h"

/**************************************************************************
HTML动作单元配置内容:
1. HTML ELEMENT的XPATH
2. 执行的动作
3. 输出结果(结果具有属性)
**************************************************************************/

LRESULT WINAPI input_html_element_action( LPCWSTR xpath, 
										 HTML_ELEMENT_ACTION *action )
{
	LRESULT ret = ERROR_SUCCESS; 

	do 
	{
	} while ( FALSE );

	return ret; 
}
