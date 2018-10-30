#pragma once

#define IP "127.0.0.1"
#define PORT 2018

//proc_init
#define WM_PROCESSING		WM_USER + 1
#define WM_UPDATE_STATUS	WM_USER + 2

using namespace std;

struct notice {
	string title;
	string name;
	string url;
	int date = 0;
	int view = 0;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_init(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main_clock(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_post(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_tag(HWND, UINT, WPARAM, LPARAM);

bool http_get_curl(const char *url, string &html); 
int http_get_curl_exe(const wchar_t *url, string &html);
int http_get_socket(std::string ip, string host, string get, int port, string &html);

int parser_notice_knu();
int parser_notice_dormi();
int parser_notice_cie();
int parser_food_knu();
int parser_food_dormi();

int sock_send_c(SOCKET, char);
int sock_send(SOCKET, const char *);
int sock_send_t(SOCKET);
int sock_recv_c(SOCKET);
int sock_send_n(SOCKET, const char *, const char *);
int sock_recv_n(SOCKET, char *, int);
int sock_recv(SOCKET, char *, int);
int sock_recv_n(SOCKET, char *);
int sock_recv_d(SOCKET);
int sock_recv_w(SOCKET, char *, int);

wchar_t* EncodeCharToWchar(const char *, wchar_t *);
char* EncodeWcharToChar(const wchar_t *);

extern HINSTANCE hInstance;
extern HWND h_main;
extern HWND h_init;
extern HWND h_child;

//temp
#define LINK L"http://naver.com"
#define LINK1 L"http://google.com"