static char *tmisc_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2005   tmisc.cpp	Ver1.00";
/* ========================================================================
	Project  Name			: Win32 Lightweight  Class Library Test
	Module Name				: Application Frame Class
	Create					: 1996-06-01(Sat)
	Update					: 2005-11-28(Mon)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include "tlib.h"

#include <stdio.h>
#include <mbstring.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

static HINSTANCE defaultInstance;

void InitInstanceForLoadStr(HINSTANCE hI)
{
	defaultInstance = hI;
}

#ifdef MS_VC4
BOOL	(WINAPI *SHGetPathFromIDListW)(LPCITEMIDLIST, void *);
LPITEMIDLIST (WINAPI *SHBrowseForFolderW)(BROWSEINFOW *);
#endif

LPITEMIDLIST (WINAPI *ILCreateFromPathW)(void *);
void (WINAPI *ILFreeW)(LPITEMIDLIST);

void InitGlobalItems()
{
	HMODULE	hModule = ::GetModuleHandle("shell32.dll");

#ifdef MS_VC4
	SHGetPathFromIDListW = (BOOL (WINAPI *)(LPCITEMIDLIST, void *))::GetProcAddress(hModule, "SHGetPathFromIDListW");
	SHBrowseForFolderW = (LPITEMIDLIST (WINAPI *)(BROWSEINFOW *))::GetProcAddress(hModule, "SHBrowseForFolderW");
#endif
	ILCreateFromPathW = (LPITEMIDLIST (WINAPI *)(void *))::GetProcAddress(hModule, "ILCreateFromPathW");
	ILFreeW = (void (WINAPI *)(LPITEMIDLIST))::GetProcAddress(hModule, "ILFree");
}


HWND CreateWindowU8(const char *class_name, const char *window_name, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU hMenu, HINSTANCE hInst, void *param)
{
	Wstr	class_name_w(class_name), window_name_w(window_name);

	return	::CreateWindowW(class_name_w, window_name_w, style, x, y, width, height, hParent, hMenu, hInst, param);
}

HWND FindWindowU8(const char *class_name, const char *window_name)
{
	Wstr	class_name_w(class_name), window_name_w(window_name);

	return	::FindWindowW(class_name_w, window_name_w);
}

BOOL TRegisterClass(LPCTSTR class_name, UINT style, HICON hIcon, HCURSOR hCursor, HBRUSH hbrBackground, int classExtra, int wndExtra, LPCTSTR menu_str)
{
	WNDCLASSW	wc;
	Wstr		class_nameW(class_name);
	Wstr		menu_strW(menu_str);

	memset(&wc, 0, sizeof(wc));
	wc.style			= style;
	wc.lpfnWndProc		= TApp::WinProc;
	wc.cbClsExtra 		= classExtra;
	wc.cbWndExtra		= wndExtra;
	wc.hInstance		= TApp::GetInstance();
	wc.hIcon			= hIcon;
	wc.hCursor			= hCursor;
	wc.hbrBackground	= hbrBackground;
	wc.lpszMenuName		= menu_strW;
	wc.lpszClassName	= class_nameW;

	return	::RegisterClassW(&wc);
}

BOOL AppendMenuU8(HMENU hMenu, UINT flags, UINT idItem, const char *item_str)
{
	Wstr	item_str_w(item_str);
	return	::AppendMenuW(hMenu, flags, idItem, item_str_w);
}

BOOL InsertMenuU8(HMENU hMenu, UINT idItem, UINT flags, UINT idNewItem, const char *item_str)
{
	Wstr	item_str_w(item_str);
	return	::InsertMenuW(hMenu, idItem, flags, idNewItem, item_str_w);
}

BOOL ModifyMenuU8(HMENU hMenu, UINT idItem, UINT flags, UINT idNewItem, const char *item_str)
{
	Wstr	item_str_w(item_str);
	return	::ModifyMenuW(hMenu, idItem, flags, idNewItem, item_str_w);
}

UINT DragQueryFileU8(HDROP hDrop, UINT iFile, char *buf, UINT cb)
{
	Wstr	wbuf(cb);

	UINT	ret = ::DragQueryFileW(hDrop, iFile, wbuf.Buf(), cb);

	if (ret > 0 && buf) {
		ret = WtoU8(wbuf, buf, cb);
	}
	return	ret;
}

void WIN32_FIND_DATA_WtoU8(const WIN32_FIND_DATAW *fdat_w, WIN32_FIND_DATA_U8 *fdat_u8, BOOL include_fname)
{
	memcpy(fdat_u8, fdat_w, offsetof(WIN32_FIND_DATAW, cFileName));
	if (include_fname) {
		WtoU8(fdat_w->cFileName, fdat_u8->cFileName, sizeof(fdat_u8->cFileName));
		WtoU8(fdat_w->cAlternateFileName, fdat_u8->cAlternateFileName, sizeof(fdat_u8->cAlternateFileName));
	}
}

HANDLE FindFirstFileU8(const char *path, WIN32_FIND_DATA_U8 *fdat)
{
	Wstr				wpath(path);
	WIN32_FIND_DATAW	fdat_w;
	HANDLE				ret;

	if ((ret = ::FindFirstFileW(wpath, &fdat_w)) != INVALID_HANDLE_VALUE) {
		WIN32_FIND_DATA_WtoU8(&fdat_w, fdat);
	}

	return	ret;
}

BOOL FindNextFileU8(HANDLE hDir, WIN32_FIND_DATA_U8 *fdat)
{
	WIN32_FIND_DATAW	fdat_w;
	BOOL				ret;

	if ((ret = ::FindNextFileW(hDir, &fdat_w))) {
		WIN32_FIND_DATA_WtoU8(&fdat_w, fdat);
	}

	return	ret;
}

HANDLE CreateFileU8(const char *path, DWORD access_flg, DWORD share_flg, SECURITY_ATTRIBUTES *sa, DWORD create_flg, DWORD attr_flg, HANDLE hTemplate)
{
	Wstr wpath(path);
	return ::CreateFileW(wpath, access_flg, share_flg, sa, create_flg, attr_flg, hTemplate);
}

BOOL DeleteFileU8(const char *path)
{
	Wstr wpath(path);
	return ::DeleteFileW(wpath);
}

BOOL CreateDirectoryU8(const char *path, SECURITY_ATTRIBUTES *lsa)
{
	Wstr wpath(path);
	return ::CreateDirectoryW(wpath, lsa);
}

BOOL RemoveDirectoryU8(const char *path)
{
	Wstr wpath(path);
	return ::RemoveDirectoryW(wpath);
}

DWORD GetFullPathNameU8(const char *path, DWORD size, char *buf, char **fname)
{
	Wstr	wpath(path), wbuf(size);
	WCHAR	*wfname=NULL;

	DWORD	ret = ::GetFullPathNameW(wpath, size, wbuf.Buf(), &wfname);

	if (ret == 0 || ret > size)
		return	ret;

	int fname_len = wfname ? WtoU8(wfname, buf, size) : 0;
	int path_len  = WtoU8(wbuf, buf, size);
	*fname = wfname ? (buf + path_len - fname_len) : NULL;

	return	ret;
}

DWORD GetFileAttributesU8(const char *path)
{
	Wstr wpath(path);
	return ::GetFileAttributesW(wpath);
}

BOOL SetFileAttributesU8(const char *path, DWORD attr)
{
	Wstr	wpath(path);
	return	::SetFileAttributesW(wpath, attr);
}

HINSTANCE ShellExecuteU8(HWND hWnd, LPCSTR op, LPCSTR file, LPSTR params, LPCSTR dir, int nShow)
{
	Wstr	op_w(op), file_w(file), params_w(params), dir_w(dir);
	return	::ShellExecuteW(hWnd, op_w, file_w, params_w, dir_w, nShow);
}

BOOL ShellExecuteExU8(SHELLEXECUTEINFO *info)
{
	SHELLEXECUTEINFOW	info_w;
	memcpy(&info_w, info, sizeof(SHELLEXECUTEINFO));
	Wstr	verb_w(info->lpVerb), file_w(info->lpFile), param_w(info->lpParameters),
			dir_w(info->lpDirectory), class_w(info->lpClass);

	info_w.lpVerb		= verb_w;
	info_w.lpFile		= file_w;
	info_w.lpParameters	= param_w;
	info_w.lpDirectory	= dir_w;
	info_w.lpClass		= class_w;

	BOOL	ret = ::ShellExecuteExW(&info_w);

	info_w.lpFile		= (WCHAR *)info->lpFile;
	info_w.lpParameters	= (WCHAR *)info->lpParameters;
	info_w.lpDirectory	= (WCHAR *)info->lpDirectory;
	info_w.lpClass		= (WCHAR *)info->lpClass;
	memcpy(info, &info_w, sizeof(SHELLEXECUTEINFO));

	return	ret;
}

DWORD GetCurrentDirectoryU8(DWORD size, char *dir)
{
	Wstr	dir_w(size);
	DWORD	ret = ::GetCurrentDirectoryW(size, dir_w.Buf());
	if (ret > 0) {
		ret = WtoU8(dir_w, dir, size);
	}
	return	ret;
}

DWORD GetWindowsDirectoryU8(char *dir, DWORD size)
{
	Wstr	dir_w(size);
	DWORD	ret = ::GetWindowsDirectoryW(dir_w.Buf(), size);
	if (ret > 0) {
		ret = WtoU8(dir_w, dir, size);
	}
	return	ret;
}

BOOL SetCurrentDirectoryU8(char *dir)
{
	Wstr	dir_w(dir);
	return	::SetCurrentDirectoryW(dir_w);
}

BOOL GetOpenFileNameU8Core(LPOPENFILENAME ofn, BOOL (WINAPI *ofn_func)(OPENFILENAMEW*))
{
	OPENFILENAMEW	ofn_w;
	Wstr	filter_w(MAX_PATH), cfilter_w(ofn->nMaxCustFilter), file_w(ofn->nMaxFile), ftitle_w(ofn->nMaxFileTitle),
			idir_w(MAX_PATH), title_w(MAX_PATH), defext_w(MAX_PATH), template_w(MAX_PATH);

	memcpy(&ofn_w, ofn, sizeof(OPENFILENAME));

	WCHAR *wp=filter_w.Buf();
	for (const char *p=ofn->lpstrFilter; p && *p; p+=strlen(p)+1) {
		wp += U8toW(p, wp, MAX_PATH);
	}
	*wp = 0;
	U8toW(ofn->lpstrCustomFilter, cfilter_w.Buf(), ofn->nMaxCustFilter);
	U8toW(ofn->lpstrFile, file_w.Buf(), ofn->nMaxFile);
	U8toW(ofn->lpstrFileTitle, ftitle_w.Buf(), ofn->nMaxFileTitle);
	U8toW(ofn->lpstrInitialDir, idir_w.Buf(), MAX_PATH);
	U8toW(ofn->lpstrTitle, title_w.Buf(), MAX_PATH);
	U8toW(ofn->lpstrDefExt, defext_w.Buf(), MAX_PATH);
	U8toW(ofn->lpTemplateName, template_w.Buf(), MAX_PATH);

	if (ofn->lpstrFilter)		ofn_w.lpstrFilter		= filter_w;
	if (ofn->lpstrCustomFilter)	ofn_w.lpstrCustomFilter	= cfilter_w.Buf();
	if (ofn->lpstrFile)			ofn_w.lpstrFile			= file_w.Buf();
	if (ofn->lpstrFileTitle)	ofn_w.lpstrFileTitle	= ftitle_w.Buf();
	if (ofn->lpstrInitialDir)	ofn_w.lpstrInitialDir	= idir_w;
	if (ofn->lpstrTitle)		ofn_w.lpstrTitle		= title_w;
	if (ofn->lpstrDefExt)		ofn_w.lpstrDefExt		= defext_w;
	if (ofn->lpTemplateName)	ofn_w.lpTemplateName	= template_w;

	BOOL	ret = ofn_func(&ofn_w);

	if (ofn->lpstrCustomFilter)	WtoU8(cfilter_w, ofn->lpstrCustomFilter, MAX_PATH_U8);
	if (ofn->lpstrFileTitle)	WtoU8(ftitle_w, ofn->lpstrFileTitle, MAX_PATH_U8);
	if (ofn->lpstrFile) {
		if (ofn_w.Flags & OFN_ALLOWMULTISELECT) {
			const WCHAR *wp=file_w;
			for (char *p=ofn->lpstrFile; wp && *wp; wp+=wcslen(wp)+1) {
				p += WtoU8(wp, p, MAX_PATH_U8);
			}
			*p = 0;
		}
		else {
			WtoU8(file_w, ofn->lpstrFile, MAX_PATH_U8);
		}
	}
//	if (ofn_w.lpstrFile[ofn_w.nFileOffset])
		ofn->nFileOffset = ::WideCharToMultiByte(CP_UTF8, 0, ofn_w.lpstrFile, ofn_w.nFileOffset, 0, 0, 0, 0);

	return	ret;
}

BOOL GetOpenFileNameU8(LPOPENFILENAME ofn)
{
	return	GetOpenFileNameU8Core(ofn, GetOpenFileNameW);
}

BOOL GetSaveFileNameU8(LPOPENFILENAME ofn)
{
	return	GetOpenFileNameU8Core(ofn, GetSaveFileNameW);
}

/*
	リンクの解決
	あらかじめ、CoInitialize(NULL); を実行しておくこと
*/
BOOL ReadLink(LPCSTR src, LPSTR dest, LPSTR arg)
{
	IShellLink		*shellLink;
	IPersistFile	*persistFile;
	WORD			wbuf[MAX_PATH];
	BOOL			ret = FALSE;

	if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void **)&shellLink)))
	{
		if (SUCCEEDED(shellLink->QueryInterface(IID_IPersistFile, (void **)&persistFile)))
		{
			U8toW(src, wbuf, MAX_PATH);
			if (SUCCEEDED(persistFile->Load(wbuf, STGM_READ)))
			{
				if (SUCCEEDED(shellLink->GetPath((char *)wbuf, MAX_PATH, NULL, SLGP_SHORTPATH)))
				{
					WtoU8(wbuf, dest, MAX_PATH_U8);
					shellLink->GetArguments((char *)wbuf, MAX_PATH);
					WtoU8(wbuf, arg, MAX_PATH_U8);
					ret = TRUE;
				}
			}
			persistFile->Release();
		}
		shellLink->Release();
	}
	return	ret;
}


