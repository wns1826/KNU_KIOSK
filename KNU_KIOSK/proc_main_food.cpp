#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_main_food(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) { //1400
	static int day = 3;
	switch (iMessage) {
	case WM_CREATE: {
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 1400, 255, 255, 255);

		time_t t = std::time(0);
		tm* now = std::localtime(&t);
		wchar_t w_str[100];
		day = now->tm_wday - 1;
		if (day == -1)
			day = 6;
		wsprintf(w_str, L"%.2d월 %.2d일 (%c)", now->tm_mon + 1, now->tm_mday, day_text[now->tm_wday]);

		Draw.Text(0, 5, 1080, 100, 50, 0, 0, 0, L"Noto Sans CJK KR DemiLight", w_str, 1);
		Draw.Line(20, 100, 1060, 100, 1, 0, 0, 0);
		Draw.Line(120, 100, 120, 1350, 1, 0, 0, 0);
		Draw.Line(20, 100, 20, 1350, 1, 0, 0, 0);
		Draw.Line(1060, 100, 1060, 1350, 1, 0, 0, 0);
		Draw.Line(20, 100, 120, 150, 1, 0, 0, 0);
		Draw.Line(20, 150, 1060, 150, 1, 0, 0, 0);
		Draw.Line(20, 550, 1060, 550, 1, 0, 0, 0);
		Draw.Line(20, 950, 1060, 950, 1, 0, 0, 0);
		Draw.Line(20, 1350, 1060, 1350, 1, 0, 0, 0);
		Draw.Line(430, 100, 430, 1350, 1, 0, 0, 0);
		Draw.Line(740, 100, 740, 1350, 1, 0, 0, 0);
		//Draw.Line(120, 100, 120, 1350, 1, 0, 0, 0);
		Draw.Text(32, 320, 100, 400, 35, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"아침");
		Draw.Text(32, 720, 100, 400, 35, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"점심");
		Draw.Text(32, 1120, 100, 400, 35, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"저녁");
		Draw.Text(210, 100, 200, 50, 35, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"학생일품");
		Draw.Text(510, 100, 200, 50, 35, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"교직원식");
		Draw.Text(830, 100, 200, 50, 35, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"기숙사식");
		
		for (int i = 0; i < 2; i++) {
			wstring menu;
			for (int j = 0; j < food_knu_student[day][i].size(); j++) {
				menu += food_knu_student[day][i][j];
				menu += L"\n";
			}
			Draw.Text(130, 140 + (400 - Draw.Text_Rect_y(30, L"Noto Sans CJK KR DemiLight", menu.c_str())) / 2 + (i + 1) * 400, 300, 400, 30, 0, 0, 0, L"Noto Sans CJK KR DemiLight", menu.c_str(), 1);
		}

		for (int i = 0; i < 2; i++) {
			wstring menu;
			for (int j = 0; j < food_knu_teacher[day][i].size(); j++) {
				menu += food_knu_teacher[day][i][j];
				menu += L"\n";
			}
			Draw.Text(440, 140 + (400 - Draw.Text_Rect_y(30, L"Noto Sans CJK KR DemiLight", menu.c_str())) / 2 + (i + 1) * 400, 300, 400, 30, 0, 0, 0, L"Noto Sans CJK KR DemiLight", menu.c_str(), 1);
		}

		for (int i = 0; i < 3; i++) {
			wstring menu;
			for (int j = 0; j < food_dormi[day][i].size(); j++) {
				menu += food_dormi[day][i][j];
				menu += L"\n";
			}
			Draw.Text(750, 140 + (400 - Draw.Text_Rect_y(30, L"Noto Sans CJK KR DemiLight", menu.c_str())) / 2 + i * 400, 300, 400, 30, 0, 0, 0, L"Noto Sans CJK KR DemiLight", menu.c_str(), 1);
		}
		break; }
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}