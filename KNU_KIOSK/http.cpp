#include "stdafx.h"
#include "header.h"

extern HANGUL Hangul;

string curl_http_get(const wchar_t *url) {
	wstring wstr;
	wstr = L"/c curl.exe -L -H \"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36\" \"";
	wstr += url;
	wstr += L"\" -o \"%TEMP%\\knu_kiosk.temp\"";
	
	SHELLEXECUTEINFO sei;
	::ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));

	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.lpFile = L"cmd.exe";
	sei.lpParameters = wstr.c_str();
	sei.lpDirectory = L"C:\\KIOSK";
	sei.nShow = SW_HIDE;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = L"open";
	
	/*ShellExecuteEx(&sei);
	if (sei.hProcess != NULL)
	{
		::WaitForSingleObject(sei.hProcess, INFINITE);
	}*/

	wstring path = _wgetenv(L"TEMP");
	path += L"\\knu_kiosk.temp";
	wifstream in(path, std::ios::in | std::ios::binary);
	in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	if (!in)
		return "";
	in.seekg(0, std::ios::end);
	wstr.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&wstr[0], wstr.size());
	in.close();

	string html;
	char* cstr = EncodeWcharToChar(Hangul.set(wstr).c_str());
	html = cstr;
	delete cstr;

	return html;
}