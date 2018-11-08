#include "stdafx.h"
#include "header.h"

int parser_notice_cie() {
	string html;
	curl_http_get(L"http://cie.kunsan.ac.kr/view/notices_data/6/listdata.do?searchtype=undefined&search=&&page=0", html);

	GumboOutput* parse = gumbo_parse(html.c_str());
//	find_tbody(parse->root, L"ÇÐ°ú");
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}