/*=========================================================================
	GetLoadStrA/W/U8
=========================================================================*/
LPSTR GetLoadStrA(UINT resId, HINSTANCE hI)
{
	static TResHash	*hash;

	if (hash == NULL) {
		hash = new TResHash(200);
	}

	char		buf[1024];
	TResHashObj	*obj;

	if ((obj = hash->Search(resId)) == NULL) {
		if (::LoadStringA(hI ? hI : defaultInstance, resId, buf, sizeof(buf)) >= 0) {
			obj = new TResHashObj(resId, strdup(buf));
			hash->Register(obj);
		}
	}
	return	obj ? (char *)obj->val : NULL;
}

LPWSTR GetLoadStrW(UINT resId, HINSTANCE hI)
{
	static TResHash	*hash;

	if (hash == NULL) {
		hash = new TResHash(200);
	}

	WCHAR		buf[1024];
	TResHashObj	*obj;

	if ((obj = hash->Search(resId)) == NULL) {
		if (::LoadStringW(hI ? hI : defaultInstance, resId, buf, sizeof(buf) / sizeof(WCHAR)) >= 0) {
			obj = new TResHashObj(resId, wcsdup(buf));
			hash->Register(obj);
		}
	}
	return	obj ? (LPWSTR)obj->val : NULL;
}

