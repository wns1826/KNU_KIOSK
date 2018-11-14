#include "stdafx.h"
#include "header.h"

int find_tbody_knu_calendar(GumboNode *, int);
int add_calendar(GumboNode *, int);

int parser_calendar_1() { //학부
	string html = curl_http_get(L"http://www.kunsan.ac.kr/index.kunsan?menuCd=DOM_000000103001001000&sso=ok");

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody_knu_calendar(parse->root, 1);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int parser_calendar_2() { //대학원
	string html = curl_http_get(L"http://www.kunsan.ac.kr/index.kunsan?menuCd=DOM_000000103001002000");

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody_knu_calendar(parse->root, 2);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int find_tbody_knu_calendar(GumboNode* node, int type) { //type 1=학부, 2=대학원
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}
	else if (node->v.element.tag == GUMBO_TAG_TBODY) {
		add_calendar(node, type);
		return 1;
	}

	GumboVector* children = &node->v.element.children;
	for (int i = 0; i < children->length; ++i) {
		if (find_tbody_knu_calendar(static_cast<GumboNode*>(children->data[i]), type) == 1)
			break;
	}
	return 0;
}

int add_calendar(GumboNode* tbody, int type) {
	GumboVector* tbody_child = &tbody->v.element.children;
	for (int i = 0; i < tbody_child->length; i++) {
		GumboNode* tr = (GumboNode*)tbody_child->data[i];
		if (tr->type == GUMBO_NODE_ELEMENT && tr->v.element.tag == GUMBO_TAG_TR) {
			GumboVector* tr_child = &tr->v.element.children;
		}
	}
	return 0;
}