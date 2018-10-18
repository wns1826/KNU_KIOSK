#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK Proc_Init(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static WEBVIEW WebView;
	static int a = 255;
	static int a_time = 0;
	switch (iMessage) {
	case WM_CREATE: {

		HWND hWnd_Web;
		WebView.Size(250, 250);
		WebView.AddressBar(false);
		WebView.MenuBar(false);
		WebView.ToolBar(false);
		WebView.Navigate(L"127.0.0.1/progress.html");
		hWnd_Web = WebView.SParent(hWnd);
		WebView.SPos(415, 1450);

		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, NULL, 0, LWA_ALPHA);

		a_time = clock();
		SetTimer(hWnd, 1, 10, NULL);

		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 1920, 255, 255, 255);
		Draw.Draw(0, 0, 1080, 1920, L"init.png");
		//Draw.Rect(110, 1680, 862, 140, 50, 50, 50, 150);
		Draw.Text(110, 1705, 862, 140, 50, 244, 118, 9, L"Noto Sans CJK KR Regular", L"서버에 연결하는 중", 1);
		break; }
	case WM_TIMER: {
		switch (wParam) {
		case 1:
			a = (int)(((clock() - a_time) / 2000.0) * 255);
			if (255 <= a) {
				a = 255;
				KillTimer(hWnd, 1);
			}
			SetLayeredWindowAttributes(hWnd, NULL, a, LWA_ALPHA);
			break;
		case 2:
			a = (int)(((clock() - a_time) / 2000.0) * 255);
			if (255 <= a) {
				a = 255;
				KillTimer(hWnd, 2);
			}
			SetLayeredWindowAttributes(hWnd, NULL, 255 - a, LWA_ALPHA);
			break;
		}
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