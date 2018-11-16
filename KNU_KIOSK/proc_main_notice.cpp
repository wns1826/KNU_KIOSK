#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_main_notice(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) { //1400
	static int ani_time;
	static int fps = 0;
	static int time_count = 0; //100ms 단위로 카운트
	switch (iMessage) {
	case WM_CREATE: {
		ani_time = clock();
		SetTimer(hWnd, 1, 30, NULL);
		SetTimer(hWnd, 2, 100, NULL);
		break; }
	case WM_PAINT: {
		if (init_end == false)
			break;
		DRAW Draw(hWnd);
		wchar_t w_str[100];
		Draw.Rect(0, 0, 1080, 1400, 255, 255, 255);

		Draw.Text(20, 5, 1080, 100, 70, 0, 0, 0, L"Noto Sans CJK KR DemiLight", L"공지사항");
		wsprintf(w_str, L"%.2d시 %.2d분에 업데이트 됨", update_h, update_m);
		Draw.Text(770, 75, 230, 30, 20, 0, 0, 0, L"Noto Sans CJK KR DemiLight", w_str);
		Draw.Draw(995, 50, 60, 60, L"resource\\image\\list\\update1.png");
		Draw.Line(30, 110, 1050, 110, 1, 0, 0, 0);
		
		if (10000 <= clock() - ani_time) {
			ani_time = clock() + 1500;
			printf("FPS = %g\n", fps / 10.0);
			fps = 0;
		}
		fps++;
		//제목 120~950
		for (int i = 0; i < 16; i++) {
			if (i < title.size()) {
				int over = Draw.Text_Rect_x(50, L"Noto Sans CJK KR Light", title[i].title.c_str()) - 800;
				int time = clock() - ani_time;
				if (over < 0) over = 0;
				if (time < 0) time = 0;
				if (time > 8500) time = 8500;
				int pos = 120 - over * (time / 8000.0);
				Draw.Text(pos, 110 + i * 80, 3000, 70, 50, 0, 0, 0, L"Noto Sans CJK KR Light", title[i].title.c_str());
			}
		}
		
		Draw.Rect(0, 113, 120, 1400, 255, 255, 255);
		Draw.Rect(950, 113, 130, 1400, 255, 255, 255);
		//분류
		for (int i = 0; i < 16; i++) {
			if (i < title.size()) {
				Draw.Text(20, 125 + i * 80, 100, 70, 30, category_color[title[i].category - 1][0], category_color[title[i].category - 1][1], category_color[title[i].category - 1][2], L"Noto Sans CJK KR Light", category[title[i].category - 1][(time_count / 10) % category_num[title[i].category - 1]].c_str(), 1);
			}
		}

		time_t t = std::time(0);
		tm* now = std::localtime(&t);

		//날짜
		for (int i = 0; i < 16; i++) {
			if (title.size() != 0) {
				if (title.size() >= i) {
					if (now->tm_mday - (title[i].date % 100) == 0)
						wsprintf(w_str, L"오늘", now->tm_mday - (title[i].date % 100));
					else
						wsprintf(w_str, L"%d일 전", now->tm_mday - (title[i].date % 100));
					Draw.Text(955, 125 + i * 80, 100, 80, 30, 0, 0, 0, L"Noto Sans CJK KR Light", w_str, 1);
				}
			}
		}
		break; }
	case WM_TIMER:
		switch (wParam) {
		case 1:
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 2:
			time_count++;
			break;
		}
		break;
	case WM_LBUTTONUP: {
		//110 + i + 80
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		int num = (y - 110) / 80;
		if (990 <= x && x <= 1050 && 50 <= y && y <= 110) {
			setup();
			h_init = CreateWindow(L"kiosk_init", L"init", WS_POPUP | WS_VISIBLE, 0, 0, 1080, 1920, hWnd, (HMENU)NULL, hInstance, NULL);
		}
		else if (y >= 110) {
			h_post = CreateWindowEx(WS_EX_TOPMOST, L"kiosk_popup_post", L"popup", WS_POPUP | WS_THICKFRAME | WS_VISIBLE, 50, 250, 980, 1200, hWnd, NULL, hInstance, NULL);
			PostMessage(h_post, WM_USER + 1, (WPARAM)title[num].url.c_str(), NULL);
		}
		break; }
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}