#include "stdafx.h"
#include "header.h"

extern HANGUL Hangul;

int find_tbody_food_knu(GumboNode *);
int add_food_knu(GumboNode *);

int parser_food_knu() {
	string html = curl_http_get(L"http://www.kunsan.ac.kr/board/list.kunsan?boardId=BBS_0000641&menuCd=DOM_000000104002007000&contentsSid=3778&cpath=");

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody_food_knu(parse->root);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int find_tbody_food_knu(GumboNode* node) {
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}
	else if (node->v.element.tag == GUMBO_TAG_TBODY) {
		add_food_knu(node);
		return 1;
	}

	GumboVector* children = &node->v.element.children;
	for (int i = 0; i < children->length; ++i) {
		if (find_tbody_food_knu(static_cast<GumboNode*>(children->data[i])) == 1)
			break;
	}
	return 0;
}

int add_food_knu(GumboNode* tbody) {
	GumboVector* tbody_child = &tbody->v.element.children;
	int tr_num = 0;
	for (int i = 0; i < tbody_child->length; i++) {
		GumboNode* tr = (GumboNode*)tbody_child->data[i];
		if (tr->type == GUMBO_NODE_ELEMENT && tr->v.element.tag == GUMBO_TAG_TR) {
			GumboVector* tr_child = &tr->v.element.children;
			if (1 <= tr_num && tr_num <= 4) {
				int td_num = 0;
				for (int j = 0; j < tr_child->length; j++) {
					GumboNode* td = (GumboNode*)tr_child->data[j];
					if (td->type == GUMBO_NODE_ELEMENT && td->v.element.tag == GUMBO_TAG_TD) {
						GumboVector* td_child = &td->v.element.children;
						for (int k = 0; k < td_child->length; k++) {
							GumboNode* td_text = (GumboNode*)td_child->data[k];
							if (td_text->type == GUMBO_NODE_TEXT) {
								wstring menu = Hangul.del_space(Hangul.get(EncodeCharToWchar(td_text->v.text.text)));
								printf("%s\n", EncodeWcharToChar(menu.c_str()));
							}
						}
						printf("\n\n");
						td_num++;
					}
				}
			}
			tr_num++;
		}
	}
	return 0;
}