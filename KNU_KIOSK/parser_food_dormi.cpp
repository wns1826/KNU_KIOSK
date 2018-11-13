#include "stdafx.h"
#include "header.h"

int find_tbody_food_dormi(GumboNode *, int *);
int add_food_dormi(GumboNode *);

int parser_food_dormi() {
	string html = curl_http_get(L"http://www.kunsan.ac.kr/dormi/index.kunsan?menuCd=DOM_000000704006000000");

	GumboOutput* parse = gumbo_parse(html.c_str());
	int n = 0;
	find_tbody_food_dormi(parse->root, &n);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int find_tbody_food_dormi(GumboNode* node, int *n) {
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}
	else if (node->v.element.tag == GUMBO_TAG_TBODY) {
		(*n)++;
		if (*n == 2) {
			add_food_dormi(node);
			return 1;
		}
	}

	GumboVector* children = &node->v.element.children;
	for (int i = 0; i < children->length; ++i) {
		if (find_tbody_food_dormi(static_cast<GumboNode*>(children->data[i]), n) == 1)
			break;
	}
	return 0;
}

int add_food_dormi(GumboNode* tbody) {
	GumboVector* tbody_child = &tbody->v.element.children;
	int tr = 0;
	for (int i = 0; i < tbody_child->length; i++) {
		GumboNode* tr = (GumboNode*)tbody_child->data[i];
		if (tr->type == GUMBO_NODE_ELEMENT && tr->v.element.tag == GUMBO_TAG_TR) {
			GumboVector* tr_child = &tr->v.element.children;
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
	}
	return 0;
}