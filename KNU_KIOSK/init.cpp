#include "stdafx.h"
#include "header.h"

void thread_init(HWND hWnd) {

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"������ �����ϴ� ��", NULL);
	////return;

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"�������� ������Ʈ ��", NULL);
	parser_notice_knu_1();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"�л�/���� ���� ��", NULL);
	//parser_notice_knu_2();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"����/�ȳ�/���� ���� ��", NULL);
	//parser_notice_knu_3();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"���/���� ���� ��", NULL);
	//parser_notice_knu_4();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"����/���� ���� ��", NULL);
	//parser_notice_knu_5();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"�а� �������� ���� ��", NULL);
	//parser_notice_cie();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"����� �������� ���� ��", NULL);
	//parser_notice_dormi();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"�н� ���� ��", NULL);
	//parser_food_knu();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"������ ���� ��", NULL);
	//parser_food_dormi();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"�л����� ���� ��", NULL);
	//parser_calendar_1();
	//parser_calendar_2();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"���й��� ���� ��", NULL);
	//parser_bus();

	//PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"���й��� ���� ��", NULL);
	//parser_popup();

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"������ ��", NULL);
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

	PostMessage(hWnd, WM_UPDATE_STATUS, (WPARAM)L"�Ϸ�", NULL);
	PostMessage(hWnd, WM_DESTROY, NULL, NULL);

	return;
}