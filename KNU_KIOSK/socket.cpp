#include "stdafx.h"

int sock_send_c(SOCKET sock, char ch) {
	char str[2] = { ch, 0 };
	int len;
	len = send(sock, str, 1, NULL);
	return len;
}

int sock_send(SOCKET sock, const char* str) {
	int len;
	len = send(sock, str, strlen(str), NULL);
	return len;
}

int sock_send_t(SOCKET sock) {
	int len;
	len = send(sock, "T", 1, NULL);
	return len == SOCKET_ERROR ? true : false;
}

int sock_send_n(SOCKET sock, const char* str, const char* str1) {
	int len;
	char buffer[102400];
	sprintf(buffer, "%s%.4d%s", str, strlen(str1), str1);
	len = send(sock, buffer, strlen(buffer), NULL);
	return len;
}

int sock_recv_c(SOCKET sock) {
	char str[2];
	int len;
	len = recv(sock, str, 1, NULL);
	if (len <= 0)
		return SOCKET_ERROR;
	return str[0];
}

int sock_recv(SOCKET sock, char *str, int size) {
	int len;
	len = recv(sock, str, size, NULL);
	if (len < 0)
		return len;
	str[len] = '\0';
	return len;
}

int sock_recv_n(SOCKET sock, char *str) {
	int len;
	len = recv(sock, str, 4, NULL);
	if (len == 4) {
		str[len] = '\0';
		int len = atoi(str);
		if (len == 0) {
			str[0] = '\0';
			return 0;
		}
		len = recv(sock, str, len, 0);
		if (len < 0)
			return len;
		str[len] = '\0';
		return len;
	}
	return SOCKET_ERROR;
}

int sock_recv_n(SOCKET sock, char *str, int len) {
	if (len == 0) {
		str[0] = '\0';
		return 0;
	}
	len = recv(sock, str, len, 0);
	if (len < 0)
		return len;
	str[len] = '\0';
	return len;
}

int sock_recv_d(SOCKET sock) {
	char str[1024];
	int len;
	len = recv(sock, str, 1024, NULL);
	return len;
}

int sock_recv_w(SOCKET sock, char *str, int size) {
	wchar_t buffer[1024];
	int len;
	len = recv(sock, (char *)buffer, size * sizeof(wchar_t), NULL);
//	EncodeWcharToChar(buffer, str);
	if (len < 0)
		return len;
	str[len] = '\0';
	return len;
}