LPSTR GetLoadStr(UINT resId, HINSTANCE hI)
{
	static TResHash	*hash;

	if (hash == NULL) {
		hash = new TResHash(200);
	}

	WCHAR		buf[1024];
	TResHashObj	*obj;

	if ((obj = hash->Search(resId)) == NULL) {
		if (::LoadStringW(hI ? hI : defaultInstance, resId, buf, sizeof(buf) / sizeof(WCHAR)) >= 0) {
			obj = new TResHashObj(resId, WtoU8(buf, TRUE));
			hash->Register(obj);
		}
	}
	return	obj ? (char *)obj->val : NULL;
}

/*=========================================================================
	TResHash for internal use
=========================================================================*/
TResHash::TResHash(int _hashNum)
{
	hashNum = _hashNum;
	hashTbl = new TResHashObj *[hashNum];
	memset(hashTbl, 0, sizeof(TResHashObj *) * hashNum);
}

BOOL TResHash::Register(TResHashObj *target)
{
	TResHashObj **obj;

	for (obj = &hashTbl[target->resId % hashNum]; *obj; obj=&(*obj)->next)
		;
	*obj = target;
	return	TRUE;
}

TResHashObj *TResHash::Search(UINT resId)
{
	for (TResHashObj *obj = hashTbl[resId % hashNum]; obj; obj=obj->next) {
		if (obj->resId == resId)
			return	obj;
	}
	return	NULL;
}


