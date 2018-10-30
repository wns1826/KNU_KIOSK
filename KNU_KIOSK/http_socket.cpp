#include "stdafx.h"
#include "header.h"

int http_get_socket(std::string ip, std::string host, std::string get, int port, string &html) {
	WSADATA	WSAData;
	SOCKADDR_IN addr;
	SOCKET sock;
	std::string str;
	char c_str[1000000];
	int len;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) return NULL;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
		printf("%s 서버와의 통신에 실패하였습니다", host.c_str());
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	str.clear();
	str += "GET ";
	str += get;
	str += " HTTP/1.1\r\nHost: ";
	str += host;
	str += "\r\nConnection: keep-alive\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36\r\nAccept: */*\r\nAccept-Encoding: gzip, deflate, sdch\r\nAccept-Language: ko-KR,ko;q=0.8,en-US;q=0.6,en;q=0.4\r\n\r\n";

	cout << str << "\n\n\n";

	strcpy_s(c_str, str.c_str());
	if (sock_send(sock, c_str) == SOCKET_ERROR) {
		printf("요청 실패: %s", host);
		return -1;
	}
	if (sock_recv(sock, c_str, 102400) == SOCKET_ERROR) {
		printf("응답 오류: %s", host);
		return -1;
	}
	cout << c_str << "\n\n\n";

	if (sock_recv(sock, c_str, 1000000) == SOCKET_ERROR) {
		printf("응답 오류: %s", host);
		return -1;
	}
	closesocket(sock);


	//EncodeHttptoChar(c_str);
	//cout << c_str << "\n\n\n";
	//html = c_str;


	return 0;
}