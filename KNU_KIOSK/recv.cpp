#include "stdafx.h"
#include "header.h"

int server_recv() {

	while (1) {
		Sleep(10000);
		PostMessage(h_main, WM_USER + 0, NULL, NULL);
	}
	return 0;
}