/*=========================================================================
	LCID
=========================================================================*/
static LCID defaultLCID;

void TSetDefaultLCID(LCID lcid)
{
	defaultLCID = lcid ? lcid : ::GetSystemDefaultLCID();
	::SetThreadLocale(defaultLCID);
}

HMODULE TLoadLibrary(LPTSTR dllname)
{
	HMODULE	hModule = ::LoadLibrary(dllname);

	if (defaultLCID)
		::SetThreadLocale(defaultLCID);

	return	hModule;
}

/*=========================================================================
	パス合成（ANSI 版）
=========================================================================*/
int MakePath(char *dest, const char *dir, const char *file)
{
	BOOL	separetor = TRUE;
	int		len;

	if ((len = strlen(dir)) == 0)
		return	wsprintf(dest, "%s", file);

	if (dir[len -1] == '\\')	// 表など、2byte目が'\\'で終る文字列対策
	{
		if (len >= 2 && IsDBCSLeadByte(dir[len -2]) == FALSE)
			separetor = FALSE;
		else {
			for (u_char *p=(u_char *)dir; *p && p[1]; IsDBCSLeadByte(*p) ? p+=2 : p++)
				;
			if (*p == '\\')
				separetor = FALSE;
		}
	}
	return	wsprintf(dest, "%s%s%s", dir, separetor ? "\\" : "", file);
}

