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

vector<notice> title;						//공지
vector<wstring> food_knu_student[7][2];		//학식
vector<wstring> food_knu_teacher[7][2];		//교직원식
vector<wstring> food_dormi[7][3];			//기숙사식
vector<wstring> knu_popup;					//팝업 경로 (이미지 파싱 후 다운받은 로컬 경로[%TEMP%\\kiosk_popup_{num}.jpg])

HANGUL Hangul;



//init 제목 애니메이션
const wchar_t init_title_1[12][6] = {
	L"ㄱ_",
	L"구_",
	L"군_",
	L"군ㅅ_",
	L"군사_",
	L"군산_",
	L"군산ㄷ_",
	L"군산대_",
	L"군산대ㅇ_",
	L"군산대으_",
	L"군산대의_",
	L"군산대의" };
const wchar_t init_title_2[6][4] = {
	L"ㅁ_",
	L"모_",
	L"모ㄷ_",
	L"모드_",
	L"모든_",
	L"모든" };
const wchar_t init_title_3[9][5] = {
	L"ㄱ_",
	L"고_",
	L"공_",
	L"공ㅈ_",
	L"공지_",
	L"공지ㄹ_",
	L"공지르_",
	L"공지를_",
	L"공지를" };
const wchar_t init_title_4[7][4] = {
	L"ㄷ_",
	L"다_",
	L"담_",
	L"담ㄷ_",
	L"담다_",
	L"담다_",
	L"담다" };
const wchar_t init_title_4_ani[2][4] = {
	L"담다",
	L"담다_" };
const wchar_t init_title_empty[1] = L"";

//main 공지 카테고리
const int category_num[8] = { 1, 2, 3, 2, 2, 1, 1, 1 };
const wstring category[8][3] = {
	{L"공지", L"", L""},
	{L"학사", L"장학", L"" },
	{L"모집", L"안내", L"공고" },
	{L"행사", L"안내", L"" },
	{L"교육", L"연구", L"" },
	{L"기숙사", L"", L"" },
	{L"학과", L"", L"" },
	{L"기타", L"", L"" },
};