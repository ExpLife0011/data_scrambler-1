// stdafx.cpp : source file that includes just the standard includes
// html_maker_config.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef _DEBUG
#if defined _M_IX86
#pragma comment(lib,"scramble_kerneld.lib")
#else
#error only support compile x86 version, support windows x86 and x64.
#endif
#else
#if defined _M_IX86
#pragma comment(lib,"scramble_kernel.lib")
#else
#error only support compile x86 version, support windows x86 and x64.
#endif
#endif


