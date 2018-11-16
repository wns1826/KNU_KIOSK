#pragma once

using namespace std;

#define IP "52.231.154.58"
#define PORT 4996

//����
#define WM_REDRAW			WM_APP  + 1
#define WM_RECV				WM_APP  + 2
//proc_init
#define WM_PROCESSING		WM_USER + 1
#define WM_UPDATE_STATUS	WM_USER + 2
//proc_main
#define WM_PAGE				WM_USER + 1
//proc_popup_post
#define WM_URL				WM_USER + 1

struct notice {
	int date = 0;
	int view = 0;
	int category; //1=���� 2=�л� 3=���� 4=��� 5=���� 6=����� 7=�а� 8=��Ÿ
	wstring title;
	wstring name;
	wstring url;
	wstring file;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_init(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main_notice(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main_food(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main_calendar(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main_bus(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main_clock(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main_menu(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_main_popup(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_popup_post(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK proc_popup_tag(HWND, UINT, WPARAM, LPARAM);

void WndReg();
void thread_init(HWND);
void setup();

int parser_notice_knu_1();	//�б� ����
int parser_notice_knu_2();	//�б� �л�/����
int parser_notice_knu_3();	//�б� ����/�ȳ�/����
int parser_notice_knu_4();	//�б� ���/�ȳ�
int parser_notice_knu_5();	//�б� ����/����
int parser_notice_dormi();	//����� ����
int parser_notice_cie();	//�а� ����
int parser_food_knu();		//�н�+��������
int parser_food_dormi();	//������
int parser_calendar_1();	//�к� �л�����
int parser_calendar_2();	//���п� �л�����
int parser_bus();			//���й���
int parser_popup();			//�б� ��� �˾�

int curl_http_get(const char *, string &);
string curl_http_get(const wchar_t *); 
int curl_http_get_download(string, string);

int sock_send_c(SOCKET, char);
int sock_send(SOCKET, const char *);
int sock_send_t(SOCKET);
int sock_recv_c(SOCKET);
int sock_send_n(SOCKET sock, const char *);
int sock_recv_n(SOCKET, char *, int);
int sock_recv(SOCKET, char *, int);
int sock_recv_n(SOCKET, char *);
int sock_recv_d(SOCKET);
int sock_recv_w(SOCKET, char *, int);

wchar_t* EncodeCharToWchar(const char *);
char* EncodeWcharToChar(const wchar_t *);

extern HINSTANCE hInstance;
extern HWND hwnd;
extern HWND h_init;
extern HWND h_main;

//main_child
extern HWND h_clock;
extern HWND h_child;
extern HWND h_menu;
extern HWND h_popup;
//main_popup
extern HWND h_post;
extern HWND h_tag;

extern SOCKET sock;

extern tm* update_last;
extern int update_h, update_m;

extern vector<notice> title;
extern vector<wstring> food_knu_student[7][2];
extern vector<wstring> food_knu_teacher[7][2];
extern vector<wstring> food_dormi[7][3];
extern vector<wstring> knu_popup;

extern bool init_end;

extern const wchar_t day_text[8];
extern const wchar_t init_title_1[12][6];
extern const wchar_t init_title_2[6][4];
extern const wchar_t init_title_3[9][5];
extern const wchar_t init_title_4[7][4];
extern const wchar_t init_title_4_ani[2][4];
extern const wchar_t init_title_empty[1];

extern const int category_num[8];
extern const int category_color[8][3];
extern const wstring category[8][3];