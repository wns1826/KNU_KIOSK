#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_popup_post(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) { //980 1250
	WEBVIEW *WebView;
	switch (iMessage) {
	case WM_CREATE: {
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 980, 1250, 255, 255, 255);
	//	Draw.Rect(0, 0, 980, 60, 0, 255, 255);
		Draw.Text(5, 0, 980, 60, 35, 0, 0, 0, L"Noto Sans CJK KR Light", L"게시글 보기");
		Draw.Text(10, 1130, 980, 100, 40, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"모바일에서 확인하기", 1);
		break; }
	case WM_USER + 1: {
		sock_send_n(sock, EncodeWcharToChar((wchar_t*)wParam));

		WebView = new WEBVIEW();
		WebView->Size(980, 1100);
		WebView->AddressBar(false);
		WebView->MenuBar(false);
		WebView->ToolBar(false);
		WebView->Navigate((wchar_t*)wParam);
		WebView->SParent(hWnd);
		WebView->SPos(0, 60);

		SetProp(hWnd, L"IE", (HANDLE)WebView);

		HWND h_ie = WebView->ShWnd();
		for (int i = 0; i < 5; i++) {
			PostMessage(h_ie, WM_KEYDOWN, 0x00000028, 0x01500001);
			PostMessage(h_ie, WM_KEYUP, 0x00000028, 0xC1500001);
		}
		break; }
	case WM_DESTROY:
		WebView = (WEBVIEW*)GetProp(hWnd, L"IE");
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