/************************************************************************************* 
This file is a part of CrashRpt library.

Copyright (c) 2003, Michael Carruth
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this 
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

* Neither the name of the author nor the names of its contributors 
may be used to endorse or promote products derived from this software without 
specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************************/

// File: Utility.h
// Description: Miscellaneous helper functions
// Authors: mikecarruth, zexspectrum
// Date: 

#ifndef _UTILITY_H_
#define _UTILITY_H_

#ifdef TEST_DATA_SENDER
#include "data_center_pch.h"
#else
#include "stdafx.h"
#endif //TEST_DATA_SENDER

#undef NOT_INCLUDE_WTL 
#ifdef NOT_INCLUDE_WTL
/////////////////////////////////////////////////////////////////////////////
// CRegKey

class CRegKey
{
public:
	CRegKey() throw();
	CRegKey( CRegKey& key ) throw();
	explicit CRegKey(HKEY hKey) throw();
	~CRegKey() throw();

	CRegKey& operator=( CRegKey& key ) throw();

	// Attributes
public:
	operator HKEY() const throw();
	HKEY m_hKey;
	REGSAM m_samWOW64;

	// Operations
public:
	ATL_DEPRECATED("CRegKey::SetValue(DWORD, TCHAR *valueName) has been superseded by CRegKey::SetDWORDValue")
		LONG SetValue(DWORD dwValue, LPCTSTR lpszValueName);
	ATL_DEPRECATED("CRegKey::SetValue(TCHAR *value, TCHAR *valueName) has been superseded by CRegKey::SetStringValue and CRegKey::SetMultiStringValue")
		LONG SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL, bool bMulti = false, int nValueLen = -1);
	LONG SetValue(LPCTSTR pszValueName, DWORD dwType, const void* pValue, ULONG nBytes) throw();
	LONG SetGUIDValue(LPCTSTR pszValueName, REFGUID guidValue) throw();
	LONG SetBinaryValue(LPCTSTR pszValueName, const void* pValue, ULONG nBytes) throw();
	LONG SetDWORDValue(LPCTSTR pszValueName, DWORD dwValue) throw();
	LONG SetQWORDValue(LPCTSTR pszValueName, ULONGLONG qwValue) throw();
	LONG SetStringValue(_In_opt_z_ LPCTSTR pszValueName, _In_opt_z_ LPCTSTR pszValue, _In_ DWORD dwType = REG_SZ) throw();
	LONG SetMultiStringValue(LPCTSTR pszValueName, LPCTSTR pszValue) throw();

	ATL_DEPRECATED("CRegKey::QueryValue(DWORD, TCHAR *valueName) has been superseded by CRegKey::QueryDWORDValue")
		LONG QueryValue(_Out_ DWORD& dwValue, _In_opt_z_ LPCTSTR lpszValueName);
	ATL_DEPRECATED("CRegKey::QueryValue(TCHAR *value, TCHAR *valueName) has been superseded by CRegKey::QueryStringValue and CRegKey::QueryMultiStringValue")
		LONG QueryValue(_Out_opt_z_cap_post_count_(*pdwCount, *pdwCount) LPTSTR szValue, _In_opt_z_ LPCTSTR lpszValueName, _Inout_ DWORD* pdwCount);
	LONG QueryValue(_In_opt_z_ LPCTSTR pszValueName, DWORD* pdwType, void* pData, ULONG* pnBytes) throw();
	LONG QueryGUIDValue(_In_opt_z_ LPCTSTR pszValueName, GUID& guidValue) throw();
	LONG QueryBinaryValue(_In_opt_z_ LPCTSTR pszValueName, void* pValue, ULONG* pnBytes) throw();
	LONG QueryDWORDValue(_In_opt_z_ LPCTSTR pszValueName, DWORD& dwValue) throw();
	LONG QueryQWORDValue(_In_opt_z_ LPCTSTR pszValueName, ULONGLONG& qwValue) throw();
	LONG QueryStringValue(_In_opt_z_ LPCTSTR pszValueName, _Out_opt_z_cap_post_count_(*pnChars, *pnChars)  LPTSTR pszValue, _Inout_ ULONG* pnChars) throw();
	LONG QueryMultiStringValue(_In_opt_z_ LPCTSTR pszValueName, _Out_opt_z_cap_post_count_(*pnChars, *pnChars)  LPTSTR pszValue, _Inout_ ULONG* pnChars) throw();

	// Get the key's security attributes.
	LONG GetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd, LPDWORD pnBytes) throw();
	// Set the key's security attributes.
	LONG SetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd) throw();

	LONG SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL) throw();
	static LONG WINAPI SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);

	// Create a new registry key (or open an existing one).
	LONG Create(_In_ HKEY hKeyParent, _In_z_ LPCTSTR lpszKeyName,
		_In_opt_z_ LPTSTR lpszClass = REG_NONE, _In_ DWORD dwOptions = REG_OPTION_NON_VOLATILE,
		_In_ REGSAM samDesired = KEY_READ | KEY_WRITE,
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecAttr = NULL,
		_Out_opt_ LPDWORD lpdwDisposition = NULL) throw();
	// Open an existing registry key.
	LONG Open(HKEY hKeyParent, LPCTSTR lpszKeyName,
		REGSAM samDesired = KEY_READ | KEY_WRITE) throw();
	// Close the registry key.
	LONG Close() throw();
	// Flush the key's data to disk.
	LONG Flush() throw();

	// Detach the CRegKey object from its HKEY.  Releases ownership.
	HKEY Detach() throw();
	// Attach the CRegKey object to an existing HKEY.  Takes ownership.
	void Attach(HKEY hKey) throw();

	// Enumerate the subkeys of the key.
	LONG EnumKey(_In_ DWORD iIndex, _Out_z_cap_post_count_(*pnNameLength, *pnNameLength) LPTSTR pszName, _Inout_ LPDWORD pnNameLength, _Out_opt_ FILETIME* pftLastWriteTime = NULL) throw();
	LONG NotifyChangeKeyValue(BOOL bWatchSubtree, DWORD dwNotifyFilter, HANDLE hEvent, BOOL bAsync = TRUE) throw();

	LONG DeleteSubKey(LPCTSTR lpszSubKey) throw();
	LONG RecurseDeleteKey(LPCTSTR lpszKey) throw();
	LONG DeleteValue(LPCTSTR lpszValue) throw();
};

