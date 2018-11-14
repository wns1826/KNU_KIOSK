#include "stdafx.h"
#include "header.h"

void thread_init(HWND hWnd) {
	wchar_t w_str[1000];

	wcscpy(w_str, L"서버에 연결하는 중");
	for (int i = 1; sock == SOCKET_ERROR; i++) {
		PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)w_str, NULL);
		
		WSADATA	WSAData;
		SOCKADDR_IN addr;

		WSAStartup(MAKEWORD(2, 0), &WSAData);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET) return;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(PORT);
		addr.sin_addr.S_un.S_addr = inet_addr(IP);
		if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
			closesocket(sock);
			WSACleanup();
			sock = SOCKET_ERROR;
		}
		wsprintf(w_str, L"서버 연결 실패... 재시도 중 (%d)", i);
	}


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

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"팝업이미지 받는 중", NULL);
	parser_popup();

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