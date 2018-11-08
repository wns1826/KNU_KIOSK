#include "stdafx.h"
#include "header.h"

const wchar_t init_title_1[12][6] = {
	L"ㄱ_",
	L"구_",
	L"군_",
	L"군ㅅ_",
	L"군사_",
	L"군산_",
	L"군산ㄷ_",
	L"군산대_",
	L"군산대ㅇ_",
	L"군산대으_",
	L"군산대의_",
	L"군산대의" };
const wchar_t init_title_2[6][4] = {
	L"ㅁ_",
	L"모_",
	L"모ㄷ_",
	L"모드_",
	L"모든_",
	L"모든" };
const wchar_t init_title_3[9][5] = {
	L"ㄱ_",
	L"고_",
	L"공_",
	L"공ㅈ_",
	L"공지_",
	L"공지ㄹ_",
	L"공지르_",
	L"공지를_",
	L"공지를" };
const wchar_t init_title_4[7][4] = {
	L"ㄷ_",
	L"다_",
	L"담_",
	L"담ㄷ_",
	L"담다_",
	L"담다_",
	L"담다" };
const wchar_t init_title_4_ani[2][4] = {
	L"담다",
	L"담다_" };
const wchar_t init_title_empty[] = L"";

void thread_init(HWND hWnd) {

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"서버에 연결하는 중", NULL);
	//return;

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"공지사항 업데이트 중", NULL);
	parser_notice_knu_1();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"학사/장학 갱신 중", NULL);
	parser_notice_knu_2();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"모집/안내/공고 갱신 중", NULL);
	parser_notice_knu_3();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"행사/뉴스 갱신 중", NULL);
	parser_notice_knu_4();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"교육/연구 갱신 중", NULL);
	parser_notice_knu_5();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"학과 공지사항 갱신 중", NULL);
	parser_notice_cie();

/*	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"기숙사 공지사항 갱신 중", NULL);
	parser_notice_dormi();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"학식 갱신 중", NULL);
	parser_food_knu();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"기숙사식 갱신 중", NULL);
	parser_food_dormi();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"마무리 중", NULL);
	//PostMessage(h_child, WM_, NULL, NULL);*/

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"완료", NULL);
	
	InvalidateRect(h_list, NULL, FALSE);
	PostMessage(hWnd, WM_DESTROY, NULL, NULL);
	return;
}

