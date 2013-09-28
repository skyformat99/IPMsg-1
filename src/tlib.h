/* @(#)Copyright (C) H.Shirouzu 1996-2005   tlib.h	Ver0.97 */
/* ========================================================================
	Project  Name			: Win32 Lightweight  Class Library Test
	Module Name				: Main Header
	Create					: 1996-06-01(Sat)
	Update					: 2005-11-28(Mon)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#ifndef TLIB_H
#define TLIB_H

#ifndef STRICT
#define STRICT
#endif

/* for crypto api */
#define _WIN32_WINNT 0x0600

#include <windows.h>
#include <windowsx.h>

#include "commctrl.h"
#include <regstr.h>
#include <shlobj.h>
#include <tchar.h>

#define BFFM_SETSELECTIONW (WM_USER + 103)
#define LVM_INSERTITEMW (LVM_FIRST + 77)
DEFINE_GUID(IID_IShellLinkW, 0x000214F9, 0x0000, 0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

#ifdef MS_VC4

typedef struct _browseinfoA {
    HWND        hwndOwner;
    LPCITEMIDLIST pidlRoot;
    LPSTR        pszDisplayName;        // Return display name of item selected.
    LPCSTR       lpszTitle;                     // text to go in the banner over the tree.
    UINT         ulFlags;                       // Flags that control the return stuff
    BFFCALLBACK  lpfn;
    LPARAM       lParam;                        // extra info that's passed back in callbacks
    int          iImage;                        // output var: where to return the Image index.
} BROWSEINFOA, *PBROWSEINFOA, *LPBROWSEINFOA;

typedef struct _browseinfoW {
    HWND        hwndOwner;
    LPCITEMIDLIST pidlRoot;
    LPWSTR       pszDisplayName;        // Return display name of item selected.
    LPCWSTR      lpszTitle;                     // text to go in the banner over the tree.
    UINT         ulFlags;                       // Flags that control the return stuff
    BFFCALLBACK  lpfn;
    LPARAM       lParam;                        // extra info that's passed back in callbacks
    int          iImage;                        // output var: where to return the Image index.
} BROWSEINFOW, *PBROWSEINFOW, *LPBROWSEINFOW;

extern BOOL	(WINAPI *SHGetPathFromIDListW)(LPCITEMIDLIST, void *);
extern LPITEMIDLIST (WINAPI *SHBrowseForFolderW)(BROWSEINFOW *);
#endif

extern LPITEMIDLIST (WINAPI *ILCreateFromPathW)(void *);
extern void (WINAPI *ILFreeW)(LPITEMIDLIST);

#define WINEXEC_ERR_MAX		31
#define TLIB_SLEEPTIMER		32000

#define IsNewShell()	(LOBYTE(LOWORD(GetVersion())) >= 4)
#define IsWin95()		(LOBYTE(LOWORD(GetVersion())) >= 4 && GetVersion() >= 0x80000000)
#define IsWinNT()		(LOBYTE(LOWORD(GetVersion())) >= 4 && GetVersion() < 0x80000000)
#define IsWin2K()		(LOBYTE(LOWORD(GetVersion())) >= 5 && GetVersion() < 0x80000000)
#define IsWinVista()	(LOBYTE(LOWORD(GetVersion())) >= 6 && GetVersion() < 0x80000000)
#define IsWin31()		(LOBYTE(LOWORD(GetVersion())) == 3 && HIBYTE(LOWORD(GetVersion())) < 20)
#define IsNT350()		(LOBYTE(LOWORD(GetVersion())) == 3 && HIBYTE(LOWORD(GetVersion())) == 50)

#define IsLang(lang)	(PRIMARYLANGID(LANGIDFROMLCID(GetThreadLocale())) == lang)

#define BUTTON_CLASS		_T("BUTTON")
#define COMBOBOX_CLASS		_T("COMBOBOX")
#define EDIT_CLASS			_T("EDIT")
#define LISTBOX_CLASS		_T("LISTBOX")
#define MDICLIENT_CLASS		_T("MDICLIENT")
#define SCROLLBAR_CLASS		_T("SCROLLBAR")
#define STATIC_CLASS		_T("STATIC")

#define MAX_WPATH		32000
#define MAX_PATH_EX		(MAX_PATH * 8)
#define MAX_PATH_U8		(MAX_PATH * 3)

#define BITS_OF_BYTE	8
#define BYTE_NUM		256

#ifndef EM_SETTARGETDEVICE
#define COLOR_BTNFACE           15
#define COLOR_3DFACE            COLOR_BTNFACE
#define EM_SETBKGNDCOLOR		(WM_USER + 67)
#define EM_SETTARGETDEVICE		(WM_USER + 72)
#endif

struct WINPOS {
	int		x;
	int		y;
	int		cx;
	int		cy;
};

typedef DWORD HashID;

class THash;

class THashObj {
protected:
	THashObj	*priorHash;
	THashObj	*nextHash;
	HashID		id;

public:
	THashObj() { priorHash = nextHash = NULL; id = 0; }
	~THashObj() { if (priorHash && priorHash != this) UnlinkHash(); }

	BOOL LinkHash(THashObj *top, HashID _id);
	BOOL UnlinkHash();
	friend THash;
};

class THash {
protected:
	THashObj	*hashTbl;
	int			hashNum;
	int			registerNum;

public:
	THash(int _hashNum);
	~THash();
	void Register(THashObj *obj, HashID id);
	void UnRegister(THashObj *obj);
	THashObj *GetHashObj(HashID id);
	DWORD MakeHash(HashID id) { return	id * 0xF3F77D13; }
	int	GetRegisterNum() { return	registerNum; }
};

class TWin : public THashObj {
protected:
	RECT			rect;
	HACCEL			hAccel;
	TWin			*parent;
	BOOL			sleepBusy;	// for TWin::Sleep() only

public:
	TWin(TWin *_parent = NULL);
	virtual	~TWin();

	HWND			hWnd;

	virtual void	Show(int mode = SW_SHOWDEFAULT);
	virtual BOOL	Create(LPCTSTR className=NULL, LPCTSTR title=_T(""), DWORD style=(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN), DWORD exStyle=0, HMENU hMenu=NULL);
	virtual	void	Destroy(void);

	virtual BOOL	EvCommand(WORD wNotifyCode, WORD wID, LPARAM hwndCtl);
	virtual BOOL	EvSysCommand(WPARAM uCmdType, POINTS pos);
	virtual BOOL	EvCreate(LPARAM lParam);
	virtual BOOL	EvClose(void);
	virtual BOOL	EvNcDestroy(void);
	virtual BOOL	EvQueryEndSession(BOOL nSession, BOOL nLogOut);
	virtual BOOL	EvEndSession(BOOL nSession, BOOL nLogOut);
	virtual BOOL	EvQueryOpen(void);
	virtual BOOL	EvPaint(void);
	virtual BOOL	EvNcPaint(HRGN hRgn);
	virtual BOOL	EvSize(UINT fwSizeType, WORD nWidth, WORD nHeight);
	virtual BOOL	EvShowWindow(BOOL fShow, int fnStatus);
	virtual BOOL	EvGetMinMaxInfo(MINMAXINFO *info);
	virtual BOOL	EvTimer(WPARAM timerID, TIMERPROC proc);
	virtual BOOL	EvSetCursor(HWND cursorWnd, WORD nHitTest, WORD wMouseMsg);
	virtual BOOL	EvMouseMove(UINT fwKeys, POINTS pos);
	virtual BOOL	EvNcHitTest(POINTS pos, LRESULT *result);
	virtual BOOL	EvMeasureItem(UINT ctlID, MEASUREITEMSTRUCT *lpMis);
	virtual BOOL	EvDrawItem(UINT ctlID, DRAWITEMSTRUCT *lpDis);
	virtual BOOL	EvMenuSelect(UINT uItem, UINT fuFlag, HMENU hMenu);
	virtual BOOL	EvDropFiles(HDROP hDrop);
	virtual BOOL	EvNotify(UINT ctlID, NMHDR *pNmHdr);
	virtual BOOL	EvContextMenu(HWND childWnd, POINTS pos);
	virtual BOOL	EvHotKey(int hotKey);

	virtual BOOL	EventScroll(UINT uMsg, int nCode, int nPos, HWND scrollBar);

	virtual BOOL	EventButton(UINT uMsg, int nHitTest, POINTS pos);
	virtual BOOL	EventKey(UINT uMsg, int nVirtKey, LONG lKeyData);
	virtual BOOL	EventInitMenu(UINT uMsg, HMENU hMenu, UINT uPos, BOOL fSystemMenu);
	virtual BOOL	EventCtlColor(UINT uMsg, HDC hDcCtl, HWND hWndCtl, HBRUSH *result);
	virtual BOOL	EventFocus(UINT uMsg, HWND focusWnd);
	virtual BOOL	EventSystem(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL	EventUser(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual UINT	GetDlgItemText(int ctlId, LPTSTR buf, int len);
	virtual UINT	GetDlgItemTextW(int ctlId, WCHAR *buf, int len);
	virtual BOOL	SetDlgItemText(int ctlId, LPCTSTR buf);
	virtual BOOL	SetDlgItemTextW(int ctlId, const WCHAR *buf);
	virtual int		GetDlgItemInt(int ctlId, BOOL *err=NULL, BOOL sign=TRUE);
	virtual BOOL	SetDlgItemInt(int ctlId, int val, BOOL sign=TRUE);
	virtual HWND	GetDlgItem(int ctlId);
	virtual BOOL	CheckDlgButton(int ctlId, UINT check);
	virtual UINT	IsDlgButtonChecked(int ctlId);
	virtual	int		MessageBox(LPCTSTR msg, LPCTSTR title=_T("msg"), UINT style=MB_OK);
	virtual	int		MessageBoxW(WCHAR *msg, WCHAR *title=L"", UINT style=MB_OK);
	virtual BOOL	BringWindowToTop(void);
	virtual BOOL	SetForegroundWindow(void);
	virtual BOOL	ShowWindow(int mode);
	virtual BOOL	SetForceForegroundWindow(void);
	virtual BOOL	PostMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL	PostMessageW(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT	SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT	SendMessageW(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LONG	SendDlgItemMessage(int ctlId, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LONG	SendDlgItemMessageW(int ctlId, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL	GetWindowRect(RECT *_rect=NULL);
	virtual BOOL	SetWindowPos(HWND hInsAfter, int x, int y, int cx, int cy, UINT fuFlags);
	virtual HWND	SetActiveWindow(void);
	virtual int		GetWindowText(LPTSTR text, int size);
	virtual BOOL	GetWindowTextW(WCHAR *text, int size);
	virtual BOOL	SetWindowText(LPCTSTR text);
	virtual BOOL	SetWindowTextW(const WCHAR *text);
	virtual int		GetWindowTextLength(void);
	virtual int		GetWindowTextLengthW(void);

	virtual LONG	SetWindowLong(int index, LONG val);
	virtual WORD	SetWindowWord(int index, WORD val);
	virtual LONG	GetWindowLong(int index);
	virtual WORD	GetWindowWord(int index);
	virtual TWin	*GetParent(void) { return parent; };
	virtual void	SetParent(TWin *_parent) { parent = _parent; };
	virtual BOOL	MoveWindow(int x, int y, int cx, int cy, int bRepaint);
	virtual BOOL	Sleep(UINT mSec);
	virtual BOOL	Idle(void);
	virtual RECT	*Rect() { return &rect; }

	virtual	BOOL	PreProcMsg(MSG *msg);
	virtual	LRESULT	WinProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual	LRESULT	DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class TDlg : public TWin {
protected:
	UINT	resId;
	BOOL	modalFlg;

public:
	TDlg(UINT	resid, TWin *_parent = NULL);
	virtual ~TDlg();

	virtual BOOL	Create(HINSTANCE hI = NULL);
	virtual	void	Destroy(void);
	virtual int		Exec(void);
	virtual void	EndDialog(int);
	UINT			ResId(void) { return resId; }

	virtual BOOL	EvCreate(LPARAM lParam);
	virtual BOOL	EvCommand(WORD wNotifyCode, WORD wID, LPARAM hwndCtl);
	virtual BOOL	EvSysCommand(WPARAM uCmdType, POINTS pos);
	virtual BOOL	EvQueryOpen(void);

	virtual	BOOL	PreProcMsg(MSG *msg);
	virtual LRESULT	WinProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class TSubClass : public TWin {
protected:
	WNDPROC		oldProc;

public:
	TSubClass(TWin *_parent = NULL);

	virtual BOOL	CreateByWnd(HWND _hWnd);
	virtual	LRESULT	DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class TSubClassCtl : public TSubClass {
protected:
public:
	TSubClassCtl(TWin *_parent);

	virtual	BOOL	PreProcMsg(MSG *msg);
};

BOOL TRegisterClass(LPCTSTR class_name, UINT style=CS_DBLCLKS, HICON hIcon=0, HCURSOR hCursor=0, HBRUSH hbrBackground=0, int classExtra=0, int wndExtra=0, LPCTSTR menu_str=0);

class TApp {
protected:
	static TApp	*tapp;
	THash		*hash;
	LPCSTR		defaultClass;

	LPSTR		cmdLine;
	int			nCmdShow;
	TWin		*mainWnd;
	TWin		*preWnd;
	HINSTANCE	hI;

	TWin			*SearchWnd(HWND hWnd) { return (TWin *)hash->GetHashObj((HashID)hWnd); }
	virtual BOOL	InitApp(void);

public:
	TApp(HINSTANCE _hI, LPSTR _cmdLine, int _nCmdShow);
	virtual ~TApp();
	virtual void	InitWindow() = 0;
	virtual int		Run();

	LPCTSTR	GetDefaultClass() { return defaultClass; }
	void	AddWin(TWin *win) { preWnd = win; }
	void	AddWinByWnd(TWin *win, HWND hWnd) { win->hWnd = hWnd; hash->Register(win, (HashID)win->hWnd); }
	void	DelWin(TWin *win) { hash->UnRegister(win); }
	BOOL	PreProcMsg(MSG *msg);

	static TApp *GetApp() { return tapp; }
	static HINSTANCE GetInstance() { return tapp->hI; }
	static LRESULT CALLBACK WinProc(HWND hW, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

struct TListObj {
	TListObj *prior, *next;
};

class TList {
protected:
	TListObj	top;

public:
	TList(void);
	void		Init(void);
	void		AddObj(TListObj *obj);
	void		DelObj(TListObj *obj);
	TListObj	*TopObj(void);
	TListObj	*NextObj(TListObj *obj);
	BOOL		IsEmpty() { return	top.next == &top; }
	void		MoveList(TList *from_list);
};

#define FREE_LIST	0
#define USED_LIST	1
#define	RLIST_MAX	2
class TRecycleList {
protected:
	char	*data;
	TList	list[RLIST_MAX];

public:
	TRecycleList(int init_cnt, int size);
	~TRecycleList();
	TListObj *GetObj(int list_type);
	void PutObj(int list_type, TListObj *obj);
};

#define MAX_KEYARRAY	30

class TRegistry {
protected:
	HKEY	topKey;
	int		openCnt;
	HKEY	hKey[MAX_KEYARRAY];

public:
	TRegistry(LPCSTR company, LPSTR appName=NULL);
	TRegistry(HKEY top_key);
	~TRegistry();

	void	ChangeTopKey(HKEY topKey);
	BOOL	ChangeApp(LPCSTR company, LPSTR appName=NULL);
	BOOL	GetInt(LPCSTR key, int *val);
	BOOL	SetInt(LPCSTR key, int val);
	BOOL	GetLong(LPCSTR key, long *val);
	BOOL	SetLong(LPCSTR key, long val);
	BOOL	GetStr(LPCSTR key, LPSTR str, int size);
	BOOL	GetStrA(LPCSTR key, LPSTR str, int size);
	BOOL	SetStr(LPCSTR key, LPCSTR str);
	BOOL	SetStrA(LPCSTR key, LPCSTR str);
	BOOL	GetByte(LPCSTR key, BYTE *data, int *size);
	BOOL	SetByte(LPCSTR key, const BYTE *data, int size);
	BOOL	OpenKey(LPCSTR subKey, BOOL createFlg=FALSE);
	BOOL	CreateKey(LPCSTR subKey) { return OpenKey(subKey, TRUE); }
	BOOL	CloseKey(void);
	BOOL	DeleteKey(LPCSTR str);
	BOOL	DeleteValue(LPCSTR str);
	BOOL	EnumKey(DWORD cnt, LPSTR buf, int size);
	BOOL	EnumValue(DWORD cnt, LPSTR buf, int size, DWORD *type=NULL);
	BOOL	DeleteChildTree(LPSTR subkey=NULL);
};

class TInifile {
protected:
	char	*ini_file;
	char	*cur_section;

public:
	TInifile(char *ini_name=NULL);
	~TInifile();
	void Init(char *ini_name=NULL);
	void SetSection(char *section);
	BOOL SetStr(const char *key, const char *val);
	DWORD GetStr(const char *key, char *val, int max_size, const char *default_val="");
	BOOL SetInt(const char *key, int val);
	BOOL DelSection(const char *section);
	BOOL DelKey(const char *key);
	int GetInt(const char *key, int default_val=-1);
	const char *GetIniFileName(void) { return	ini_file; }
};

/* for internal use */
struct TResHashObj {
	TResHashObj	*prior;
	TResHashObj	*next;
	UINT		resId;
	void		*val;
	TResHashObj(UINT _resId, void *_val=NULL) { prior = next = NULL; resId = _resId; val = _val; }
};

/* for internal use */
class TResHash {
protected:
	int			hashNum;
	TResHashObj	**hashTbl;

public:
	TResHash(int _hashNum);
	BOOL		Register(TResHashObj *);
	TResHashObj	*Search(UINT id);
};

struct WIN32_FIND_DATA_U8 {
	DWORD		dwFileAttributes;
	FILETIME	ftCreationTime;
	FILETIME	ftLastAccessTime;
	FILETIME	ftLastWriteTime;
	DWORD		nFileSizeHigh;
	DWORD		nFileSizeLow;
	DWORD		dwReserved0;
	DWORD		dwReserved1;
	char		cFileName[ MAX_PATH_U8 ];
	char		cAlternateFileName[ 14 * 3 ];
};

void InitInstanceForLoadStr(HINSTANCE hI);
void InitGlobalItems();
LPSTR GetLoadStr(UINT resId, HINSTANCE hI=NULL);
LPSTR GetLoadStrA(UINT resId, HINSTANCE hI=NULL);
LPWSTR GetLoadStrW(UINT resId, HINSTANCE hI=NULL);
void TSetDefaultLCID(LCID id=0);
HMODULE TLoadLibrary(LPTSTR dllname);
int MakePath(char *dest, const char *dir, const char *file);
int MakePathW(WCHAR *dest, const WCHAR *dir, const WCHAR *file);
WCHAR lGetCharIncW(const WCHAR **str);
WCHAR lGetCharIncA(const char **str);
WCHAR lGetCharW(const WCHAR *str, int);
WCHAR lGetCharA(const char *str, int);
void lSetCharW(WCHAR *str, int offset, WCHAR ch);
void lSetCharA(char *str, int offset, WCHAR ch);

#define CP_UTF8                   65001       // UTF-8 translation
inline int AtoW(const char *src, WCHAR *dst, int bufsize, int max_len=-1) {
	return	::MultiByteToWideChar(CP_ACP, 0, src, max_len, dst, bufsize);
}
inline int WtoA(const WCHAR *src, char *dst, int bufsize, int max_len=-1) {
	return	::WideCharToMultiByte(CP_ACP, 0, src, max_len, dst, bufsize, 0, 0);
}
inline int WtoU8(const WCHAR *src, char *dst, int bufsize, int max_len=-1) {
	return	::WideCharToMultiByte(CP_UTF8, 0, src, max_len, dst, bufsize, 0, 0);
}
inline int U8toW(const char *src, WCHAR *dst, int bufsize, int max_len=-1) {
	return	::MultiByteToWideChar(CP_UTF8, 0, src, max_len, dst, bufsize);
}

WCHAR *AtoW(const char *src, BOOL noStatic=FALSE);
WCHAR *U8toW(const char *src, BOOL noStatic=FALSE);
char *WtoU8(const WCHAR *src, BOOL noStatic=FALSE);
char *WtoA(const WCHAR *src, BOOL noStatic=FALSE);
char *AtoU8(const char *src, BOOL noStatic=FALSE);
char *U8toA(const char *src, BOOL noStatic=FALSE);

char *strdupNew(const char *_s);
WCHAR *wcsdupNew(const WCHAR *_s);

// Win32(W) API UTF8 wrapper
BOOL GetMenuStringU8(HMENU hMenu, UINT uItem, char *buf, int bufsize, UINT flags);
DWORD GetModuleFileNameU8(HMODULE hModule, char *buf, DWORD bufsize);
UINT GetDriveTypeU8(const char *path);

// UTF8 string class
enum StrFlg { BY_UTF8, BY_MBCS };

class U8str {
	char	*s;
public:
	U8str(const WCHAR *_s=NULL) { s = _s ? WtoU8(_s, TRUE) : NULL; }
	U8str(const char *_s, StrFlg flg=BY_UTF8) { s = _s ? flg == BY_UTF8 ? strdupNew(s) : AtoU8(_s, TRUE) : NULL; }
	U8str(int len) { if (len) { s = new char [len]; *s = 0; } else { s = NULL; } }
	~U8str() { delete [] s; }
	operator const char *() { return s; }
	char	*Buf() { return s; }
};

class Wstr {
	WCHAR	*s;
public:
	Wstr(const char *_s, StrFlg flg=BY_UTF8) { s = _s ? flg == BY_UTF8 ? U8toW(_s, TRUE) : AtoW(_s, TRUE) : NULL; }
	Wstr(int len) { if (len) { s = new WCHAR [len]; *s = 0; } else { s = NULL; } }
	~Wstr() { delete [] s; }
	operator const WCHAR *() { return s; }
	WCHAR	*Buf() { return s; }
};

class MBCSstr {
	char	*s;
public:
	MBCSstr(const WCHAR *_s=NULL) { s = _s ? WtoA(_s, TRUE) : NULL; }
	MBCSstr(const char *_s, StrFlg flg=BY_UTF8) { s = _s ? flg == BY_UTF8 ? U8toA(_s, TRUE) : strdupNew(s) : NULL; }
	MBCSstr(int len) { if (len) { s = new char [len]; *s = 0; } else { s = NULL; } }
	~MBCSstr() { delete [] s; }
	operator const char *() { return s; }
	char	*Buf() { return s; }
};

HWND CreateWindowU8(const char *class_name, const char *window_name, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU hMenu, HINSTANCE hInst, void *param);
HWND FindWindowU8(const char *class_name, const char *window_name=NULL);
BOOL AppendMenuU8(HMENU hMenu, UINT flags, UINT idItem, const char *item_str);
BOOL InsertMenuU8(HMENU hMenu, UINT idItem, UINT flags, UINT idNewItem, const char *item_str);
BOOL ModifyMenuU8(HMENU hMenu, UINT idItem, UINT flags, UINT idNewItem, const char *item_str);
DWORD GetFileAttributesU8(const char *path);
BOOL SetFileAttributesU8(const char *path, DWORD attr);

UINT DragQueryFileU8(HDROP hDrop, UINT iFile, char *buf, UINT cb);
void WIN32_FIND_DATA_WtoU8(const WIN32_FIND_DATAW *fdat_w, WIN32_FIND_DATA_U8 *fdat_u8, BOOL include_fname=TRUE);
HANDLE FindFirstFileU8(const char *path, WIN32_FIND_DATA_U8 *fdat);
BOOL FindNextFileU8(HANDLE hDir, WIN32_FIND_DATA_U8 *fdat);
DWORD GetFullPathNameU8(const char *path, DWORD size, char *buf, char **fname);
HANDLE CreateFileU8(const char *path, DWORD access_flg, DWORD share_flg, SECURITY_ATTRIBUTES *sa, DWORD create_flg, DWORD attr_flg, HANDLE hTemplate);
BOOL CreateDirectoryU8(const char *path, SECURITY_ATTRIBUTES *lsa);
BOOL DeleteFileU8(const char *path);
BOOL RemoveDirectoryU8(const char *path);

HINSTANCE ShellExecuteU8(HWND hWnd, LPCSTR op, LPCSTR file, LPSTR params, LPCSTR dir, int nShow);
BOOL ShellExecuteExU8(SHELLEXECUTEINFO *info);
DWORD GetCurrentDirectoryU8(DWORD size, char *dir);
DWORD GetWindowsDirectoryU8(char *dir, DWORD size);
BOOL SetCurrentDirectoryU8(char *dir);
BOOL GetOpenFileNameU8(LPOPENFILENAME ofn);
BOOL GetSaveFileNameU8(LPOPENFILENAME ofn);

BOOL ReadLink(LPCSTR src, LPSTR dest, LPSTR arg);

int strncmpi(const char *str1, const char *str2, int num);
char *strncpyz(char *dest, const char *src, int num);

void Debug(char *fmt,...);
BOOL InstallExceptionFilter(char *title, char *info);
#endif
