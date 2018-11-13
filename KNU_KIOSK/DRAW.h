#pragma once

using namespace Gdiplus;

class DRAW
{
public:
	DRAW(HWND hWnd, BOOL mem = TRUE);
	void Rect(int x, int y, int size_x, int size_y, int r, int g, int b, int a = 255);
	void Draw(int x, int y, int size_x, int size_y, const wchar_t* file);
	void Text(int x, int y, int size_x, int size_y, int font_size, int r, int g, int b, const wchar_t* font, const wchar_t* Str, int Alignment = 0);
	void Line(int x1, int y1, int x2, int y2, int line_size, int r, int g, int b, int a = 255);
	int Text_Rect(int font_size, const wchar_t* font, const wchar_t* Str_t);
	~DRAW();
private:
	HWND hWnd;
	RECT rc;
	PAINTSTRUCT ps;
	HDC hdc;
	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	HDC MemDC;
	HBITMAP Backscreen;
	HBITMAP hPreBit;
	HDC BackDC;
	BITMAP bit;
	bool mem;
//	Graphics* G;
};