LRESULT CALLBACK proc_init(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static WEBVIEW WebView;
	static int a = 255;
	static int a_time = 0;
	static int cnt_txt = 0;
	static const wchar_t *t1, *t2, *t3, *t4;
	static bool ani = true;
	static bool end = false;
	static thread *th_init;
	static wstring status_text = L"준비 중";
	switch (iMessage) {
	case WM_CREATE: {

		WebView.Size(250, 250);
		WebView.AddressBar(false);
		WebView.MenuBar(false);
		WebView.ToolBar(false);
		WebView.Navigate(L"kiosk.youn.in/progress.html");
		WebView.SParent(hWnd);
		WebView.SPos(415, 1450);

		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, NULL, 0, LWA_ALPHA);

		a_time = clock();
		SetTimer(hWnd, 1, 10, NULL);

		t1 = t2 = t3 = t4 = init_title_empty;

		//PostMessage(hWnd, WM_PROCESSING, 1, NULL);

		break; }
	case WM_PAINT: {
		DRAW Draw(hWnd);
		//Draw.Rect(0, 0, 1080, 1920, 255, 255, 255);
		Draw.Rect(0, 0, 1080, 1920, 255, 210, 0);
		Draw.Draw(0, 0, 1080, 1920, L"resource\\image\\init\\init.png");
		//Draw.Rect(110, 1680, 862, 140, 50, 50, 50, 150);
		//Draw.Text(83, 55, 862, 150, 117, 0, 0, 0, L"Noto Sans CJK KR Thin", L"군산대의");
		Draw.Text(83, 162, 862, 150, 117, 0, 0, 0, L"Noto Sans CJK KR Thin", t1);
		Draw.Text(83, 289, 862, 150, 117, 0, 0, 0, L"Noto Sans CJK KR Thin", t2);
		Draw.Text(83, 416, 862, 150, 117, 0, 0, 0, L"Noto Sans CJK KR Thin", t3);
		Draw.Text(83, 543, 862, 150, 117, 0, 0, 0, L"Noto Sans CJK KR Thin", t4);
		Draw.Text(110, 1705, 862, 140, 50, 244, 118, 9, L"Noto Sans CJK KR Regular", status_text.c_str(), 1);
		break; }
	case WM_TIMER: {
		switch (wParam) {
		case 1: //페이드인
			a = (int)(((clock() - a_time) / 1200.0) * 255);
			if (255 <= a) {
				a = 255;
				KillTimer(hWnd, 1);
				cnt_txt = 0;
				th_init = new thread(&thread_init, hWnd);
				SetTimer(hWnd, 3, 130, NULL);
				ShowWindow(h_main, SW_SHOW);
			}
			SetLayeredWindowAttributes(hWnd, NULL, a, LWA_ALPHA);
			break;
		case 2: //페이드아웃
			a = (int)(((clock() - a_time) / 1200.0) * 255);
			if (255 <= a) {
				a = 255;
				KillTimer(hWnd, 2);
				DestroyWindow(hWnd);
			}
			SetLayeredWindowAttributes(hWnd, NULL, 255 - a, LWA_ALPHA);
			break;
		case 3: //텍스트 애니메이션 11 5 8 6
			if (cnt_txt < 11)
				t1 = init_title_1[cnt_txt], t2 = t3 = t4 = init_title_empty;
			else if (cnt_txt < 16)
				t1 = init_title_1[11], t2 = init_title_2[cnt_txt - 11], t3 = t4 = init_title_empty;
			else if (cnt_txt < 24)
				t1 = init_title_1[11], t2 = init_title_2[5], t3 = init_title_3[cnt_txt - 16], t4 = init_title_empty;
			else if (cnt_txt < 29)
				t1 = init_title_1[11], t2 = init_title_2[5], t3 = init_title_3[8], t4 = init_title_4[cnt_txt - 24];
			else if (cnt_txt == 29) {
				ani = true;
				SetTimer(hWnd, 4, 500, NULL);
			}
			else if (50 < cnt_txt) {
				cnt_txt = 30;
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
				SetTimer(hWnd, 5, 60, NULL);
				break;
			}
			cnt_txt++;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 4: //_
			if (ani) {
				t4 = init_title_4_ani[0];
				ani = false;
			}
			else {
				t4 = init_title_4_ani[1];
				ani = true;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 5:
			if (cnt_txt < -50) {
				cnt_txt = 0;
				KillTimer(hWnd, 5);
				KillTimer(hWnd, 6);
				SetTimer(hWnd, 3, 130, NULL);
				break;
			}
			else if (cnt_txt < -1);
			else if (cnt_txt == -1) {
				ani = true;
				SetTimer(hWnd, 6, 500, NULL);
			}
			else if (cnt_txt == 0)
				t1 = L"_", t2 = t3 = t4 = init_title_empty;
			else if (cnt_txt < 11)
				t1 = init_title_1[cnt_txt], t2 = t3 = t4 = init_title_empty;
			else if (cnt_txt < 16)
				t1 = init_title_1[11], t2 = init_title_2[cnt_txt - 11], t3 = t4 = init_title_empty;
			else if (cnt_txt < 24)
				t1 = init_title_1[11], t2 = init_title_2[5], t3 = init_title_3[cnt_txt - 16], t4 = init_title_empty;
			else if (cnt_txt < 30)
				t1 = init_title_1[11], t2 = init_title_2[5], t3 = init_title_3[8], t4 = init_title_4[cnt_txt - 24];
			cnt_txt--;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 6: //_
			if (ani) {
				t1 = L"";
				ani = false;
			}
			else {
				t1 = L"_";
				ani = true;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		break; }
	case WM_UPDATE_STATUS: {
		status_text = (const wchar_t*)wParam;
		InvalidateRect(hWnd, NULL, FALSE);
		break; }
	case WM_DESTROY: {
		if (!end) {

			KillTimer(hWnd, 1);
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 4);
			KillTimer(hWnd, 5);
			KillTimer(hWnd, 6);

			t1 = init_title_1[11], t2 = init_title_2[5], t3 = init_title_3[8], t4 = init_title_4[6];
			InvalidateRect(hWnd, NULL, FALSE);

			a_time = clock();
			SetTimer(hWnd, 2, 10, NULL);
			end = true;
			return 0;
		}
		WebView.~WEBVIEW();
		break; }
	case WM_CLOSE:
	case WM_QUIT:
	case WM_QUERYENDSESSION:
		DestroyWindow(h_main);
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}