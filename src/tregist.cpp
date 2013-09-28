static char *tregist_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2005   tregist.cpp	Ver0.95";
/* ========================================================================
	Project  Name			: Win32 Lightweight  Class Library Test
	Module Name				: Registry Class
	Create					: 1996-06-01(Sat)
	Update					: 2005-05-03(Tue)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include <stdio.h>
#include "tlib.h"

TRegistry::TRegistry(LPCSTR company, LPSTR appName)
{
	openCnt = 0;
	ChangeApp(company, appName);
}

TRegistry::TRegistry(HKEY top_key)
{
	topKey = top_key;
	openCnt = 0;
}

TRegistry::~TRegistry(void)
{
	while (openCnt > 0)
		CloseKey();
}

BOOL TRegistry::ChangeApp(LPCSTR company, LPSTR appName)
{
	while (openCnt > 0)
		CloseKey();

	topKey = HKEY_CURRENT_USER;

	char	buf[100];
	wsprintf(buf, "software\\%s", company);
	if (appName != NULL && *appName)
		wsprintf(buf + strlen(buf), "\\%s", appName);

	return	CreateKey(buf);
}

void TRegistry::ChangeTopKey(HKEY top_key)
{
	while (openCnt > 0)
		CloseKey();

	topKey = top_key;
}

BOOL TRegistry::OpenKey(LPCSTR subKey, BOOL createFlg)
{
	HKEY	parentKey = (openCnt == 0 ? topKey : hKey[openCnt -1]);

	if (openCnt >= MAX_KEYARRAY)
		return	FALSE;

	DWORD	tmp;
	LONG	status;
	Wstr	subKey_w(subKey);

	if (createFlg) {
		status = ::RegCreateKeyExW(parentKey, subKey_w, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey[openCnt], &tmp);
	}
	else {
		if ((status = ::RegOpenKeyExW(parentKey, subKey_w, 0, KEY_ALL_ACCESS, &hKey[openCnt])) != ERROR_SUCCESS)
			status = ::RegOpenKeyExW(parentKey, subKey_w, 0, KEY_READ, &hKey[openCnt]);
	}

	if (status == ERROR_SUCCESS)
		return	openCnt++, TRUE;
	else
		return	FALSE;
}

BOOL TRegistry::CloseKey(void)
{
	if (openCnt <= 0)
		return	FALSE;

	::RegCloseKey(hKey[--openCnt]);

	return	TRUE;
}

BOOL TRegistry::GetInt(LPCSTR subKey, int *val)
{
	long	tmp_val;

	if (GetLong(subKey, &tmp_val) == FALSE)
		return	FALSE;
	*val = (int)tmp_val;
	return	TRUE;
}

BOOL TRegistry::SetInt(LPCSTR subKey, int val)
{
	return	SetLong(subKey, (long)val);
}

BOOL TRegistry::GetLong(LPCSTR subKey, long *val)
{
	DWORD	type = REG_DWORD, dw_size = sizeof(long);
	Wstr	subKey_w(subKey);

	if (::RegQueryValueExW(hKey[openCnt -1], subKey_w, 0, &type, (BYTE *)val, &dw_size) == ERROR_SUCCESS)
		return	TRUE;

// 昔の互換性用
	WCHAR	wbuf[100];
	long	size_byte = sizeof(wbuf);

	if (::RegQueryValueW(hKey[openCnt -1], subKey_w, wbuf, &size_byte) != ERROR_SUCCESS)
		return	FALSE;
	*val = wcstol(wbuf, 0, 10);
	return	TRUE;
}

BOOL TRegistry::SetLong(LPCSTR subKey, long val)
{
	Wstr	subKey_w(subKey);

	return	::RegSetValueExW(hKey[openCnt -1], subKey_w, 0, REG_DWORD, (const BYTE *)&val, sizeof(val)) == ERROR_SUCCESS;
}

BOOL TRegistry::GetStr(LPCSTR subKey, LPSTR str, int size)
{
	DWORD	type = REG_SZ;
	Wstr	subKey_w(subKey), str_w(size);
	DWORD	size_byte = size;

	if (::RegQueryValueExW(hKey[openCnt -1], subKey_w, 0, &type, (BYTE *)str_w.Buf(), &size_byte) != ERROR_SUCCESS
	&&  ::RegQueryValueW(hKey[openCnt -1], subKey_w, str_w.Buf(), (LPLONG)&size_byte) != ERROR_SUCCESS)
		return	FALSE;

	WtoU8(str_w, str, size);
	return	TRUE;
}

BOOL TRegistry::GetStrA(LPCSTR subKey, LPSTR str, int size)
{
	DWORD	type = REG_SZ;

	if (::RegQueryValueExA(hKey[openCnt -1], subKey, 0, &type, (BYTE *)str, (DWORD *)&size) != ERROR_SUCCESS
	&&  ::RegQueryValueA(hKey[openCnt -1], subKey, str, (LPLONG)&size) != ERROR_SUCCESS)
		return	FALSE;

	return	TRUE;
}

BOOL TRegistry::SetStr(LPCSTR subKey, LPCSTR str)
{
	Wstr	subKey_w(subKey), str_w(str);

	return	::RegSetValueExW(hKey[openCnt -1], subKey_w, 0, REG_SZ, (const BYTE *)(const WCHAR *)str_w, (wcslen(str_w) +1) * sizeof(WCHAR)) == ERROR_SUCCESS;
}

BOOL TRegistry::SetStrA(LPCSTR subKey, LPCSTR str)
{
	return	::RegSetValueExA(hKey[openCnt -1], subKey, 0, REG_SZ, (const BYTE *)str, strlen(str) +1) == ERROR_SUCCESS;
}

BOOL TRegistry::GetByte(LPCSTR subKey, BYTE *data, int *size)
{
	DWORD	type = REG_BINARY;
	Wstr	subKey_w(subKey);

	return	::RegQueryValueExW(hKey[openCnt -1], subKey_w, 0, &type, (BYTE *)data, (LPDWORD)size) == ERROR_SUCCESS;
}

BOOL TRegistry::SetByte(LPCSTR subKey, const BYTE *data, int size)
{
	Wstr	subKey_w(subKey);
	return	::RegSetValueExW(hKey[openCnt -1], subKey_w, 0, REG_BINARY, data, size) == ERROR_SUCCESS;
}

BOOL TRegistry::DeleteKey(LPCSTR subKey)
{
	Wstr	subKey_w(subKey);
	return	::RegDeleteKeyW(hKey[openCnt -1], subKey_w) == ERROR_SUCCESS;
}

BOOL TRegistry::DeleteValue(LPCSTR subValue)
{
	Wstr	subValue_w(subValue);
	return	::RegDeleteValueW(hKey[openCnt -1], subValue_w) == ERROR_SUCCESS;
}

BOOL TRegistry::EnumKey(DWORD cnt, LPSTR buf, int size)
{
	Wstr	buf_w(size);
	DWORD	size_byte = size;

	if (::RegEnumKeyExW(hKey[openCnt -1], cnt, buf_w.Buf(), &size_byte, 0, 0, 0, 0) != ERROR_SUCCESS)
		return	FALSE;

	WtoU8(buf_w, buf, size);
	return	TRUE;
}

BOOL TRegistry::EnumValue(DWORD cnt, LPSTR buf, int size, DWORD *type)
{
	Wstr	buf_w(size);
	DWORD	size_byte = size;

	if (::RegEnumValueW(hKey[openCnt -1], cnt, buf_w.Buf(), &size_byte, 0, type, 0, 0) != ERROR_SUCCESS)
		return	FALSE;

	WtoU8(buf_w, buf, size);
	return	TRUE;
}

/*
	subKey を指定した場合は subkey を含むキー以下を削除
	subkey が NULL の場合、カレント の配下を削除
*/
BOOL TRegistry::DeleteChildTree(LPSTR subKey)
{
	char	buf[100];
	BOOL	ret = TRUE;

	if (subKey != NULL && OpenKey(subKey) != TRUE)
		return	FALSE;

	while (EnumKey(0, buf, sizeof(buf)))
	{
		if ((ret = DeleteChildTree(buf)) != TRUE)
			break;
	}
	if (subKey != NULL)
	{
		CloseKey();
		ret = DeleteKey(subKey) ? ret : FALSE;
	}
	else {
		while (EnumValue(0, buf, sizeof(buf)))
		{
			if (DeleteValue(buf) != TRUE)
			{
				ret = FALSE;
				break;
			}
		}
	}
	return	ret;
}

