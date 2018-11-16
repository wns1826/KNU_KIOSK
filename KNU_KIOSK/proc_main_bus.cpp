#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_main_bus(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static WEBVIEW* WebView;
	switch (iMessage) {
	case WM_CREATE: {
		WebView = new WEBVIEW();
		WebView->Size(1040, 1300);
		WebView->AddressBar(false);
		WebView->MenuBar(false);
		WebView->ToolBar(false);
		WebView->Navigate(L"http://www.kunsan.ac.kr/synap/skin/doc.html?fn=153621609594922.hwp&rs=/upload_data/Synap/CNT_ATCHDOWN/&cpath=");
		WebView->SParent(hWnd);
		WebView->SPos(30, 112);
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 1400, 255, 255, 255);

		Draw.Text(20, 5, 1080, 100, 70, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"통학버스");
		Draw.Line(30, 110, 1050, 110, 1, 0, 0, 0);
		break; }
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}