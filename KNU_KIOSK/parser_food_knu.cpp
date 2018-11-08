#include "stdafx.h"
#include "header.h"

int parser_food_knu() {
	string html;
	curl_http_get(L"temp", html);

	GumboOutput* parse = gumbo_parse(html.c_str());
	//find_tbody(parse->root);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}