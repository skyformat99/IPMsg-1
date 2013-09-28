static char *tini_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2005   tini.cpp	Ver0.95";
/* ========================================================================
	Project  Name			: Win32 Lightweight  Class Library Test
	Module Name				: Registry Class
	Create					: 1996-06-01(Sat)
	Update					: 2005-11-28(Mon)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include <stdio.h>
#include "tlib.h"

TInifile::TInifile(char *_ini_file)
{
	ini_file = cur_section = NULL;
	if (_ini_file)
		Init(_ini_file);
	SetSection("Default");
}

TInifile::~TInifile(void)
{
	free(cur_section);
	free(ini_file);
}

void TInifile::Init(char *_ini_file)
{
	ini_file = strdup(_ini_file);
}

void TInifile::SetSection(char *section)
{
	free(cur_section);
	cur_section = strdup(section);
}

BOOL TInifile::DelSection(const char *section)
{
	return	::WritePrivateProfileString(section, NULL, NULL, ini_file);
}

BOOL TInifile::DelKey(const char *key)
{
	return	::WritePrivateProfileString(cur_section, key, NULL, ini_file);
}

BOOL TInifile::SetStr(const char *key, const char *val)
{
	if (!val)
		return	DelKey(key);

	char *buf = new char [strlen(val) + 3];

	sprintf(buf, "\"%s\"", val);
	BOOL	ret = ::WritePrivateProfileString(cur_section, key, buf, ini_file);

	delete [] buf;
	return	ret;
}

DWORD TInifile::GetStr(const char *key, char *val, int max_size, const char *default_val)
{
	return	::GetPrivateProfileString(cur_section, key, default_val, val, max_size, ini_file);
}

BOOL TInifile::SetInt(const char *key, int val)
{
	char	buf[100];
	sprintf(buf, "%d", val);
	return	SetStr(key, buf);
}

int TInifile::GetInt(const char *key, int default_val)
{
	return	::GetPrivateProfileInt(cur_section, key, default_val, ini_file);
}

