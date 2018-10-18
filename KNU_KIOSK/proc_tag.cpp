#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK Proc_Tag(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_CREATE: {
		hWnd = CreateWindow(L"kiosk_init", L"init", WS_POPUP | WS_VISIBLE, 1920, 0, 1080, 1920, hWnd, (HMENU)NULL, hInstance, NULL);

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