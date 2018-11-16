#include "stdafx.h"
#include "header.h"

HINSTANCE hInstance;

HWND hwnd;
HWND h_init;
HWND h_main;

//main_child
HWND h_clock;
HWND h_child;
HWND h_menu;
HWND h_popup;
//main_popup
HWND h_post;
HWND h_tag;

SOCKET sock = SOCKET_ERROR;

tm* update_last;
int update_h, update_m;

vector<notice> title;						//����
vector<wstring> food_knu_student[7][2];		//�н�
vector<wstring> food_knu_teacher[7][2];		//��������
vector<wstring> food_dormi[7][3];			//������
vector<wstring> knu_popup;					//�˾� ��� (�̹��� �Ľ� �� �ٿ���� ���� ���[%TEMP%\\kiosk_popup_{num}.jpg])

HANGUL Hangul;

bool init_end = false;

const wchar_t day_text[8] = L"�Ͽ�ȭ�������";
//init ���� �ִϸ��̼�
const wchar_t init_title_1[12][6] = {
	L"��_",
	L"��_",
	L"��_",
	L"����_",
	L"����_",
	L"����_",
	L"���ꤧ_",
	L"�����_",
	L"����뤷_",
	L"�������_",
	L"�������_",
	L"�������" };
const wchar_t init_title_2[6][4] = {
	L"��_",
	L"��_",
	L"��_",
	L"���_",
	L"���_",
	L"���" };
const wchar_t init_title_3[9][5] = {
	L"��_",
	L"��_",
	L"��_",
	L"����_",
	L"����_",
	L"������_",
	L"������_",
	L"������_",
	L"������" };
const wchar_t init_title_4[7][4] = {
	L"��_",
	L"��_",
	L"��_",
	L"�㤧_",
	L"���_",
	L"���_",
	L"���" };
const wchar_t init_title_4_ani[2][4] = {
	L"���",
	L"���_" };
const wchar_t init_title_empty[1] = L"";

//main ���� ī�װ�
const int category_num[8] = { 1, 2, 3, 2, 2, 1, 1, 1 };
const int category_color[8][3] = { {0, 0, 0}, {129, 210, 55}, {255, 53, 143}, {255, 98, 0}, {127, 100, 169}, {84, 125, 190}, {174, 238, 81}, {7, 223, 228} };
const wstring category[8][3] = {
	{L"����", L"", L""},
	{L"�л�", L"����", L"" },
	{L"����", L"�ȳ�", L"����" },
	{L"���", L"�ȳ�", L"" },
	{L"����", L"����", L"" },
	{L"�����", L"", L"" },
	{L"�а�", L"", L"" },
	{L"��Ÿ", L"", L"" },
};