#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_main_clock(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) { //100
	static int td = 0;
	switch (iMessage) {
	case WM_CREATE: {
		SetTimer(hWnd, 1, 1000, NULL);
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 100, 0, 128, 255);

		time_t t = std::time(0);
		tm* now = std::localtime(&t);
		wchar_t w_str[10];

		if (td < 5)
			wsprintf(w_str, L"%.2d:%.2d:%.2d", now->tm_hour, now->tm_min, now->tm_sec);
		else if (td < 7) {
			wsprintf(w_str, L"%.2d/%.2d(%c)", now->tm_mon + 1, now->tm_mday, day_text[now->tm_wday]);
			if (td == 6)
				td = 0;
		}

		Draw.Draw(15, 23, 214, 56, L"resource\\image\\list\\logo+txt.png");
		Draw.Text(0, 13, 1080, 100, 50, 255, 255, 255, L"맑은 고딕", L"컴퓨터정보공학과", 1);
		Draw.Text(780, 13, 280, 100, 50, 255, 255, 255, L"맑은 고딕", w_str, 2);

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
		PostMessage(hWnd, WM_REDRAW, NULL, NULL);
		break; }
	case WM_REDRAW:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK proc_main_popup(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) { //279
	static int ani_time;
	static int popup_num = 0;
	static int popup_pos = 0;
	switch (iMessage) {
	case WM_CREATE: {
		ani_time = clock();
		SetTimer(hWnd, 1, 500, NULL);
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		if (popup_pos == 0 && popup_num < knu_popup.size())
			Draw.Draw(0, 0, 1080, 279, knu_popup[popup_num].c_str());
		else if (popup_num < knu_popup.size()) {
			Draw.Draw(0, 0, 1080, 279, knu_popup[popup_num].c_str());
			if (popup_num == 0)
				Draw.Draw(popup_pos, 0, 1080, 279, knu_popup[knu_popup.size() - 1].c_str());
			else
				Draw.Draw(popup_pos, 0, 1080, 279, knu_popup[popup_num - 1].c_str());
		}
		break; }
	case WM_TIMER: {
		switch (wParam) {
		case 1: //대기
			if (5000 <= clock() - ani_time) {
				KillTimer(hWnd, 1);
				popup_pos = 1;
				popup_num++;
				if (knu_popup.size() <= popup_num)
					popup_num = 0;
				ani_time = clock();
				SetTimer(hWnd, 2, 30, NULL);
			}
			break;
		case 2: //이동
			popup_pos = 1080 * (clock() - ani_time) / 2000.0; 
			if (1080 <= popup_pos) {
				popup_pos = 0;
				KillTimer(hWnd, 2);
				ani_time = clock();
				SetTimer(hWnd, 1, 500, NULL);
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
	}
	case WM_REDRAW:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

