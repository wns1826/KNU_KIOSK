#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_popup_post(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) { //980 1250
	static WEBVIEW *WebView;
	static bool mode_tag;
	static wstring url;
	static bool ani;
	switch (iMessage) {
	case WM_CREATE: {
		mode_tag = false;
		SetTimer(hWnd, 1, 500, NULL);
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 980, 1250, 255, 255, 255);
		//	Draw.Rect(0, 0, 980, 60, 0, 255, 255);
		Draw.Text(5, 0, 980, 60, 35, 0, 0, 0, L"Noto Sans CJK KR Light", L"게시글 보기");
		Draw.Draw(910, 0, 50, 50, L"resource\\image\\post\\x.png");
		Draw.Line(0, 59, 980, 59, 1, 0, 0, 0);
		Draw.Rect(0, 1125, 980, 100, 21, 180, 162);
		if (!mode_tag) {
			Draw.Text(0, 1127, 980, 100, 40, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"모바일에서 이어보기", 1);
		}
		else {
			Draw.Text(0, 425, 980, 100, 65, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"QR코드를 스캔해주세요!", 1);
			Draw.Draw(340, 115, 300, 300, L"resource\\image\\tag\\qr.png");
			Draw.Line(30, 600, 350, 600, 1, 0, 0, 0);
			Draw.Text(0, 540, 980, 100, 70, 128, 128, 0, L"Noto Sans CJK KR DemiLight", L"OR", 1);
			Draw.Line(630, 600, 950, 600, 1, 0, 0, 0);
			Draw.Text(0, 670, 980, 100, 65, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"우측면에 휴대폰을 태그해주세요!", 1);
			Draw.Text(0, 750, 980, 100, 40, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"(NFC 읽기/쓰기 모드가 활성화 상태여야 합니다)", 1);
			Draw.Draw(400, 865, 200, 200, L"resource\\image\\tag\\nfc.png");
			if (ani)
				Draw.Draw(660, 850, 200, 200, L"resource\\image\\tag\\a.jpg");
			else
				Draw.Draw(630, 850, 200, 200, L"resource\\image\\tag\\a.jpg");
 			Draw.Text(0, 1127, 980, 100, 40, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"게시글 확인하기", 1);
			if (ani) ani = false;
			else ani = true;
		}
		break; }
	case WM_URL: {
		sock_send_n(sock, EncodeWcharToChar((wchar_t*)wParam));

		url = (wchar_t*)wParam;

		WebView = new WEBVIEW();
		WebView->Size(980, 1100);
		WebView->AddressBar(false);
		WebView->MenuBar(false);
		WebView->ToolBar(false);
		WebView->Navigate((wchar_t*)wParam);
		WebView->SParent(hWnd);
		WebView->SPos(0, 60);

		HWND h_ie = WebView->ShWnd();
		for (int i = 0; i < 2; i++) {
			PostMessage(h_ie, WM_KEYDOWN, 0x00000028, 0x01500001);
			PostMessage(h_ie, WM_KEYUP, 0x00000028, 0xC1500001);
		}
		break; }
	case WM_LBUTTONUP: {
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		if (900 <= x && x <= 980 && 0 <= y && y <= 60)
			DestroyWindow(hWnd);
		else if (0 <= x && x <= 980 && 1125 <= y && y <= 1250) {
			mode_tag = !mode_tag;
			if (mode_tag) {
				ShowWindow(WebView->ShWnd(), SW_HIDE);
			}
			else {
				ShowWindow(WebView->ShWnd(), SW_SHOW);
			}
		}
		PostMessage(hWnd, WM_REDRAW, NULL, NULL);
		break; }
	case WM_TIMER: {
		switch (wParam) {
		case 1:
			if (mode_tag)
				InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		break; }
	case WM_REDRAW:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		delete WebView;
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK proc_popup_tag(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_CREATE: {

		break; }
	case WM_PAINT: {
		break; }
	case WM_CLOSE:
	case WM_QUIT:
	case WM_DESTROY:
	case WM_QUERYENDSESSION: {
		PostQuitMessage(0);
		break; }
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}