#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_tag(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
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