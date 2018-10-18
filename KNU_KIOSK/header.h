#pragma once

#define IP "127.0.0.1"
#define PORT 2018

extern HINSTANCE hInstance;
extern HWND hWnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Proc_Init(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Proc_List(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Proc_Post(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Proc_Tag(HWND, UINT, WPARAM, LPARAM);