inline CRegKey::CRegKey() throw() : 
m_hKey( NULL ), m_samWOW64(0)
{
}

inline CRegKey::CRegKey( CRegKey& key ) throw() :
m_hKey( NULL ), m_samWOW64(key.m_samWOW64)
{
	Attach( key.Detach() );
}

inline CRegKey::CRegKey(HKEY hKey) throw() :
m_hKey(hKey), m_samWOW64(0)
{
}

inline CRegKey::~CRegKey() throw()
{Close();}

inline CRegKey& CRegKey::operator=( CRegKey& key ) throw()
{
	if(m_hKey!=key.m_hKey)
	{
		Close();
		Attach( key.Detach() );
		m_samWOW64 = key.m_samWOW64;
	}
	return( *this );
}

inline CRegKey::operator HKEY() const throw()
{return m_hKey;}

inline HKEY CRegKey::Detach() throw()
{
	HKEY hKey = m_hKey;
	m_hKey = NULL;
	m_samWOW64 = 0;
	return hKey;
}

inline void CRegKey::Attach(HKEY hKey) throw()
{
	ATLASSUME(m_hKey == NULL);
	m_hKey = hKey;
	m_samWOW64 = 0;
}

inline LONG CRegKey::DeleteSubKey(LPCTSTR lpszSubKey) throw()
{
	ATLASSUME(m_hKey != NULL);

#if WINVER >= 0x0501
	typedef LSTATUS (WINAPI * PFNRegDeleteKeyEx)(HKEY, LPCTSTR, REGSAM, DWORD);
	static bool bInitialized = false;
	static PFNRegDeleteKeyEx pfnRegDeleteKeyEx = NULL;

	if (!bInitialized)
	{
		HMODULE hAdvapi32 = GetModuleHandle(_T("Advapi32.dll"));
		if (hAdvapi32 != NULL)
		{
#ifdef _UNICODE
			pfnRegDeleteKeyEx = (PFNRegDeleteKeyEx)GetProcAddress(hAdvapi32, "RegDeleteKeyExW");
#else
			pfnRegDeleteKeyEx = (PFNRegDeleteKeyEx)GetProcAddress(hAdvapi32, "RegDeleteKeyExA");
#endif	// _UNICODE
		}
		bInitialized = true;
	}

	if (pfnRegDeleteKeyEx != NULL)
	{
		return pfnRegDeleteKeyEx(m_hKey, lpszSubKey, m_samWOW64, 0);
	}

#endif	// WINVER

	return RegDeleteKey(m_hKey, lpszSubKey);
}

