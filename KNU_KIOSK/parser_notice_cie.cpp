#include "stdafx.h"
#include "header.h"

int find_tbody_cie(GumboNode *);
int add_title_cie(GumboNode *);

int parser_notice_cie() {
	string html = curl_http_get(L"http://cie.kunsan.ac.kr/view/notices_data/6/listdata.do?searchtype=undefined&search=&&page=0");

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody_cie(parse->root);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int find_tbody_cie(GumboNode* node) {
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}
	else if (node->v.element.tag == GUMBO_TAG_TBODY) {
		add_title_cie(node);
		return 1;
	}

	GumboVector* children = &node->v.element.children;
	for (int i = 0; i < children->length; ++i) {
		if (find_tbody_cie(static_cast<GumboNode*>(children->data[i])) == 1)
			break;
	}
	return 0;
}

int add_title_cie(GumboNode* tbody) {
	GumboVector* tbody_child = &tbody->v.element.children;
	for (int i = 0; i < tbody_child->length; i++) {
		GumboNode* tr = (GumboNode*)tbody_child->data[i];
		if (tr->type == GUMBO_NODE_ELEMENT && tr->v.element.tag == GUMBO_TAG_TR) {
			GumboVector* tr_child = &tr->v.element.children;
			notice temp;
			int td_num = 0;
			temp.category = 7;
			for (int j = 0; j < tr_child->length; j++) {
				GumboNode* td = (GumboNode*)tr_child->data[j];
				if (td->type == GUMBO_NODE_ELEMENT && td->v.element.tag == GUMBO_TAG_TD) {
					GumboVector* td_child = &td->v.element.children;
					if (td_num == 1) { //타이틀
						for (int k = 0; k < td_child->length; k++) {
							GumboNode* a = (GumboNode*)td_child->data[k];
							if (a->type == GUMBO_NODE_ELEMENT && a->v.element.tag == GUMBO_TAG_A) {
								GumboVector* a_child = &a->v.element.children;
								GumboNode* a_text = (GumboNode*)a_child->data[0];
								temp.title = Hangul.get(EncodeCharToWchar(a_text->v.text.text));

								GumboAttribute* a_href = gumbo_get_attribute(&a->v.element.attributes, "href");
								if (a_href != NULL) {
									const char* str = a_href->value;
									temp.url = L"http://cie.kunsan.ac.kr/view/notices_data";
									temp.url += Hangul.get(EncodeCharToWchar(str + 22));
									for (int i = 0; i < 6; i++)
										temp.url[temp.url.size() - i - 1] = 0;
								}
							}
						}
					}
					else if (td_num == 2) { //첨부

					}
					else if (td_num == 3) { //등록자

					}
					else if (td_num == 4) { //등록일
						GumboNode* td_text = (GumboNode*)td_child->data[0];
						const char* str = td_text->v.text.text;
						int year, mon, day;
						sscanf(str, "%d.%d.%d", &year, &mon, &day);
						temp.date = year * 10000 + mon * 100 + day;
					}
					else if (td_num == 5) { //조회수
						GumboNode* td_text = (GumboNode*)td_child->data[0];
						temp.view = atoi(td_text->v.text.text);
					}
					td_num++;
				}
			}
			title.push_back(temp);
		}
	}
	return 0;
}