/*=========================================================================
	パス合成（UNICODE 版）
=========================================================================*/
int MakePathW(WCHAR *dest, const WCHAR *dir, const WCHAR *file)
{
	int		len;

	if ((len = wcslen(dir)) == 0)
		return	wsprintfW(dest, L"%s", file);

	return	wsprintfW(dest, L"%s%s%s", dir, dir[len -1] == L'\\' ? L"" : L"\\" , file);
}

WCHAR lGetCharIncW(const WCHAR **str)
{
	return	*(*str)++;
}

WCHAR lGetCharIncA(const char **str)
{
	WCHAR	ch = *(*str)++;

	if (IsDBCSLeadByte((BYTE)ch)) {
		ch <<= BITS_OF_BYTE;
		ch |= *(*str)++;	// null 判定は手抜き
	}
	return	ch;
}

WCHAR lGetCharW(const WCHAR *str, int offset)
{
	return	str[offset];
}

WCHAR lGetCharA(const char *str, int offset)
{
	while (offset-- > 0)
		lGetCharIncA(&str);

	return	lGetCharIncA(&str);
}

void lSetCharW(WCHAR *str, int offset, WCHAR ch)
{
	str[offset] = ch;
}

void lSetCharA(char *str, int offset, WCHAR ch)
{
	while (offset-- > 0) {
		if (IsDBCSLeadByte(*str++))
			*str++;
	}

	BYTE	high_ch = ch >> BITS_OF_BYTE;

	if (high_ch)
		*str++ = high_ch;
	*str = (BYTE)ch;
}

/*
	nul文字を必ず付与する strncpy
*/
char *strncpyz(char *dest, const char *src, int num)
{
	char	*sv = dest;

	while (num-- > 0)
		if ((*dest++ = *src++) == '\0')
			return	sv;

	if (sv != dest)		// num > 0
		*(dest -1) = 0;
	return	sv;
}