inline LONG CRegKey::DeleteValue(LPCTSTR lpszValue) throw()
{
	ATLASSUME(m_hKey != NULL);
	return RegDeleteValue(m_hKey, (LPTSTR)lpszValue);
}

inline LONG CRegKey::Close() throw()
{
	LONG lRes = ERROR_SUCCESS;
	if (m_hKey != NULL)
	{
		lRes = RegCloseKey(m_hKey);
		m_hKey = NULL;
	}
	m_samWOW64 = 0;
	return lRes;
}

inline LONG CRegKey::Flush() throw()
{
	ATLASSUME(m_hKey != NULL);

	return ::RegFlushKey(m_hKey);
}

inline LONG CRegKey::EnumKey(_In_ DWORD iIndex, _Out_z_cap_post_count_(*pnNameLength, *pnNameLength) LPTSTR pszName, _Inout_ LPDWORD pnNameLength, _Out_opt_ FILETIME* pftLastWriteTime) throw()
{
	FILETIME ftLastWriteTime;

	ATLASSUME(m_hKey != NULL);
	if (pftLastWriteTime == NULL)
	{
		pftLastWriteTime = &ftLastWriteTime;
	}

	return ::RegEnumKeyEx(m_hKey, iIndex, pszName, pnNameLength, NULL, NULL, NULL, pftLastWriteTime);
}

inline LONG CRegKey::NotifyChangeKeyValue(BOOL bWatchSubtree, DWORD dwNotifyFilter, HANDLE hEvent, BOOL bAsync) throw()
{
	ATLASSUME(m_hKey != NULL);
	ATLASSERT((hEvent != NULL) || !bAsync);

	return ::RegNotifyChangeKeyValue(m_hKey, bWatchSubtree, dwNotifyFilter, hEvent, bAsync);
}

inline LONG CRegKey::Create(_In_ HKEY hKeyParent, _In_z_ LPCTSTR lpszKeyName,
							_In_opt_z_ LPTSTR lpszClass, _In_ DWORD dwOptions, _In_ REGSAM samDesired,
							_In_opt_ LPSECURITY_ATTRIBUTES lpSecAttr, _Out_opt_ LPDWORD lpdwDisposition) throw()
{
	ATLASSERT(hKeyParent != NULL);
	DWORD dw;
	HKEY hKey = NULL;
	LONG lRes = RegCreateKeyEx(hKeyParent, lpszKeyName, 0,
		lpszClass, dwOptions, samDesired, lpSecAttr, &hKey, &dw);
	if (lpdwDisposition != NULL)
		*lpdwDisposition = dw;
	if (lRes == ERROR_SUCCESS)
	{
		lRes = Close();
		m_hKey = hKey;
#if WINVER >= 0x0501
		m_samWOW64 = samDesired & (KEY_WOW64_32KEY | KEY_WOW64_64KEY);
#endif
	}
	return lRes;
}

inline LONG CRegKey::Open(HKEY hKeyParent, LPCTSTR lpszKeyName, REGSAM samDesired) throw()
{
	ATLASSUME(hKeyParent != NULL);
	HKEY hKey = NULL;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyName, 0, samDesired, &hKey);
	if (lRes == ERROR_SUCCESS)
	{
		lRes = Close();
		ATLASSERT(lRes == ERROR_SUCCESS);
		m_hKey = hKey;
#if WINVER >= 0x0501
		m_samWOW64 = samDesired & (KEY_WOW64_32KEY | KEY_WOW64_64KEY);
#endif
	}
	return lRes;
}

#pragma warning(push)
#pragma warning(disable: 4996)
inline LONG CRegKey::QueryValue(DWORD& dwValue, LPCTSTR lpszValueName)
{
	DWORD dwType = NULL;
	DWORD dwCount = sizeof(DWORD);
	LONG lRes = RegQueryValueEx(m_hKey, lpszValueName, NULL, &dwType,
		(LPBYTE)&dwValue, &dwCount);
	ATLASSERT((lRes!=ERROR_SUCCESS) || (dwType == REG_DWORD));
	ATLASSERT((lRes!=ERROR_SUCCESS) || (dwCount == sizeof(DWORD)));
	if (dwType != REG_DWORD)
		return ERROR_INVALID_DATA;
	return lRes;
}

