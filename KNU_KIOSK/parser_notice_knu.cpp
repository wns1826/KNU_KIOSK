#include "stdafx.h"
#include "header.h"

//#define LINK1 L"http://www.kunsan.ac.kr/board/list.kunsan?boardId=BBS_0000008&menuCd=DOM_000000105001001000&contentsSid=211&startPage=1&orderBy=REGISTER_DATE+DESC&listCel=1&sso=ok&categoryCode1=&searchType=DATA_TITLE&keyword=&listRow=100"
#define LINK2 ""
#define LINK3 ""
#define LINK4 ""

string find_tbody(GumboNode* root) {
	/*const GumboVector* root_children = &root->v.element.children;
	GumboNode* tbody = NULL;
	for (int i = 0; i < root_children->length; ++i) {
		GumboNode* child = (GumboNode*)root_children->data[i];
		if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TBODY) {
			tbody = child;
			break;
		}
	}

	GumboVector* tbody_children = &tbody->v.element.children;
	for (int i = 0; i < tbody_children->length; ++i) {
		GumboNode* child = (GumboNode*)tbody_children->data[i];
		if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TR) {
			if (child->v.element.children.length != 1) {
				return "<empty title>";
			}
			GumboNode* title_text = (GumboNode*)child->v.element.children.data[0];
			return title_text->v.text.text;
		}
	}*/
	return "<no title found>";
}

void add_notice(GumboNode* node) {
	GumboVector* children = &node->v.element.children;
	for (unsigned int i = 0; i < children->length; ++i) {
		find_tbody(static_cast<GumboNode*>(children->data[i]));
	}
}

int parser_notice_knu() {
	string html;
	http_get_curl_exe(LINK1, html);

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody(parse->root);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}