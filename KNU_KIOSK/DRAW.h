#pragma once

using namespace Gdiplus;

class DRAW
{
public:
	DRAW(HWND hWnd, BOOL mem = TRUE);
	void Rect(int x, int y, int size_x, int size_y, int r, int g, int b, int a = 255);
	void Bitmap(int x, int y, int size_x, int size_y, HBITMAP hBit);
	void Rotate(Graphics G, int rotate);
	void Draw(int x, int y, int size_x, int size_y, int resource_num, const wchar_t* Type);
	void Draw(int x, int y, int size_x, int size_y, const wchar_t* file);
	void Text(int x, int y, int size_x, int size_y, int font_size, int r, int g, int b, const wchar_t* font, const wchar_t* Str, int Alignment = 0);
	int Text_Rect(int x, int y, int size_x, int font_size, const wchar_t* font, const wchar_t* Str_t);
	~DRAW();
protected:
	HWND hWnd;
	RECT rc;
	PAINTSTRUCT ps;
public:
	HDC hdc;
protected:
	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	HDC MemDC;
	HBITMAP Backscreen;
	HBITMAP hPreBit;
	HDC BackDC;
	BITMAP bit;
	bool mem;
};
