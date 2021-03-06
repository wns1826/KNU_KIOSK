#pragma once

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "gdiplus")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "libcurld.lib")
#pragma comment(lib, "gumbo.lib")
#pragma comment(lib, "D2D1.lib")

#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <WinSock2.h>
#include <Windows.h>
#include <commctrl.h>
#include <GdiPlus.h>
#include <mshtml.h>
#include <exdisp.h>
#include <atlstr.h>
#include <d2d1.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <locale>
#include <codecvt>
#include <thread>

#include "DRAW.h"
#include "WEBVIEW.h"
#include "HANGUL.h"

#include "lib/curl/curl.h"
#include "lib/gumbo/gumbo.h"

extern HANGUL Hangul;