#pragma warning(disable: 6053 6385)
inline LONG CRegKey::QueryValue(_Out_opt_z_cap_post_count_(*pdwCount, *pdwCount) LPTSTR pszValue, _In_opt_z_ LPCTSTR lpszValueName, _Inout_ DWORD* pdwCount)
{
	ATLENSURE(pdwCount != NULL);
	DWORD dwType = NULL;
	LONG lRes = RegQueryValueEx(m_hKey, lpszValueName, NULL, &dwType, (LPBYTE)pszValue, pdwCount);
	ATLASSERT((lRes!=ERROR_SUCCESS) || (dwType == REG_SZ) ||
		(dwType == REG_MULTI_SZ) || (dwType == REG_EXPAND_SZ));
	if (pszValue != NULL)
	{
		if(*pdwCount>0)
		{
			switch(dwType)
			{
			case REG_SZ:
			case REG_EXPAND_SZ:
				if ((*pdwCount) % sizeof(TCHAR) != 0 || pszValue[(*pdwCount) / sizeof(TCHAR) - 1] != 0)
				{
					pszValue[0]=_T('\0');
					return ERROR_INVALID_DATA;
				}
				break;
			case REG_MULTI_SZ:
				if ((*pdwCount) % sizeof(TCHAR) != 0 || (*pdwCount) / sizeof(TCHAR) < 1 || pszValue[(*pdwCount) / sizeof(TCHAR) -1] != 0 || (((*pdwCount) / sizeof(TCHAR))>1 && pszValue[(*pdwCount) / sizeof(TCHAR) - 2] != 0) )
				{
					pszValue[0]=_T('\0');
					return ERROR_INVALID_DATA;
				}
				break;
			default:
				// Ensure termination
				pszValue[0]=_T('\0');
				return ERROR_INVALID_DATA;
			}
		}
		else
		{
			// this is a blank one with no data yet
			// Ensure termination
			pszValue[0]=_T('\0');
		}
	}
	return lRes;
}
#pragma warning(pop)	

inline LONG CRegKey::QueryValue(LPCTSTR pszValueName, DWORD* pdwType, void* pData, ULONG* pnBytes) throw()
{
	ATLASSUME(m_hKey != NULL);

	return( ::RegQueryValueEx(m_hKey, pszValueName, NULL, pdwType, static_cast< LPBYTE >( pData ), pnBytes) );
}

inline LONG CRegKey::QueryDWORDValue(LPCTSTR pszValueName, DWORD& dwValue) throw()
{
	LONG lRes;
	ULONG nBytes;
	DWORD dwType;

	ATLASSUME(m_hKey != NULL);

	nBytes = sizeof(DWORD);
	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(&dwValue),
		&nBytes);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	if (dwType != REG_DWORD)
		return ERROR_INVALID_DATA;

	return ERROR_SUCCESS;
}
inline LONG CRegKey::QueryQWORDValue(LPCTSTR pszValueName, ULONGLONG& qwValue) throw()
{
	LONG lRes;
	ULONG nBytes;
	DWORD dwType;

	ATLASSUME(m_hKey != NULL);

	nBytes = sizeof(ULONGLONG);
	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(&qwValue),
		&nBytes);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	if (dwType != REG_QWORD)
		return ERROR_INVALID_DATA;

	return ERROR_SUCCESS;
}

inline LONG CRegKey::QueryBinaryValue(LPCTSTR pszValueName, void* pValue, ULONG* pnBytes) throw()
{
	LONG lRes;
	DWORD dwType;

	ATLASSERT(pnBytes != NULL);
	ATLASSUME(m_hKey != NULL);

	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(pValue),
		pnBytes);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	if (dwType != REG_BINARY)
		return ERROR_INVALID_DATA;

	return ERROR_SUCCESS;
}

