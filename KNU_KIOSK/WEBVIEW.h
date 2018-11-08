#include "stdafx.h"
#include "header.h"

class WEBVIEW {
public:
	WEBVIEW();
	~WEBVIEW();

	//READ
	void URL(wchar_t *); //URL
	BSTR Name(void); //이름
	HRESULT ReadyState(void); //준비상태
	HWND hWnd(void); //핸들
	BSTR Type(void); //타입

	bool MenuBar(void); //메뉴바
	bool ToolBar(void); //툴바
	bool AddressBar(void); //주소창
	bool StatusBar(void); //상태바
	bool Resizable(void); //크기 조정
	bool Silent(void); //대화상자
	bool FullScreen(void); //전체화면
	bool TheaterMode(void); //극장모드
	bool Visible(void); //화면 표시
	long Top(void); //위쪽
	long Left(void); //왼쪽
	long Height(void); //높이
	long Width(void); //길이		

	//WRITE
	void Refresh(void); //새로 고침
	void Quit(void); //종료
	void Stop(void); //중지
	void Navigate(const wchar_t *); //이동
	void GoBack(void); //이전
	void GoForward(void); //다음
	void GoHome(void); //홈

	void MenuBar(bool); //메뉴바
	void ToolBar(bool); //툴바
	void AddressBar(bool); //주소창
	void StatusBar(bool); //상태바
	void Resizable(bool); //크기 조정
	void Silent(bool); //대화상자
	void FullScreen(bool); //전체화면
	void TheaterMode(bool); //극장모드
	void Visible(bool); //화면 표시
	void Top(long); //위쪽
	void Left(long); //왼쪽
	void Height(long); //높이
	void Width(long); //길이

	void Pos(long, long); //좌표
	void Pos(long, long, long, long); //좌표+크기
	void Size(long, long); //크기

	void SPos(long, long);
	void SPos(long, long, long, long);
	void SSize(long, long);

	HWND ShWnd();
	HWND SParent(HWND);

private:
	IWebBrowser2* pWebBrowser = nullptr;
	HWND hServer = NULL;
};

