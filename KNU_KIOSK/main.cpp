#include "stdafx.h"
#include "header.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )

HINSTANCE hInstance;
HWND hWnd;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	::hInstance = hInstance;

	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = L"KNU_KIOSK";
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);


	WndClass.lpfnWndProc = Proc_Init;
	WndClass.lpszClassName = L"kiosk_init";
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = Proc_List;
	WndClass.lpszClassName = L"kiosk_list";
	RegisterClass(&WndClass);

	hWnd = CreateWindowEx(WS_EX_TOPMOST, L"KNU_KIOSK", L"군산대학교 공지 키오스크", WS_OVERLAPPEDWINDOW, 1920, 0, 1080, 1920, NULL, (HMENU)NULL, hInstance, NULL);

	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	dwStyle &= ~WS_OVERLAPPEDWINDOW;
	SetWindowLong(hWnd, GWL_STYLE, dwStyle);

//	ShowWindow(hWnd, SW_SHOW);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}