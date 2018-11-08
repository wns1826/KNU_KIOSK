#include "stdafx.h"
#include "header.h"

class WEBVIEW {
public:
	WEBVIEW();
	~WEBVIEW();

	//READ
	void URL(wchar_t *); //URL
	BSTR Name(void); //�̸�
	HRESULT ReadyState(void); //�غ����
	HWND hWnd(void); //�ڵ�
	BSTR Type(void); //Ÿ��

	bool MenuBar(void); //�޴���
	bool ToolBar(void); //����
	bool AddressBar(void); //�ּ�â
	bool StatusBar(void); //���¹�
	bool Resizable(void); //ũ�� ����
	bool Silent(void); //��ȭ����
	bool FullScreen(void); //��üȭ��
	bool TheaterMode(void); //������
	bool Visible(void); //ȭ�� ǥ��
	long Top(void); //����
	long Left(void); //����
	long Height(void); //����
	long Width(void); //����		

	//WRITE
	void Refresh(void); //���� ��ħ
	void Quit(void); //����
	void Stop(void); //����
	void Navigate(const wchar_t *); //�̵�
	void GoBack(void); //����
	void GoForward(void); //����
	void GoHome(void); //Ȩ

	void MenuBar(bool); //�޴���
	void ToolBar(bool); //����
	void AddressBar(bool); //�ּ�â
	void StatusBar(bool); //���¹�
	void Resizable(bool); //ũ�� ����
	void Silent(bool); //��ȭ����
	void FullScreen(bool); //��üȭ��
	void TheaterMode(bool); //������
	void Visible(bool); //ȭ�� ǥ��
	void Top(long); //����
	void Left(long); //����
	void Height(long); //����
	void Width(long); //����

	void Pos(long, long); //��ǥ
	void Pos(long, long, long, long); //��ǥ+ũ��
	void Size(long, long); //ũ��

	void SPos(long, long);
	void SPos(long, long, long, long);
	void SSize(long, long);

	HWND ShWnd();
	HWND SParent(HWND);

private:
	IWebBrowser2* pWebBrowser = nullptr;
	HWND hServer = NULL;
};

