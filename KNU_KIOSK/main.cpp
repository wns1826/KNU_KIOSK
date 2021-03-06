#include "stdafx.h"
#include "header.h"

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	::hInstance = hInstance;

	WndReg();

	hwnd = CreateWindowEx(NULL, L"kiosk", L"군산대학교 공지 키오스크", WS_OVERLAPPEDWINDOW, 0, 0, 1080, 1920, NULL, (HMENU)NULL, hInstance, NULL);

	DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	dwStyle &= ~WS_OVERLAPPEDWINDOW;
	SetWindowLong(hwnd, GWL_STYLE, dwStyle);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void WndReg() {
	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = L"kiosk";
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_init;
	WndClass.lpszClassName = L"kiosk_init";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_main;
	WndClass.lpszClassName = L"kiosk_main";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_main_notice;
	WndClass.lpszClassName = L"kiosk_main_notice";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_main_food;
	WndClass.lpszClassName = L"kiosk_main_food";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_main_calendar;
	WndClass.lpszClassName = L"kiosk_main_calendar";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_main_bus;
	WndClass.lpszClassName = L"kiosk_main_bus";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_main_clock;
	WndClass.lpszClassName = L"kiosk_main_clock";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_main_menu;
	WndClass.lpszClassName = L"kiosk_main_menu";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_main_popup;
	WndClass.lpszClassName = L"kiosk_main_popup";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_popup_post;
	WndClass.lpszClassName = L"kiosk_popup_post";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = proc_popup_tag;
	WndClass.lpszClassName = L"kiosk_popup_tag";
	RegisterClass(&WndClass);
}