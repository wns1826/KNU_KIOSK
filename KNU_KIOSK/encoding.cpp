#include "stdafx.h"
#include "header.h"

wchar_t* EncodeCharToWchar(const char* c_str) {
	int nLen = MultiByteToWideChar(CP_ACP, 0, c_str, strlen(c_str), NULL, NULL);
	wchar_t* str = new wchar_t[nLen + 2];
	MultiByteToWideChar(CP_ACP, 0, c_str, strlen(c_str), str, nLen);
	str[nLen] = 0;
	return str;
}

char* EncodeWcharToChar(const wchar_t* str) {
	int nLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	char* c_str = new char[nLen + 2];
	WideCharToMultiByte(CP_ACP, 0, str, -1, c_str, nLen, NULL, NULL);
	c_str[nLen] = 0;
	return c_str;
}