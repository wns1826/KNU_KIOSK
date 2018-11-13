#include "stdafx.h"
#include "header.h"

int parser_bus() {
	string html = curl_http_get(L"http://www.kunsan.ac.kr/index.kunsan?menuCd=DOM_000000104002002003");

	GumboOutput* parse = gumbo_parse(html.c_str());

	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}