#pragma warning(push)
#pragma warning(disable: 6053)
/* prefast noise VSW 496818 */
inline LONG CRegKey::QueryStringValue(LPCTSTR pszValueName, LPTSTR pszValue, ULONG* pnChars) throw()
{
	LONG lRes;
	DWORD dwType;
	ULONG nBytes;

	ATLASSUME(m_hKey != NULL);
	ATLASSERT(pnChars != NULL);

	nBytes = (*pnChars)*sizeof(TCHAR);
	*pnChars = 0;
	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(pszValue),
		&nBytes);

	if (lRes != ERROR_SUCCESS)
	{
		return lRes;
	}

	if(dwType != REG_SZ && dwType != REG_EXPAND_SZ)
	{
		return ERROR_INVALID_DATA;
	}

	if (pszValue != NULL)
	{
		if(nBytes!=0)
		{
#pragma warning(suppress:6385) // suppress noisy code analysis warning due to annotation on RegQueryValueEx
			if ((nBytes % sizeof(TCHAR) != 0) || (pszValue[nBytes / sizeof(TCHAR) -1] != 0))
			{
				return ERROR_INVALID_DATA;
			}
		}
		else
		{
			pszValue[0]=_T('\0');
		}
	}

	*pnChars = nBytes/sizeof(TCHAR);

	return ERROR_SUCCESS;
}
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 6053)
/* prefast noise VSW 496818 */
inline LONG CRegKey::QueryMultiStringValue(LPCTSTR pszValueName, LPTSTR pszValue, ULONG* pnChars) throw()
{
	LONG lRes;
	DWORD dwType;
	ULONG nBytes;

	ATLASSUME(m_hKey != NULL);
	ATLASSERT(pnChars != NULL);

	if (pszValue != NULL && *pnChars < 2)
		return ERROR_INSUFFICIENT_BUFFER;

	nBytes = (*pnChars)*sizeof(TCHAR);
	*pnChars = 0;

	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(pszValue),
		&nBytes);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	if (dwType != REG_MULTI_SZ)
		return ERROR_INVALID_DATA;
	if (pszValue != NULL && (nBytes % sizeof(TCHAR) != 0 || nBytes / sizeof(TCHAR) < 1 || pszValue[nBytes / sizeof(TCHAR) -1] != 0 || ((nBytes/sizeof(TCHAR))>1 && pszValue[nBytes / sizeof(TCHAR) - 2] != 0)))
		return ERROR_INVALID_DATA;

	*pnChars = nBytes/sizeof(TCHAR);

	return ERROR_SUCCESS;
}
#pragma warning(pop)

inline LONG CRegKey::QueryGUIDValue(LPCTSTR pszValueName, GUID& guidValue) throw()
{
	TCHAR szGUID[64];
	LONG lRes;
	ULONG nCount;
	HRESULT hr;

	ATLASSUME(m_hKey != NULL);

	guidValue = GUID_NULL;

	nCount = 64;
	lRes = QueryStringValue(pszValueName, szGUID, &nCount);

	if (lRes != ERROR_SUCCESS)
		return lRes;

	if(szGUID[0] != _T('{'))
		return ERROR_INVALID_DATA;

	USES_CONVERSION_EX;
	LPOLESTR lpstr = T2OLE_EX(szGUID, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
#ifndef _UNICODE
	if(lpstr == NULL) 
		return E_OUTOFMEMORY;
#endif	

	hr = ::CLSIDFromString(lpstr, &guidValue);
	if (FAILED(hr))
		return ERROR_INVALID_DATA;

	return ERROR_SUCCESS;
}

inline LONG WINAPI CRegKey::SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	ATLASSERT(lpszValue != NULL);
	CRegKey key;
	LONG lRes = key.Create(hKeyParent, lpszKeyName);
	if (lRes == ERROR_SUCCESS)
		lRes = key.SetStringValue(lpszValueName, lpszValue);
	return lRes;
}

inline LONG CRegKey::SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName) throw()
{
	ATLASSERT(lpszValue != NULL);
	CRegKey key;
	LONG lRes = key.Create(m_hKey, lpszKeyName, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE | m_samWOW64);
	if (lRes == ERROR_SUCCESS)
		lRes = key.SetStringValue(lpszValueName, lpszValue);
	return lRes;
}

#pragma warning(push)
#pragma warning(disable: 4996)
inline LONG CRegKey::SetValue(DWORD dwValue, LPCTSTR pszValueName)
{
	ATLASSUME(m_hKey != NULL);
	return SetDWORDValue(pszValueName, dwValue);
}

