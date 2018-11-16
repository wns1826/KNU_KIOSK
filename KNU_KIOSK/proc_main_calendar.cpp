#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_main_calendar(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static WEBVIEW* WebView;
	switch (iMessage) {
	case WM_CREATE: {
		WebView = new WEBVIEW();
		WebView->Size(1040, 1300);
		WebView->AddressBar(false);
		WebView->MenuBar(false);
		WebView->ToolBar(false);
		WebView->Navigate(L"http://www.kunsan.ac.kr/index.kunsan?menuCd=DOM_000000103001001000&sso=ok");
		WebView->SParent(hWnd);
		WebView->SPos(30, 112);

		HWND h_ie = WebView->ShWnd();
		for (int i = 0; i < 2; i++) {
			PostMessage(h_ie, WM_KEYDOWN, 0x00000028, 0x01500001);
			PostMessage(h_ie, WM_KEYUP, 0x00000028, 0xC1500001);
		}

		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 1400, 255, 255, 255);

		Draw.Text(20, 5, 1080, 100, 70, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"학사일정");
		Draw.Line(30, 110, 1050, 110, 1, 0, 0, 0);
		break; }
	case WM_DESTROY:
		delete WebView;
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}