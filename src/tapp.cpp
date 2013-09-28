static char *tapp_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2005   tapp.cpp	Ver0.97";
/* ========================================================================
	Project  Name			: Win32 Lightweight  Class Library Test
	Module Name				: Application Frame Class
	Create					: 1996-06-01(Sat)
	Update					: 2005-05-29(Sun)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include "tlib.h"

TApp *TApp::tapp = NULL;
#define MAX_TAPPWIN_HASH	1009

TApp::TApp(HINSTANCE _hI, LPSTR _cmdLine, int _nCmdShow)
{
	hI				= _hI;
	cmdLine			= _cmdLine;
	nCmdShow		= _nCmdShow;
	mainWnd			= NULL;
	defaultClass	= _T("tapp");
	tapp			= this;
	hash			= new THash(MAX_TAPPWIN_HASH);

#if ENGLISH_TEST
	TSetDefaultLCID(0x409); // for English Dialog Test
#else
	TSetDefaultLCID();
#endif
	::CoInitialize(NULL);
	::InitCommonControls();
	InitGlobalItems();
	InitInstanceForLoadStr(_hI);
}

TApp::~TApp()
{
	delete mainWnd;
	::CoUninitialize();
}

int TApp::Run(void)
{
	MSG		msg;

	InitApp();
	InitWindow();

	while (::GetMessageW(&msg, NULL, 0, 0))
	{
		if (PreProcMsg(&msg))
			continue;

		::TranslateMessage(&msg);
		::DispatchMessageW(&msg);
	}

	return	msg.wParam;
}

BOOL TApp::PreProcMsg(MSG *msg)	// for TranslateAccel & IsDialogMessage
{
	for (HWND hWnd=msg->hwnd; hWnd != NULL; hWnd=::GetParent(hWnd))
	{
		TWin	*win = SearchWnd(hWnd);

		if (win != NULL)
			return	win->PreProcMsg(msg);
	}

	return	FALSE;
}

LRESULT CALLBACK TApp::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TApp	*app = TApp::GetApp();
	TWin	*win = app->SearchWnd(hWnd);

	if (win)
		return	win->WinProc(uMsg, wParam, lParam);

	if ((win = app->preWnd) != NULL)
	{
		app->preWnd = NULL;
		app->AddWinByWnd(win, hWnd);
		return	win->WinProc(uMsg, wParam, lParam);
	}

	return	::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

BOOL TApp::InitApp(void)
{
	if (FindWindowU8(defaultClass, NULL) == NULL)
	{
		if (TRegisterClass(defaultClass) == FALSE)
			return FALSE;
	}
	return	TRUE;
}

BOOL THashObj::LinkHash(THashObj *top, HashID _id)
{
	if (priorHash)
		return FALSE;
	id = _id;
	this->nextHash = top->nextHash;
	this->priorHash = top;
	top->nextHash->priorHash = this;
	top->nextHash = this;
	return TRUE;
}

BOOL THashObj::UnlinkHash()
{
	if (!priorHash)
		return FALSE;
	priorHash->nextHash = nextHash;
	nextHash->priorHash = priorHash;
	priorHash = nextHash = NULL;
	return TRUE;
}


THash::THash(int _hashNum)
{
	hashTbl = new THashObj [hashNum = _hashNum];

	for (int i=0; i < hashNum; i++) {
		THashObj	*obj = hashTbl + i;
		obj->priorHash = obj->nextHash = obj;
	}
	registerNum = 0;
}

THash::~THash()
{
	delete [] hashTbl;
}

void THash::Register(THashObj *obj, HashID id)
{
	if (obj->LinkHash(hashTbl + (MakeHash(id) % hashNum), id))
		registerNum++;
}

void THash::UnRegister(THashObj *obj)
{
	if (obj->UnlinkHash())
		registerNum--;
}

THashObj *THash::GetHashObj(HashID id)
{
	THashObj *top = hashTbl + (MakeHash(id) % hashNum);

	for (THashObj *obj=top->nextHash; obj != top; obj=obj->nextHash) {
		if (obj->id == id)
			return obj;
	}
	return	NULL;
}

