#include "stdafx.h"
#include "header.h"

int parser_calendar_1() { //학부
	string html = curl_http_get(L"http://www.kunsan.ac.kr/index.kunsan?menuCd=DOM_000000103001001000&sso=ok");

	GumboOutput* parse = gumbo_parse(html.c_str());

	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int parser_calendar_2() { //대학원
	string html = curl_http_get(L"http://www.kunsan.ac.kr/index.kunsan?menuCd=DOM_000000103001002000");

	GumboOutput* parse = gumbo_parse(html.c_str());

	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}