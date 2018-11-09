#include "stdafx.h"
#include "header.h"

int parser_food_knu() {
	string html = curl_http_get(L"http://www.kunsan.ac.kr/board/list.kunsan?boardId=BBS_0000641&menuCd=DOM_000000104002007000&contentsSid=3778&cpath=");

	GumboOutput* parse = gumbo_parse(html.c_str());
	//find_tbody(parse->root);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}