/*
	大文字小文字を無視する strncmp
*/
int strncmpi(const char *str1, const char *str2, int num)
{
	for (int cnt=0; cnt < num; cnt++)
	{
		char	c1 = toupper(str1[cnt]), c2 = toupper(str2[cnt]);

		if (c1 == c2)
		{
			if (c1)
				continue;
			else
				return	0;
		}
		if (c1 > c2)
			return	1;
		else
			return	-1;
	}
	return	0;
}


/*=========================================================================
	Win32(W) API UTF8 wrapper
=========================================================================*/
BOOL GetMenuStringU8(HMENU hMenu, UINT uItem, char *buf, int bufsize, UINT flags)
{
	WCHAR	*wbuf = new WCHAR [bufsize];
	BOOL	ret = ::GetMenuStringW(hMenu, uItem, wbuf, bufsize, flags);
	if (ret) {
		WtoU8(wbuf, buf, bufsize);
	}
	delete wbuf;
	return	ret;
}

DWORD GetModuleFileNameU8(HMODULE hModule, char *buf, DWORD bufsize)
{
	WCHAR	*wbuf = new WCHAR [bufsize];
	DWORD	ret = ::GetModuleFileNameW(hModule, wbuf, bufsize);
	if (ret) {
		WtoU8(wbuf, buf, bufsize);
	}
	delete wbuf;
	return	ret;
}

UINT GetDriveTypeU8(const char *path)
{
	Wstr	wpath(path);

	return	::GetDriveTypeW(wpath);
}

/*=========================================================================
	UTF8 string utilitys
=========================================================================*/



/*=========================================================================
	UCS2(W) - UTF-8(U8) - ANSI(A) 相互変換
=========================================================================*/
WCHAR *AtoW(const char *src, BOOL noStatic)
{
	static	WCHAR	*_wbuf = NULL;

	WCHAR	*wtmp = NULL;
	WCHAR	*&wbuf = noStatic ? wtmp : _wbuf;

	if (wbuf) {
		delete [] wbuf;
		wbuf = NULL;
	}

	int		len;
	if ((len = AtoW(src, NULL, 0)) > 0) {
		wbuf = new WCHAR [len];
		AtoW(src, wbuf, len);
	}
	return	wbuf;
}

WCHAR *U8toW(const char *src, BOOL noStatic)
{
	static	WCHAR	*_wbuf = NULL;

	WCHAR	*wtmp = NULL;
	WCHAR	*&wbuf = noStatic ? wtmp : _wbuf;

	if (wbuf) {
		delete [] wbuf;
		wbuf = NULL;
	}

	int		len;
	if ((len = U8toW(src, NULL, 0)) > 0) {
		wbuf = new WCHAR [len];
		U8toW(src, wbuf, len);
	}
	return	wbuf;
}

char *WtoU8(const WCHAR *src, BOOL noStatic)
{
	static	char	*_buf = NULL;

	char	*tmp = NULL;
	char	*&buf = noStatic ? tmp : _buf;

	if (buf) {
		delete [] buf;
		buf = NULL;
	}

	int		len;
	if ((len = WtoU8(src, NULL, 0)) > 0) {
		buf = new char [len];
		WtoU8(src, buf, len);
	}
	return	buf;
}

char *WtoA(const WCHAR *src, BOOL noStatic)
{
	static	char	*_buf = NULL;

	char	*tmp = NULL;
	char	*&buf = noStatic ? tmp : _buf;

	if (buf) {
		delete [] buf;
		buf = NULL;
	}

	int		len;
	if ((len = WtoA(src, NULL, 0)) > 0) {
		buf = new char [len];
		WtoA(src, buf, len);
	}
	return	buf;
}

char *AtoU8(const char *src, BOOL noStatic)
{
	static	char	*_buf = NULL;

	char	*tmp = NULL;
	char	*&buf = noStatic ? tmp : _buf;

	if (buf) {
		delete [] buf;
		buf = NULL;
	}

	WCHAR	*wsrc = AtoW(src, TRUE);
	if (wsrc) {
		buf = WtoU8(wsrc, TRUE);
	}
	delete [] wsrc;
	return	buf;
}

