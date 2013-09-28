static char *tdlg_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2005   tdlg.cpp	Ver0.95";
/* ========================================================================
	Project  Name			: Win32 Lightweight  Class Library Test
	Module Name				: Dialog Class
	Create					: 1996-06-01(Sat)
	Update					: 2005-05-03(Tue)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include "tlib.h"

TDlg::TDlg(UINT _resId, TWin *_parent) : TWin(_parent)
{
	resId	= _resId;
	modalFlg = FALSE;
}

TDlg::~TDlg()
{
	if (hWnd)
		EndDialog(FALSE);
}

BOOL TDlg::Create(HINSTANCE hInstance)
{
	TApp::GetApp()->AddWin(this);

	hWnd = ::CreateDialogW(hInstance ? hInstance : TApp::GetInstance(), (const WCHAR *)resId, parent ? parent->hWnd : NULL, (DLGPROC)TApp::WinProc);

	if (hWnd)
		return	TRUE;
	else
		return	TApp::GetApp()->DelWin(this), FALSE;
}

int TDlg::Exec(void)
{
	TApp::GetApp()->AddWin(this);
	modalFlg = TRUE;
	int result = ::DialogBoxW(TApp::GetInstance(), (const WCHAR *)resId, parent ? parent->hWnd : NULL, (DLGPROC)TApp::WinProc);
	modalFlg = FALSE;
	return	result;
}

void TDlg::Destroy(void)
{
	EndDialog(FALSE);
}

LRESULT TDlg::WinProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT	result = 0;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		if (rect.left != CW_USEDEFAULT && !(::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
			MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
		return	EvCreate(lParam);

	case WM_CLOSE:
		EvClose();
		return	0;

	case WM_COMMAND:
		EvCommand(HIWORD(wParam), LOWORD(wParam), lParam);
		return	0;

	case WM_SYSCOMMAND:
		EvSysCommand(wParam, MAKEPOINTS(lParam));
		return	0;

	case WM_TIMER:
		EvTimer(wParam, (TIMERPROC)lParam);
		return	0;

	case WM_NCDESTROY:
		GetWindowRect(&rect);
		EvNcDestroy();
		TApp::GetApp()->DelWin(this);
		hWnd = 0;
		return	0;

	case WM_QUERYENDSESSION:	// Dialog の場合、なぜか解釈が逆...
		return	!EvQueryEndSession((BOOL)wParam, (BOOL)lParam);

	case WM_ENDSESSION:
		EvEndSession((BOOL)wParam, (BOOL)lParam);
		return	0;

	case WM_QUERYOPEN:
		return	EvQueryOpen();

	case WM_PAINT:
		EvPaint();
		return	0;

	case WM_NCPAINT:
		EvNcPaint((HRGN)wParam);
		return	0;

	case WM_SIZE:
		EvSize((UINT)wParam, LOWORD(lParam), HIWORD(lParam));
		return	0;

	case WM_SHOWWINDOW:
		EvShowWindow(wParam, lParam);
		return	0;

	case WM_GETMINMAXINFO:
		EvGetMinMaxInfo((MINMAXINFO *)lParam);
		return	0;

	case WM_SETCURSOR:
		return	EvSetCursor((HWND)wParam, LOWORD(lParam), HIWORD(lParam));

	case WM_MOUSEMOVE:
		return	EvMouseMove((UINT)wParam, MAKEPOINTS(lParam));

	case WM_NCHITTEST:
		return	EvNcHitTest(MAKEPOINTS(lParam), &result), result;

	case WM_MEASUREITEM:
		return	EvMeasureItem((UINT)wParam, (LPMEASUREITEMSTRUCT)lParam);

	case WM_DRAWITEM:
		return	EvDrawItem((UINT)wParam, (LPDRAWITEMSTRUCT)lParam);

	case WM_NOTIFY:
		return	EvNotify((UINT)wParam, (LPNMHDR)lParam);

	case WM_CONTEXTMENU:
		return	EvContextMenu((HWND)wParam, MAKEPOINTS(lParam));

	case WM_HOTKEY:
		return	EvHotKey((int)wParam);

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_NCLBUTTONUP:
	case WM_NCRBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_NCLBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_NCLBUTTONDBLCLK:
	case WM_NCRBUTTONDBLCLK:
		EventButton(uMsg, wParam, MAKEPOINTS(lParam));
		return	0;

	case WM_KEYUP:
	case WM_KEYDOWN:
		EventKey(uMsg, wParam, lParam);
		return	0;

	case WM_HSCROLL:
	case WM_VSCROLL:
		EventScroll(uMsg, LOWORD(wParam), HIWORD(wParam), (HWND)lParam);
		return	0;

	case WM_INITMENU:
	case WM_INITMENUPOPUP:
		EventInitMenu(uMsg, (HMENU)wParam, LOWORD(lParam), (BOOL)HIWORD(lParam));
		return	0;

	case WM_MENUSELECT:
		EvMenuSelect(LOWORD(wParam), (BOOL)HIWORD(wParam), (HMENU)lParam);
		return	0;

	case WM_DROPFILES:
		EvDropFiles((HDROP)wParam);
		return	0;

	case WM_CTLCOLORBTN:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
		return	EventCtlColor(uMsg, (HDC)wParam, (HWND)lParam, (HBRUSH *)&result), result;

	case WM_KILLFOCUS:
	case WM_SETFOCUS:
		EventFocus(uMsg, (HWND)wParam);
		return	0;

	default:
		if (uMsg >= WM_USER && uMsg <= 0x7FFF || uMsg >= 0xC000 && uMsg <= 0xFFFF)
			return	EventUser(uMsg, wParam, lParam);
		else
			return	EventSystem(uMsg, wParam, lParam);
	}

	return	FALSE;
}

BOOL TDlg::PreProcMsg(MSG *msg)
{
	if (hAccel && ::TranslateAcceleratorW(hWnd, hAccel, msg))
		return	TRUE;

	if (!modalFlg)
		return	::IsDialogMessageW(hWnd, msg);

	return	FALSE;
}

BOOL TDlg::EvSysCommand(WPARAM uCmdType, POINTS pos)
{
	return	FALSE;
}

BOOL TDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hwndCtl)
{
	switch (wID)
	{
	case IDOK: case IDCANCEL: case IDYES: case IDNO:
	case IDABORT: case IDIGNORE: case IDRETRY:
		EndDialog(wID);
		return	TRUE;
	}

	return	FALSE;
}

BOOL TDlg::EvQueryOpen(void)
{
	return	FALSE;
}

BOOL TDlg::EvCreate(LPARAM lParam)
{
	return	TRUE;
}

void TDlg::EndDialog(int result)
{
	if (::IsWindow(hWnd))
	{
		if (modalFlg)
			::EndDialog(hWnd, result);
		else
			::DestroyWindow(hWnd);
	}
}

