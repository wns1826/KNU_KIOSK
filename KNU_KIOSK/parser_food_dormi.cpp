#include "stdafx.h"
#include "header.h"

int parser_food_dormi() {
	string html = curl_http_get(L"http://www.kunsan.ac.kr/dormi/index.kunsan?menuCd=DOM_000000704006000000");

	GumboOutput* parse = gumbo_parse(html.c_str());
	//find_tbody(parse->root);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}