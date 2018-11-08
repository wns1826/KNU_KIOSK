#include "stdafx.h"
#include "header.h"

WEBVIEW::WEBVIEW() {
	CoInitialize(NULL);
	::CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_ALL, IID_IWebBrowser2, (void**)&pWebBrowser);
}

WEBVIEW::~WEBVIEW() {
	Quit();
	pWebBrowser->Release();
	CoUninitialize();
}



void WEBVIEW::URL(wchar_t *c_str) {
	BSTR str;
	pWebBrowser->get_LocationURL(&str);
	wcscpy(c_str, str);
}

BSTR WEBVIEW::Name(void) {
	wchar_t c_str[1024];
	pWebBrowser->get_LocationName((BSTR*)c_str);
	return c_str;
}

HRESULT WEBVIEW::ReadyState(void) {
	return E_NOTIMPL;
}

HWND WEBVIEW::hWnd(void) {
	HWND hWnd_Web = NULL;
	pWebBrowser->get_HWND((SHANDLE_PTR *)&hWnd_Web);
	return hWnd_Web;
}

BSTR WEBVIEW::Type(void) {
	wchar_t c_str[1024];
	pWebBrowser->get_Type((BSTR*)c_str);
	return BSTR();
}



bool WEBVIEW::MenuBar(void) {
	VARIANT_BOOL b;
	pWebBrowser->get_MenuBar(&b);
	return b == VARIANT_TRUE ? true : false;
}

bool WEBVIEW::ToolBar(void) {
	VARIANT_BOOL b;
	pWebBrowser->get_MenuBar(&b);
	return b == VARIANT_TRUE ? true : false;
}

bool WEBVIEW::AddressBar(void) {
	VARIANT_BOOL b;
	pWebBrowser->get_MenuBar(&b);
	return b == VARIANT_TRUE ? true : false;
}

bool WEBVIEW::StatusBar(void) {
	VARIANT_BOOL b;
	pWebBrowser->get_MenuBar(&b);
	return b == VARIANT_TRUE ? true : false;
}

bool WEBVIEW::Resizable(void) {
	VARIANT_BOOL b;
	pWebBrowser->get_MenuBar(&b);
	return b == VARIANT_TRUE ? true : false;
}

bool WEBVIEW::Silent(void) {
	VARIANT_BOOL b;
	pWebBrowser->get_MenuBar(&b);
	return b == VARIANT_TRUE ? true : false;
}

bool WEBVIEW::FullScreen(void) {
	VARIANT_BOOL b;
	pWebBrowser->get_MenuBar(&b);
	return b == VARIANT_TRUE ? true : false;
}

bool WEBVIEW::TheaterMode(void) {
	VARIANT_BOOL b;
	pWebBrowser->get_MenuBar(&b);
	return b == VARIANT_TRUE ? true : false;
}

bool WEBVIEW::Visible(void) {
	VARIANT_BOOL b;
	pWebBrowser->get_MenuBar(&b);
	return b == VARIANT_TRUE ? true : false;
}

long WEBVIEW::Top(void) {
	long l;
	pWebBrowser->get_Top(&l);
	return l;
}

long WEBVIEW::Left(void) {
	long l;
	pWebBrowser->get_Left(&l);
	return l;
}

long WEBVIEW::Height(void) {
	long l;
	pWebBrowser->get_Height(&l);
	return l;
}

long WEBVIEW::Width(void) {
	long l;
	pWebBrowser->get_Width(&l);
	return l;
}



void WEBVIEW::Refresh(void) {
	pWebBrowser->Refresh();
}

void WEBVIEW::Quit(void) {
	pWebBrowser->Quit();
}

void WEBVIEW::Stop(void) {
	pWebBrowser->Stop();
}

