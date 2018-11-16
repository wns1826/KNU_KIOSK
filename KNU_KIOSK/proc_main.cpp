#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_main(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_CREATE: {
		h_clock = CreateWindow(L"kiosk_main_clock", L"clock", WS_CHILD | WS_VISIBLE, 0, 0, 1080, 100, hWnd, NULL, hInstance, NULL);
		h_child = CreateWindow(L"kiosk_main_notice", L"notice", WS_CHILD | WS_VISIBLE, 0, 100, 1080, 1400, hWnd, NULL, hInstance, NULL);
		h_menu = CreateWindow(L"kiosk_main_menu", L"menu", WS_CHILD | WS_VISIBLE, 0, 1500, 1080, 141, hWnd, NULL, hInstance, NULL);
		h_popup = CreateWindow(L"kiosk_main_popup", L"popup", WS_CHILD | WS_VISIBLE, 0, 1641, 1080, 279, hWnd, NULL, hInstance, NULL);
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 1920, 255, 255, 255);
		break; }
	case WM_REDRAW:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAGE:
		DestroyWindow(h_child);
		switch (wParam) {
		case 0:
			h_child = CreateWindow(L"kiosk_main_notice", L"notice", WS_CHILD | WS_VISIBLE, 0, 100, 1080, 1400, hWnd, NULL, hInstance, NULL);
			break;
		case 1:
			h_child = CreateWindow(L"kiosk_main_calendar", L"calendar", WS_CHILD | WS_VISIBLE, 0, 100, 1080, 1400, hWnd, NULL, hInstance, NULL);
			break;
		case 2:
			h_child = CreateWindow(L"kiosk_main_food", L"food", WS_CHILD | WS_VISIBLE, 0, 100, 1080, 1400, hWnd, NULL, hInstance, NULL);
			break;
		case 3:
			h_child = CreateWindow(L"kiosk_main_bus", L"bus", WS_CHILD | WS_VISIBLE, 0, 100, 1080, 1400, hWnd, NULL, hInstance, NULL);
			break;
		}
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}