char *U8toA(const char *src, BOOL noStatic)
{
	static	char	*_buf = NULL;

	char	*tmp = NULL;
	char	*&buf = noStatic ? tmp : _buf;

	if (buf) {
		delete [] buf;
		buf = NULL;
	}

	WCHAR	*wsrc = U8toW(src, TRUE);
	if (wsrc) {
		buf = WtoA(wsrc, TRUE);
	}
	delete [] wsrc;
	return	buf;
}

char *strdupNew(const char *_s)
{
	int		len = strlen(_s) + 1;
	char	*s = new char [len];
	memcpy(s, _s, len);
	return	s;
}

WCHAR *wcsdupNew(const WCHAR *_s)
{
	int		len = wcslen(_s) + 1;
	WCHAR	*s = new WCHAR [len];
	memcpy(s, _s, len * sizeof(WCHAR));
	return	s;
}

/*=========================================================================
	Debug
=========================================================================*/
void Debug(char *fmt,...)
{
	static char buf[8192];

	va_list	ap;
	va_start(ap, fmt);
	_vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	::OutputDebugString(buf);
}

/*=========================================================================
	例外情報取得
=========================================================================*/
static char *ExceptionTitle;
static char *ExceptionLogFile;
static char *ExceptionLogInfo;
#define STACKDUMP_SIZE		256
#define MAX_STACKDUMP_SIZE	8192

LONG WINAPI Local_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *info)
{
	static char			buf[(STACKDUMP_SIZE/sizeof(DWORD)) * 10 + 100];	// 10 ... %08x + \r\n
	static HANDLE		hFile;
	static SYSTEMTIME	tm;
	static CONTEXT		*context;
	static DWORD		len, i, j;
	static char			*stack;

	hFile = ::CreateFile(ExceptionLogFile, GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
	::SetFilePointer(hFile, 0, 0, FILE_END);
	::GetLocalTime(&tm);
	context = info->ContextRecord;

	len = sprintf(buf,
		"------ %s -----\r\n"
		" Date        : %d/%02d/%02d %02d:%02d:%02d\r\n"
		" Code/Addr   : %X / %p\r\n"
		" AX/BX/CX/DX : %08x / %08x / %08x / %08x\r\n"
		" SI/DI/BP/SP : %08x / %08x / %08x / %08x\r\n"
		"------- stack info -----\r\n"
		, ExceptionTitle
		, tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond
		, info->ExceptionRecord->ExceptionCode, info->ExceptionRecord->ExceptionAddress
		, context->Eax, context->Ebx, context->Ecx, context->Edx
		, context->Esi, context->Edi, context->Ebp, context->Esp
		);
	::WriteFile(hFile, buf, len, &len, 0);

	for (i=0; i < MAX_STACKDUMP_SIZE / STACKDUMP_SIZE; i++) {
		stack = (char *)context->Esp + (i * STACKDUMP_SIZE);
		if (::IsBadReadPtr(stack, STACKDUMP_SIZE))
			break;
		len = 0;
		for (j=0; j < STACKDUMP_SIZE / sizeof(DWORD); j++)
			len += sprintf(buf + len, "%08x%s", ((DWORD *)stack)[j], ((j+1)%8) ? " " : "\r\n");
		::WriteFile(hFile, buf, len, &len, 0);
	}

	len = sprintf(buf, "------------------------\r\n\r\n");
	::WriteFile(hFile, buf, len, &len, 0);
	::CloseHandle(hFile);

	sprintf(buf, ExceptionLogInfo, ExceptionLogFile);
	::MessageBox(0, buf, ExceptionTitle, MB_OK);

	return	EXCEPTION_EXECUTE_HANDLER;
}

BOOL InstallExceptionFilter(char *title, char *info)
{
	char	buf[MAX_PATH_U8];

	::GetModuleFileName(NULL, buf, sizeof(buf));
	strcpy(strrchr(buf, '.'), "_exception.log");
	ExceptionLogFile = strdup(buf);
	ExceptionTitle = strdup(title);
	ExceptionLogInfo = info;

	::SetUnhandledExceptionFilter(&Local_UnhandledExceptionFilter);
	return	TRUE;
}