void WEBVIEW::Navigate(const wchar_t *url) {
	VARIANT vtFlags, vtTarget, vtPostData, vtHeader;
	::VariantInit(&vtFlags);
	::VariantInit(&vtTarget);
	::VariantInit(&vtPostData);
	::VariantInit(&vtHeader);

	CComVariant *curl = new CComVariant(url);
	pWebBrowser->Navigate2(curl, &vtFlags, &vtTarget, &vtPostData, &vtHeader);

	HWND test = this->hWnd();
	ShowWindow(this->hWnd(), SW_HIDE);
}

void WEBVIEW::GoBack(void) {
	pWebBrowser->GoBack();
}

void WEBVIEW::GoForward(void) {
	pWebBrowser->GoForward();
}

void WEBVIEW::GoHome(void) {
	pWebBrowser->GoHome();
}



void WEBVIEW::MenuBar(bool b) {
	pWebBrowser->put_MenuBar(b ? VARIANT_TRUE : VARIANT_FALSE);
}

void WEBVIEW::ToolBar(bool b) {
	pWebBrowser->put_ToolBar(b ? VARIANT_TRUE : VARIANT_FALSE);
}

void WEBVIEW::AddressBar(bool b) {
	pWebBrowser->put_AddressBar(b ? VARIANT_TRUE : VARIANT_FALSE);
}

void WEBVIEW::StatusBar(bool b) {
	pWebBrowser->put_StatusBar(b ? VARIANT_TRUE : VARIANT_FALSE);
}

void WEBVIEW::Resizable(bool b) {
	pWebBrowser->put_Resizable(b ? VARIANT_TRUE : VARIANT_FALSE);
}

void WEBVIEW::Silent(bool b) {
	pWebBrowser->put_Silent(b ? VARIANT_TRUE : VARIANT_FALSE);
}

void WEBVIEW::FullScreen(bool b) {
	pWebBrowser->put_FullScreen(b ? VARIANT_TRUE : VARIANT_FALSE);
}

void WEBVIEW::TheaterMode(bool b) {
	pWebBrowser->put_TheaterMode(b ? VARIANT_TRUE : VARIANT_FALSE);
}

void WEBVIEW::Visible(bool b) {
	pWebBrowser->put_Visible(b ? VARIANT_TRUE : VARIANT_FALSE);
}

void WEBVIEW::Top(long l) {
	pWebBrowser->put_Top(l);
}

void WEBVIEW::Left(long l) {
	pWebBrowser->put_Left(l);
}

void WEBVIEW::Height(long l) {
	pWebBrowser->put_Height(l);
}

void WEBVIEW::Width(long l) {
	pWebBrowser->put_Width(l);
}



void WEBVIEW::Pos(long px, long py) {
	Left(px);
	Top(py);
}

void WEBVIEW::Pos(long px, long py, long sx, long sy) {
	Left(px);
	Top(py);
	Width(sx);
	Height(sy);
}

void WEBVIEW::Size(long sx, long sy) {
	Width(sx);
	Height(sy);
}



void WEBVIEW::SPos(long px, long py) {
	SetWindowPos(ShWnd(), NULL, px, py, NULL, NULL, SWP_NOSIZE);
}

void WEBVIEW::SPos(long px, long py, long sx, long sy) {
	SetWindowPos(ShWnd(), NULL, px, py, sx, sy, NULL);
}

void WEBVIEW::SSize(long sx, long sy) {
	SetWindowPos(ShWnd(), NULL, NULL, NULL, sx, sy, SWP_NOMOVE);
}



HWND WEBVIEW::ShWnd() {
	while(hServer == NULL) {
		hServer = FindWindowEx(hWnd(), NULL, TEXT("Frame Tab"), NULL);
		hServer = FindWindowEx(hServer, NULL, TEXT("TabWindowClass"), NULL);
		hServer = FindWindowEx(hServer, NULL, TEXT("Shell DocObject View"), NULL);
		hServer = FindWindowEx(hServer, NULL, TEXT("Internet Explorer_Server"), NULL);
	}
	return hServer;
}

HWND WEBVIEW::SParent(HWND hWnd) {
	if(hServer == NULL)
		ShWnd();
	SetParent(hServer, hWnd);
	return hServer;
}