inline LONG CRegKey::SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName, bool bMulti, int nValueLen)
{
	ATLENSURE(lpszValue != NULL);
	ATLASSUME(m_hKey != NULL);

	if (bMulti && nValueLen == -1)
		return ERROR_INVALID_PARAMETER;

	if (nValueLen == -1)
		nValueLen = lstrlen(lpszValue) + 1;

	DWORD dwType = bMulti ? REG_MULTI_SZ : REG_SZ;

	return ::RegSetValueEx(m_hKey, lpszValueName, NULL, dwType,
		reinterpret_cast<const BYTE*>(lpszValue), nValueLen*sizeof(TCHAR));
}
#pragma warning(pop)

inline LONG CRegKey::SetValue(LPCTSTR pszValueName, DWORD dwType, const void* pValue, ULONG nBytes) throw()
{
	ATLASSUME(m_hKey != NULL);
	return ::RegSetValueEx(m_hKey, pszValueName, NULL, dwType, static_cast<const BYTE*>(pValue), nBytes);
}

inline LONG CRegKey::SetBinaryValue(LPCTSTR pszValueName, const void* pData, ULONG nBytes) throw()
{
	ATLASSUME(m_hKey != NULL);
	return ::RegSetValueEx(m_hKey, pszValueName, NULL, REG_BINARY, reinterpret_cast<const BYTE*>(pData), nBytes);
}

inline LONG CRegKey::SetDWORDValue(LPCTSTR pszValueName, DWORD dwValue) throw()
{
	ATLASSUME(m_hKey != NULL);
	return ::RegSetValueEx(m_hKey, pszValueName, NULL, REG_DWORD, reinterpret_cast<const BYTE*>(&dwValue), sizeof(DWORD));
}

inline LONG CRegKey::SetQWORDValue(LPCTSTR pszValueName, ULONGLONG qwValue) throw()
{
	ATLASSUME(m_hKey != NULL);
	return ::RegSetValueEx(m_hKey, pszValueName, NULL, REG_QWORD, reinterpret_cast<const BYTE*>(&qwValue), sizeof(ULONGLONG));
}

inline LONG CRegKey::SetStringValue(_In_opt_z_ LPCTSTR pszValueName, _In_opt_z_ LPCTSTR pszValue, _In_ DWORD dwType) throw()
{
	ATLASSUME(m_hKey != NULL);
	ATLENSURE_RETURN_VAL(pszValue != NULL, ERROR_INVALID_DATA);
	ATLASSERT((dwType == REG_SZ) || (dwType == REG_EXPAND_SZ));

	return ::RegSetValueEx(m_hKey, pszValueName, NULL, dwType, reinterpret_cast<const BYTE*>(pszValue), (lstrlen(pszValue)+1)*sizeof(TCHAR));
}

inline LONG CRegKey::SetMultiStringValue(LPCTSTR pszValueName, LPCTSTR pszValue) throw()
{
	LPCTSTR pszTemp;
	ULONG nBytes;
	ULONG nLength;

	ATLASSUME(m_hKey != NULL);
	ATLENSURE_RETURN_VAL(pszValue != NULL, ERROR_INVALID_DATA);

	// Find the total length (in bytes) of all of the strings, including the
	// terminating '\0' of each string, and the second '\0' that terminates
	// the list.
	nBytes = 0;
	pszTemp = pszValue;
	do
	{
		nLength = lstrlen(pszTemp)+1;
		pszTemp += nLength;
		nBytes += nLength*sizeof(TCHAR);
	} while (nLength != 1);

	return ::RegSetValueEx(m_hKey, pszValueName, NULL, REG_MULTI_SZ, reinterpret_cast<const BYTE*>(pszValue),
		nBytes);
}

inline LONG CRegKey::SetGUIDValue(LPCTSTR pszValueName, REFGUID guidValue) throw()
{
	OLECHAR szGUID[64];

	ATLASSUME(m_hKey != NULL);

	::StringFromGUID2(guidValue, szGUID, 64);

	USES_CONVERSION_EX;
	LPCTSTR lpstr = OLE2CT_EX(szGUID, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
#ifndef _UNICODE
	if(lpstr == NULL) 
		return E_OUTOFMEMORY;
#endif	
	return SetStringValue(pszValueName, lpstr);
}

inline LONG CRegKey::GetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd, LPDWORD pnBytes) throw()
{
	ATLASSUME(m_hKey != NULL);
	ATLASSUME(pnBytes != NULL);

	return ::RegGetKeySecurity(m_hKey, si, psd, pnBytes);
}

