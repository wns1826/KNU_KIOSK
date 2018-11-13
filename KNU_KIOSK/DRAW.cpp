#include "stdafx.h"
#include "header.h"

DRAW::DRAW(HWND hWnd, BOOL mem) {
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok) {
		MessageBox(hWnd, L"GDI+ 초기 작업중 오류가 발생하였습니다", L"오류", MB_ICONERROR);
	}
	this->hWnd = hWnd;
	this->mem = mem;
	GetClientRect(hWnd, &rc);
	hdc = BeginPaint(hWnd, &ps);
	if (mem) {
		MemDC = CreateCompatibleDC(hdc);
		Backscreen = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		hPreBit = (HBITMAP)SelectObject(MemDC, Backscreen);
		BackDC = CreateCompatibleDC(hdc);
	}
	else {
		MemDC = hdc;
	}
//	G = new Graphics(MemDC);
}

void DRAW::Rect(int x, int y, int size_x, int size_y, int r, int g, int b, int a) {
	Graphics G(MemDC);

	SolidBrush B(Color(a, r, g, b));
	G.FillRectangle(&B, x, y, size_x, size_y);
}

void DRAW::Draw(int x, int y, int size_x, int size_y, const wchar_t* file) {
	Graphics G(MemDC);
	Image I(file);
	if (I.GetLastStatus() != Ok) return;
	G.DrawImage(&I, x, y, size_x, size_y);
}

int DRAW::Text_Rect(int font_size, const wchar_t* font, const wchar_t* Str_t) {
	Graphics G(MemDC);
	CharacterRange cr(0, wcslen(Str_t));
	StringFormat sf;
	sf.SetMeasurableCharacterRanges(1, &cr);
	Font F(font, font_size, FontStyleRegular, UnitPixel);
	RectF O;
	Region rgn;

	G.MeasureCharacterRanges(Str_t, wcslen(Str_t), &F, RectF(0, 0, 10000, 80), &sf, 1, &rgn);
	RectF rt;

	rgn.GetBounds(&rt, &G);

	return rt.Width;
}

void DRAW::Text(int x, int y, int size_x, int size_y, int font_size, int r, int g, int b, const wchar_t* font, const wchar_t* Str, int Alignment) {
	Graphics G(MemDC);
	Font F(font, font_size, FontStyleRegular, UnitPixel);
	RectF R(x, y, size_x, size_y);
	SolidBrush B(Color(r, g, b));

	StringFormat sf;
	switch (Alignment) {
	case 0:
		sf.SetAlignment(StringAlignmentNear);
		break;
	case 1:
		sf.SetAlignment(StringAlignmentCenter);
		break;
	case 2:
		sf.SetAlignment(StringAlignmentFar);
		break;
	}

	G.SetTextRenderingHint(TextRenderingHintAntiAlias);
	G.DrawString(Str, -1, &F, R, &sf, &B);
}

void DRAW::Line(int x1, int y1, int x2, int y2, int line_size, int r, int g, int b, int a) {
	Graphics G(MemDC);
	Pen P(Color(r, g, b), line_size);
	G.DrawLine(&P, x1, y1, x2, y2);
}

DRAW::~DRAW()
{
	if (mem) {
		DeleteObject(BackDC);
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, hPreBit);
		DeleteObject(Backscreen);
		DeleteDC(MemDC);
	}
	EndPaint(hWnd, &ps);
	GdiplusShutdown(gpToken);
}