#include "stdafx.h"
#include "header.h"

LRESULT CALLBACK proc_main(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static HWND h_clock;
	switch (iMessage) {
	case WM_CREATE: {
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 1080, 1920, 255, 255, 255);
		Draw.Text(0, 0, 1080, 100, 50, 0, 0, 0, L"¸¼Àº °íµñ", L"", 1);
		Draw.Draw(0, 0, 279, 73, L"resource\\image\\list\\logo+txt.png");
		//Draw.Draw(0, 1641, 1080, 279, L"resource\\image\\list\\1.jpg");
		h_clock = CreateWindow(L"kiosk_list_clock", L"list_clock", WS_CHILD | WS_VISIBLE, 800, 0, 280, 100, hWnd, (HMENU)NULL, hInstance, NULL);
		//Draw.Draw(1980)

		wstring cstr = L"";
		cout << title.size() << endl;
		for(int i = 0; i < title.size(); i++) {
			cstr += title[i].title;
			cstr += L"\n";
			cout << EncodeWcharToChar(title[i].category.c_str()) << " : " << EncodeWcharToChar(title[i].title.c_str()) << endl;
		}

		Draw.Text(50, 100, 980, 1650, 20, 0, 0, 0, L"¸¼Àº °íµñ", cstr.c_str());
		break; }
	case WM_TIMER: {
		switch (wParam) {
		case 1:
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

LRESULT CALLBACK proc_main_clock(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static int td = 0;
	const wchar_t d_text[] = L"ÀÏ¿ùÈ­¼ö¸ñ±ÝÅä";
	switch (iMessage) {
	case WM_CREATE: {
		SetTimer(hWnd, 1, 1000, NULL);
		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		Draw.Rect(0, 0, 280, 100, 255, 255, 255);

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

		Draw.Text(0, 0, 280, 100, 50, 0, 0, 0, L"¸¼Àº °íµñ", w_str, 2);

		break; }
	case WM_TIMER: {
		switch (wParam) {
		case 1: //¾÷µ¥ÀÌÆ®
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