inline LONG CRegKey::SetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd) throw()
{
	ATLASSUME(m_hKey != NULL);
	ATLASSUME(psd != NULL);

	return ::RegSetKeySecurity(m_hKey, si, psd);
}

inline LONG CRegKey::RecurseDeleteKey(LPCTSTR lpszKey) throw()
{
	CRegKey key;
	LONG lRes = key.Open(m_hKey, lpszKey, KEY_READ | KEY_WRITE | m_samWOW64);
	if (lRes != ERROR_SUCCESS)
	{
		if (lRes != ERROR_FILE_NOT_FOUND && lRes != ERROR_PATH_NOT_FOUND)
		{
			ATLTRACE(atlTraceCOM, 0, _T("CRegKey::RecurseDeleteKey : Failed to Open Key %s(Error = %d)\n"), lpszKey, lRes);
		}
		return lRes;
	}
	FILETIME time;
	DWORD dwSize = 256;
	TCHAR szBuffer[256];
	while (RegEnumKeyEx(key.m_hKey, 0, szBuffer, &dwSize, NULL, NULL, NULL,
		&time)==ERROR_SUCCESS)
	{
		lRes = key.RecurseDeleteKey(szBuffer);
		if (lRes != ERROR_SUCCESS)
			return lRes;
		dwSize = 256;
	}
	key.Close();
	return DeleteSubKey(lpszKey);
}

#endif //NOT_INCLUDE_WTL

namespace Utility  
{
    // Returns base name of the EXE file that launched current process.
    CString getAppName();

    // Returns the unique tmp file name.
    CString getTempFileName();

    // Returns the path to the temporary directory.
    int getTempDirectory(CString& strTemp);

    // Returns path to directory where EXE or DLL module is located.
    CString GetModulePath(HMODULE hModule);

    // Returns the absolute path and name of the module
    CString GetModuleName(HMODULE hModule);

    // Generates unique identifier (GUID)
    int GenerateGUID(CString& sGUID);  

    // Returns current system time as string (uses UTC time format).
    int GetSystemTimeUTC(CString& sTime); 

    // Converts UTC string to local time.
    void UTC2SystemTime(CString sUTC, SYSTEMTIME& st);

    // Returns friendly name of operating system (name, version, service pack)
    int GetOSFriendlyName(CString& sOSName);  

    // Returns TRUE if Windows is 64-bit
    BOOL IsOS64Bit();  

    // Retrieves current geographic location
    int GetGeoLocation(CString& sGeoLocation);

    // Returns path to a special folder (for example %LOCAL_APP_DATA%)
    int GetSpecialFolder(int csidl, CString& sFolderPath);

    // Replaces restricted characters in file name
    CString ReplaceInvalidCharsInFileName(CString sFileName);

    // Moves a file to the Recycle Bin or removes the file permanently
    int RecycleFile(CString sFilePath, bool bPermanentDelete);

    // Retrieves a string from INI file.
    CString GetINIString(LPCTSTR pszFileName, LPCTSTR pszSection, LPCTSTR pszName);

    // Adds a string to INI file.
    void SetINIString(LPCTSTR pszFileName, LPCTSTR pszSection, LPCTSTR pszName, LPCTSTR pszValue);

    // Mirrors the content of a window.
    void SetLayoutRTL(HWND hWnd);

    // Formats the error message.
    CString FormatErrorMsg(DWORD dwErrorCode);

    // Parses file path and returns file name.
    CString GetFileName(CString sPath);

    // Parses file path and returns file name without extension.
    CString GetBaseFileName(CString sFileName);

    // Parses file path and returns file extension.
    CString GetFileExtension(CString sFileName);

    // Retrieves product version info from resources embedded into EXE or DLL
    CString GetProductVersion(CString sModuleName);

    // Creates a folder. If some intermediate folders in the path do not exist,
    // it creates them.
    BOOL CreateFolder(CString sFolderName);

    // Converts system time to UINT64
    ULONG64 SystemTimeToULONG64( const SYSTEMTIME& st );

    // Formats a string of file size
    CString FileSizeToStr(ULONG64 uFileSize); 
};

#endif	// _UTILITY_H_
