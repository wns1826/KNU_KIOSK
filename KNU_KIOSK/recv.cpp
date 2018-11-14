#include "stdafx.h"
#include "header.h"

int server_recv() {

	while (1) {
		int ch = sock_recv_c(sock);
		switch (ch) {
		case SOCKET_ERROR:
			return 0;
		case 'H':
			PostMessage(h_tag, WM_RECV, NULL, NULL);
		}
	}
	return 0;
}