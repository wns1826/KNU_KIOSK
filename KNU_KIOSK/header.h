#pragma once

using namespace std;

#define IP "127.0.0.1"
#define PORT 2018

//proc_init
#define WM_PROCESSING		WM_USER + 1
#define WM_UPDATE_STATUS	WM_USER + 2

struct notice {
	int date = 0;
	int view = 0;
	wstring category;
	wstring title;
	wstring name;
	wstring url;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_init(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main_clock(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_post(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_tag(HWND, UINT, WPARAM, LPARAM);

int curl_http_get(const wchar_t *url, string &html);

int parser_notice_knu_1();
int parser_notice_knu_2();
int parser_notice_knu_3();
int parser_notice_knu_4();
int parser_notice_knu_5();
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

wchar_t* EncodeCharToWchar(const char *);
char* EncodeWcharToChar(const wchar_t *);

extern HINSTANCE hInstance;
extern HWND h_main;
extern HWND h_init;
extern HWND h_list;

extern vector<notice> title;