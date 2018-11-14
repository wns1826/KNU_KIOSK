#include "stdafx.h"

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

int curl_http_get(const char *url, string &html) {
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return 0;
}

int curl_http_get_download(string url, string file) {
	CURL *curl;
	FILE *fp;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(file.c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}
	return 0;
}

string curl_http_get(const wchar_t *url) {
	wchar_t path[1000];
	GetModuleFileName(NULL, path, 1000);
	PathRemoveFileSpec(path);
	
	wstring wstr;
	wstr = L"/c ";
	wstr += path;
	wstr += L"\\resource\\curl.exe - L - H \"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36\" \"";
	wstr += url;
	wstr += L"\" -o \"%TEMP%\\knu_kiosk.temp\"";

	wcout << wstr;
	
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
		::WaitForSingleObject(sei.hProcess, INFINITE);

	wstring temp = _wgetenv(L"TEMP");
	temp += L"\\knu_kiosk.temp";
	wifstream in(temp, std::ios::in | std::ios::binary);
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