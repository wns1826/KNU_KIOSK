#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_main_calendar(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_CREATE: {
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 1400, 255, 255, 255);

		Draw.Text(20, 5, 1080, 100, 70, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"학사일정");
		Draw.Line(30, 110, 1050, 110, 1, 0, 0, 0);
		break; }
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}