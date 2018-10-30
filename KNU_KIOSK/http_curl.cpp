#include "stdafx.h"
#include "header.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

bool http_get_curl(const char *url, string &html)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		struct curl_slist *chunk = NULL;

		chunk = curl_slist_append(chunk, "Connection: keep-alive");
		chunk = curl_slist_append(chunk, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36");
		chunk = curl_slist_append(chunk, "Accept: */*");
		chunk = curl_slist_append(chunk, "Accept-Encoding: gzip, deflate, sdch");
		chunk = curl_slist_append(chunk, "Accept-Language: ko-KR,ko;q=0.8,en-US;q=0.6,en;q=0.4");
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		return true;
	}
	else {
		return false;
	}
}

int http_get_curl_exe(const wchar_t *url, string &html) {

	wstring wstr;
	wstr = L"/c curl.exe -L -H \"User - Agent: Mozilla / 5.0 (Windows NT 10.0; Win64; x64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 69.0.3497.100 Safari / 537.36\" \"";
	wstr += url;
	wstr += L"\" -o \"C:\\KIOSK\\temp\\html\"";
	
	SHELLEXECUTEINFO sei;
	::ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));

	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.lpFile = L"cmd.exe";
	sei.lpParameters = wstr.c_str();
	sei.lpDirectory = L"C:\\KIOSK";
	sei.nShow = SW_HIDE;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = L"open";
	
	ShellExecuteEx(&sei);
	if (sei.hProcess != NULL)
	{
		::WaitForSingleObject(sei.hProcess, INFINITE);
	}

	wifstream in("C:\\KIOSK\\temp\\html", std::ios::in | std::ios::binary);
	in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	if (!in) {
		std::cout << "File not found!\n";
		return -1;
	}
	in.seekg(0, std::ios::end);
	wstr.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&wstr[0], wstr.size());
	in.close();

	char* cstr = EncodeWcharToChar(wstr.c_str());
	html = cstr;
	delete cstr;

	//html = std::wstring_convert<std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>>().to_bytes(wstr);

	//cout << html;

	return 0;
}