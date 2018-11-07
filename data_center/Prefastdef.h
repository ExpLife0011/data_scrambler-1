/*
 * 
 * Copyright (c) 2003, Michael Carruth All rights reserved.
 * This file is a part of CrashRpt library.
 *
 * Copyright 2010 JiJie Shi
 *
 * This file is part of data_scrambler.
 * 

 * Redistributions in source code form must reproduce the above copyright notice, 
 * the following disclaimer in the documentation and/or other materials provided with the distribution.

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

/*! \file   Prefastdef.h
*  \brief  SAL macro switches.
*  \date   2003-2011
*  \author zeXspectrum 
*/

#pragma once

#include <windows.h>

#if _MSC_VER<1400
#pragma warning(disable: 4616)  //warning C4616: #pragma warning : warning number '6255' out of range, must be between '4001' and '4999'
#endif

// Define SAL macros to be empty if some old Visual Studio used
#ifndef __reserved 
#define __reserved
#endif
#ifndef __in
#define __in
#endif
#ifndef __in_z
#define __in_z
#endif
#ifndef __in_opt
#define __in_opt
#endif
#ifndef __out_opt
#define __out_opt
#endif
#ifndef __out_ecount_z
#define __out_ecount_z(x)
#endif
#ifndef __deref_out
#define __deref_out
#endif
