#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_main_clock(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) { //100
	static int td = 0;
	const wchar_t d_text[] = L"일월화수목금토";
	switch (iMessage) {
	case WM_CREATE: {
		SetTimer(hWnd, 1, 1000, NULL);
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 100, 0, 128, 255);

		Draw.Text(0, 0, 1080, 100, 50, 0, 0, 0, L"맑은 고딕", L"컴퓨터정보공학과", 1);
		Draw.Draw(0, 0, 279, 73, L"resource\\image\\list\\logo+txt.png");

		time_t t = std::time(0);
		tm* now = std::localtime(&t);
		wchar_t w_str[10];

		if (td < 5)
			wsprintf(w_str, L"%.2d:%.2d:%.2d", now->tm_hour, now->tm_min, now->tm_sec);
		else if (td < 7) {
			wsprintf(w_str, L"%.2d/%.2d(%c)", now->tm_mon + 1, now->tm_mday, d_text[now->tm_wday]);
			if (td == 6)
				td = 0;
		}

		Draw.Text(780, 10, 280, 100, 50, 255, 255, 255, L"맑은 고딕", w_str, 2);

		break; }
	case WM_TIMER: {
		switch (wParam) {
		case 1: //업데이트
				//printf("%d", td);
			InvalidateRect(hWnd, NULL, FALSE);
			td++;
			break;
		}
	}
	case WM_CLOSE:
	case WM_QUIT:
	case WM_DESTROY:
	case WM_QUERYENDSESSION:
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK proc_main_menu(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) { //141
	static int select = 0;
	switch (iMessage) {
	case WM_CREATE: {
		SetTimer(hWnd, 1, 1000, NULL);
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 141, 255, 210, 0);
		Draw.Rect(0 + select * 270, 0, 270, 141, 244, 118, 9);
		Draw.Text(0, 25, 270, 141, 50, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"공지사항", 1);
		Draw.Text(270, 25, 270, 141, 50, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"학사일정", 1);
		Draw.Text(540, 25, 270, 141, 50, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"식단표", 1);
		Draw.Text(810, 25, 270, 141, 50, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"버스", 1);
		break; }
	case WM_LBUTTONUP: {
		select = LOWORD(lParam) / 270;
		PostMessage(h_main, WM_PAGE, (WPARAM)select, NULL);
		PostMessage(hWnd, WM_DRAW, NULL, NULL);
		break; }
	case WM_DRAW:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK proc_main_popup(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) { //279
	switch (iMessage) {
	case WM_CREATE: {
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Draw(0, 0, 1080, 279, L"resource\\image\\list\\1.jpg");
		break; }
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

