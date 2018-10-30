#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_CREATE: {
		h_init = CreateWindow(L"kiosk_init", L"init", WS_POPUP | WS_VISIBLE, 1920, 0, 1080, 1920, hWnd, (HMENU)NULL, hInstance, NULL);
		h_child = CreateWindow(L"kiosk_list", L"list", WS_CHILD | WS_VISIBLE, 0, 0, 1080, 1920, hWnd, (HMENU)NULL, hInstance, NULL);
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 1920, 255, 210, 0);
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