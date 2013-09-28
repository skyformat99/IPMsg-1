static char *twin_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2005   twin.cpp	Ver0.95";
/* ========================================================================
	Project  Name			: Win32 Lightweight  Class Library Test
	Module Name				: Window Class
	Create					: 1996-06-01(Sat)
	Update					: 2005-11-28(Mon)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include "tlib.h"

TWin::TWin(TWin *_parent)
{
	hWnd		= 0;
	hAccel		= NULL;
	rect.left	= CW_USEDEFAULT;
	rect.right	= CW_USEDEFAULT;
	rect.top	= CW_USEDEFAULT;
	rect.bottom	= CW_USEDEFAULT;
	parent		= _parent;
	sleepBusy	= FALSE;
}

TWin::~TWin()
{
	Destroy();
}

BOOL TWin::Create(LPCTSTR className, LPCTSTR title, DWORD style, DWORD exStyle, HMENU hMenu)
{
	if (className == NULL)
		className = TApp::GetApp()->GetDefaultClass();

	TApp::GetApp()->AddWin(this);
	Wstr	classNameW(className), titleW(title);

	if ((hWnd = ::CreateWindowExW(exStyle, classNameW, titleW, style, rect.left, rect.top, rect.right, rect.bottom, parent ? parent->hWnd : NULL, hMenu, TApp::GetInstance(), NULL)) == NULL)
		return	TApp::GetApp()->DelWin(this), FALSE;
	else
		return	TRUE;
}

void TWin::Destroy(void)
{
	if (::IsWindow(hWnd))
	{
		::DestroyWindow(hWnd);
		hWnd = 0;
	}
}

void TWin::Show(int mode)
{
	::ShowWindow(hWnd, mode);
	::UpdateWindow(hWnd);
}

LRESULT TWin::WinProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL	done = FALSE;
	LRESULT	result = 0;

	switch(uMsg)
	{
	case WM_CREATE:
		done = EvCreate(lParam);
		break;

	case WM_CLOSE:
		done = EvClose();
		break;

	case WM_COMMAND:
		done = EvCommand(HIWORD(wParam), LOWORD(wParam), lParam);
		break;

	case WM_SYSCOMMAND:
		done = EvSysCommand(wParam, MAKEPOINTS(lParam));
		break;

	case WM_TIMER:
		done = EvTimer(wParam, (TIMERPROC)lParam);
		break;

	case WM_NCDESTROY:
		GetWindowRect(&rect);
		if (EvNcDestroy() == FALSE)	// hWnd‚ð0‚É‚·‚é‘O‚ÉŒÄ‚Ño‚·
			DefWindowProc(uMsg, wParam, lParam);
		done = TRUE;
		TApp::GetApp()->DelWin(this);
		hWnd = 0;
		break;

	case WM_QUERYENDSESSION:
		result = EvQueryEndSession((BOOL)wParam, (BOOL)lParam);
		done = TRUE;
		break;

	case WM_ENDSESSION:
		done = EvEndSession((BOOL)wParam, (BOOL)lParam);
		break;

	case WM_QUERYOPEN:
		result = EvQueryOpen();
		done = TRUE;
		break;

	case WM_PAINT:
		done = EvPaint();
		break;

	case WM_NCPAINT:
		done = EvNcPaint((HRGN)wParam);
		break;

	case WM_SIZE:
		done = EvSize((UINT)wParam, LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_SHOWWINDOW:
		done = EvShowWindow(wParam, lParam);
		break;

	case WM_GETMINMAXINFO:
		done = EvGetMinMaxInfo((MINMAXINFO *)lParam);
		break;

	case WM_SETCURSOR:
		result = done = EvSetCursor((HWND)wParam, LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_MOUSEMOVE:
		done = EvMouseMove((UINT)wParam, MAKEPOINTS(lParam));
		break;

	case WM_NCHITTEST:
		done = EvNcHitTest(MAKEPOINTS(lParam), &result);
		break;

	case WM_MEASUREITEM:
		result = done = EvMeasureItem((UINT)wParam, (LPMEASUREITEMSTRUCT)lParam);
		break;

	case WM_DRAWITEM:
		result = done = EvDrawItem((UINT)wParam, (LPDRAWITEMSTRUCT)lParam);
		break;

	case WM_NOTIFY:
		result = done = EvNotify((UINT)wParam, (LPNMHDR)lParam);
		break;

	case WM_CONTEXTMENU:
		result = done = EvContextMenu((HWND)wParam, MAKEPOINTS(lParam));
		break;

	case WM_MENUSELECT:
		done = EvMenuSelect(LOWORD(wParam), HIWORD(wParam), (HMENU)lParam);
		break;

	case WM_DROPFILES:
		done = EvDropFiles((HDROP)wParam);
		break;

	case WM_HOTKEY:
		result = done = EvHotKey((int)wParam);
		break;

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
		done = EventButton(uMsg, wParam, MAKEPOINTS(lParam));
		break;

	case WM_KEYUP:
	case WM_KEYDOWN:
		done = EventKey(uMsg, wParam, lParam);
		break;

	case WM_HSCROLL:
	case WM_VSCROLL:
		done = EventScroll(uMsg, LOWORD(wParam), HIWORD(wParam), (HWND)lParam);
		break;

	case WM_INITMENU:
	case WM_INITMENUPOPUP:
		done = EventInitMenu(uMsg, (HMENU)wParam, LOWORD(lParam), (BOOL)HIWORD(lParam));
		break;

	case WM_CTLCOLORBTN:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
		done = EventCtlColor(uMsg, (HDC)wParam, (HWND)lParam, (HBRUSH *)&result);
		break;

	case WM_KILLFOCUS:
	case WM_SETFOCUS:
		done = EventFocus(uMsg, (HWND)wParam);
		break;

	default:
		if (uMsg >= WM_USER && uMsg < 0x7FFF || uMsg >= 0xC000 && uMsg <= 0xFFFF)
			result = done = EventUser(uMsg, wParam, lParam);
		else
			result = done = EventSystem(uMsg, wParam, lParam);
		break;
	}

	return	done ? result : DefWindowProc(uMsg, wParam, lParam);
}

LRESULT TWin::DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL TWin::PreProcMsg(MSG *msg)
{
	if (hAccel)
		return	::TranslateAcceleratorW(hWnd, hAccel, msg);

	return	FALSE;
}

BOOL TWin::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hwndCtl)
{
	return	FALSE;
}

BOOL TWin::EvSysCommand(WPARAM uCmdType, POINTS pos)
{
	return	FALSE;
}

BOOL TWin::EvCreate(LPARAM lParam)
{
	return	FALSE;
}

BOOL TWin::EvClose(void)
{
	return	FALSE;
}


BOOL TWin::EvMeasureItem(UINT ctlID, MEASUREITEMSTRUCT *lpMis)
{
	return	FALSE;
}

BOOL TWin::EvDrawItem(UINT ctlID, DRAWITEMSTRUCT *lpDis)
{
	return	FALSE;
}

BOOL TWin::EvNcDestroy(void)
{
	return	FALSE;
}

BOOL TWin::EvTimer(WPARAM timerID, TIMERPROC proc)
{
	return	FALSE;
}

BOOL TWin::Sleep(UINT mSec)
{
	if (mSec == 0 || sleepBusy)
		return	TRUE;

	if (::SetTimer(hWnd, TLIB_SLEEPTIMER, mSec, 0) == FALSE)
		return	FALSE;
	sleepBusy = TRUE;

	MSG		msg;
	while (::GetMessage(&msg, 0, 0, 0))
	{
		if (msg.hwnd == hWnd && msg.wParam == TLIB_SLEEPTIMER)
		{
			::KillTimer(hWnd, TLIB_SLEEPTIMER);
			break;
		}
		if (TApp::GetApp()->PreProcMsg(&msg))
			continue;

		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	sleepBusy = FALSE;

	return	TRUE;
}

BOOL TWin::EvQueryEndSession(BOOL nSession, BOOL nLogOut)
{
	return	TRUE;
}

BOOL TWin::EvEndSession(BOOL nSession, BOOL nLogOut)
{
	return	TRUE;
}

BOOL TWin::EvQueryOpen(void)
{
	return	TRUE;
}

BOOL TWin::EvPaint(void)
{
	return	FALSE;
}

BOOL TWin::EvNcPaint(HRGN hRgn)
{
	return	FALSE;
}

BOOL TWin::EvSize(UINT fwSizeType, WORD nWidth, WORD nHeight)
{
	return	FALSE;
}

BOOL TWin::EvShowWindow(BOOL fShow, int fnStatus)
{
	return	FALSE;
}

BOOL TWin::EvGetMinMaxInfo(MINMAXINFO *info)
{
	return	FALSE;
}

BOOL TWin::EvSetCursor(HWND cursorWnd, WORD nHitTest, WORD wMouseMsg)
{
	return	FALSE;
}

BOOL TWin::EvMouseMove(UINT fwKeys, POINTS pos)
{
	return	FALSE;
}

BOOL TWin::EvNcHitTest(POINTS pos, LRESULT *result)
{
	return	FALSE;
}

BOOL TWin::EvNotify(UINT ctlID, NMHDR *pNmHdr)
{
	return	FALSE;
}

BOOL TWin::EvContextMenu(HWND childWnd, POINTS pos)
{
	return	FALSE;
}

BOOL TWin::EvHotKey(int hotKey)
{
	return	FALSE;
}

BOOL TWin::EventScroll(UINT uMsg, int Code, int nPos, HWND hwndScrollBar)
{
	return	FALSE;
}

BOOL TWin::EventButton(UINT uMsg, int nHitTest, POINTS pos)
{
	return	FALSE;
}

BOOL TWin::EventKey(UINT uMsg, int nVirtKey, LONG lKeyData)
{
	return	FALSE;
}

BOOL TWin::EventInitMenu(UINT uMsg, HMENU hMenu, UINT uPos, BOOL fSystemMenu)
{
	return	FALSE;
}

BOOL TWin::EvMenuSelect(UINT uItem, UINT fuFlag, HMENU hMenu)
{
	return	FALSE;
}

BOOL TWin::EvDropFiles(HDROP hDrop)
{
	return	FALSE;
}

BOOL TWin::EventCtlColor(UINT uMsg, HDC hDcCtl, HWND hWndCtl, HBRUSH *result)
{
	return	FALSE;
}

BOOL TWin::EventFocus(UINT uMsg, HWND hFocusWnd)
{
	return	FALSE;
}

BOOL TWin::EventUser(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	FALSE;
}

BOOL TWin::EventSystem(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	FALSE;
}

UINT TWin::GetDlgItemText(int ctlId, char *buf, int len)
{
	Wstr	wbuf(len);
	UINT	ret = ::GetDlgItemTextW(hWnd, ctlId, wbuf.Buf(), len);
	if (ret) {
		ret = WtoU8(wbuf, buf, len);
	}
	return	ret;
}


UINT TWin::GetDlgItemTextW(int ctlId, WCHAR *buf, int len)
{
	return	::GetDlgItemTextW(hWnd, ctlId, buf, len);
}

BOOL TWin::SetDlgItemText(int ctlId, const char *buf)
{
	Wstr	wbuf(buf);
	return	::SetDlgItemTextW(hWnd, ctlId, wbuf);
}

BOOL TWin::SetDlgItemTextW(int ctlId, const WCHAR *buf)
{
	return	::SetDlgItemTextW(hWnd, ctlId, buf);
}

int TWin::GetDlgItemInt(int ctlId, BOOL *err, BOOL sign)
{
	return	(int)::GetDlgItemInt(hWnd, ctlId, err, sign);
}

BOOL TWin::SetDlgItemInt(int ctlId, int val, BOOL sign)
{
	return	::SetDlgItemInt(hWnd, ctlId, val, sign);
}

HWND TWin::GetDlgItem(int ctlId)
{
	return	::GetDlgItem(hWnd, ctlId);
}

BOOL TWin::CheckDlgButton(int ctlId, UINT check)
{
	return	::CheckDlgButton(hWnd, ctlId, check);
}

UINT TWin::IsDlgButtonChecked(int ctlId)
{
	return	::IsDlgButtonChecked(hWnd, ctlId);
}

int TWin::MessageBox(LPCTSTR msg, LPCTSTR title, UINT style)
{
	Wstr	msg_w(msg), title_w(title);
	return	::MessageBoxW(hWnd, msg_w, title_w, style);
}


int TWin::MessageBoxW(WCHAR *msg, WCHAR *title, UINT style)
{
	return	::MessageBoxW(hWnd, msg, title, style);
}

BOOL TWin::BringWindowToTop(void)
{
	return	::BringWindowToTop(hWnd);
}

BOOL TWin::PostMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	::PostMessage(hWnd, uMsg, wParam, lParam);
}

BOOL TWin::PostMessageW(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	::PostMessageW(hWnd, uMsg, wParam, lParam);
}

LRESULT TWin::SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	::SendMessage(hWnd, uMsg, wParam, lParam);
}

LRESULT TWin::SendMessageW(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	::SendMessageW(hWnd, uMsg, wParam, lParam);
}

LRESULT TWin::SendDlgItemMessage(int idCtl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	::SendDlgItemMessage(hWnd, idCtl, uMsg, wParam, lParam);
}

LRESULT TWin::SendDlgItemMessageW(int idCtl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	::SendDlgItemMessageW(hWnd, idCtl, uMsg, wParam, lParam);
}

BOOL TWin::GetWindowRect(RECT *_rect)
{
	return	::GetWindowRect(hWnd, _rect ? _rect : &rect);
}

BOOL TWin::SetWindowPos(HWND hInsAfter, int x, int y, int cx, int cy, UINT fuFlags)
{
	return	::SetWindowPos(hWnd, hInsAfter, x, y, cx, cy, fuFlags);
}

BOOL TWin::SetForegroundWindow(void)
{
	return	::SetForegroundWindow(hWnd);
}

BOOL TWin::ShowWindow(int mode)
{
	return	::ShowWindow(hWnd, mode);
}

BOOL TWin::SetForceForegroundWindow(void)
{
#ifndef SPI_GETFOREGROUNDLOCKTIMEOUT
#define SPI_GETFOREGROUNDLOCKTIMEOUT 0x2000
#define SPI_SETFOREGROUNDLOCKTIMEOUT 0x2001
#endif
	DWORD	foreId, targId, svTmOut;

	foreId = ::GetWindowThreadProcessId(::GetForegroundWindow(), NULL);
	targId = ::GetWindowThreadProcessId(hWnd, NULL);
	if (foreId != targId)
		::AttachThreadInput(targId, foreId, TRUE);
	::SystemParametersInfo(SPI_GETFOREGROUNDLOCKTIMEOUT, 0, (void *)&svTmOut, 0);
	::SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, 0, 0);
	BOOL	ret = ::SetForegroundWindow(hWnd);
	::SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, (void *)svTmOut, 0);
	if (foreId != targId)
		::AttachThreadInput(targId, foreId, FALSE);

	return	ret;
}

HWND TWin::SetActiveWindow(void)
{
	return	::SetActiveWindow(hWnd);
}

int TWin::GetWindowText(LPTSTR text, int size)
{
	Wstr	text_w(size);
	::GetWindowTextW(hWnd, text_w.Buf(), size);
	return	WtoU8(text_w, text, size);
}

int TWin::GetWindowTextW(WCHAR *text, int size)
{
	return	::GetWindowTextW(hWnd, text, size);
}

int TWin::GetWindowTextLength(void)	// ‚¤[‚Þ...
{
	int	len = GetWindowTextLengthW() + 1;
	Wstr	wbuf(len);
	GetWindowTextW(wbuf.Buf(), len);

	U8str	u8buf(wbuf);
	return	strlen(u8buf);
}


int TWin::GetWindowTextLengthW(void)
{
	return	::GetWindowTextLengthW(hWnd);
}

BOOL TWin::SetWindowText(LPCTSTR text)
{
	Wstr	text_w(text);
	return	::SetWindowTextW(hWnd, text_w);
}


BOOL TWin::SetWindowTextW(const WCHAR *text)
{
	return	::SetWindowTextW(hWnd, text);
}

LONG TWin::SetWindowLong(int index, LONG val)
{
	return	::SetWindowLong(hWnd, index, val);
}

WORD TWin::SetWindowWord(int index, WORD val)
{
	return	::SetWindowWord(hWnd, index, val);
}

LONG TWin::GetWindowLong(int index)
{
	return	::GetWindowLong(hWnd, index);
}

WORD TWin::GetWindowWord(int index)
{
	return	::GetWindowWord(hWnd, index);
}

BOOL TWin::MoveWindow(int x, int y, int cx, int cy, int bRepaint)
{
	return	::MoveWindow(hWnd, x, y, cx, cy, bRepaint);
}

BOOL TWin::Idle(void)
{
	MSG		msg;

	if (::PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (TApp::GetApp()->PreProcMsg(&msg))
			return	TRUE;

		::TranslateMessage(&msg);
		::DispatchMessageW(&msg);
		return	TRUE;
	}

	return	FALSE;
}


TSubClass::TSubClass(TWin *_parent) : TWin(_parent)
{
}

BOOL TSubClass::CreateByWnd(HWND _hWnd)
{
	TApp::GetApp()->AddWinByWnd(this, _hWnd);
	return	(oldProc = (WNDPROC)::SetWindowLongW(_hWnd, GWL_WNDPROC, (LONG)TApp::WinProc)) ? TRUE : FALSE;
}

LRESULT TSubClass::DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	::CallWindowProcW((WNDPROC)oldProc, hWnd, uMsg, wParam, lParam);
}

TSubClassCtl::TSubClassCtl(TWin *_parent) : TSubClass(_parent)
{
}

BOOL TSubClassCtl::PreProcMsg(MSG *msg)
{
	if (parent)
		return	parent->PreProcMsg(msg);

	return	FALSE;
}

