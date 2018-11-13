#include "stdafx.h"
#include "header.h"

void thread_init(HWND hWnd) {

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"서버에 연결하는 중", NULL);
	////return;

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"공지사항 업데이트 중", NULL);
	parser_notice_knu_1();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"학사/장학 갱신 중", NULL);
	//parser_notice_knu_2();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"모집/안내/공고 갱신 중", NULL);
	//parser_notice_knu_3();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"행사/뉴스 갱신 중", NULL);
	//parser_notice_knu_4();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"교육/연구 갱신 중", NULL);
	//parser_notice_knu_5();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"학과 공지사항 갱신 중", NULL);
	//parser_notice_cie();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"기숙사 공지사항 갱신 중", NULL);
	//parser_notice_dormi();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"학식 갱신 중", NULL);
	//parser_food_knu();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"기숙사식 갱신 중", NULL);
	//parser_food_dormi();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"학사일정 갱신 중", NULL);
	//parser_calendar_1();
	//parser_calendar_2();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"통학버스 갱신 중", NULL);
	//parser_bus();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"통학버스 갱신 중", NULL);
	//parser_popup();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"마무리 중", NULL);
	sort(title.begin(), title.end(), [](const notice &t1, const notice &t2) {
		if (t2.date < t1.date) {
			return true;
		}
		else if (t2.date == t1.date) {
			return t2.view < t1.view;
		}
		else {
			return false;
		}
	});
	InvalidateRect(h_main, NULL, FALSE);

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"완료", NULL);
	PostMessage(hWnd, WM_DESTROY, NULL, NULL);

	return;
}