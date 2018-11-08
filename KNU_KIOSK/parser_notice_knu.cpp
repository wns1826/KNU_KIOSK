#include "stdafx.h"
#include "header.h"

extern HANGUL Hangul;

int add_title(GumboNode* tbody, const wchar_t* category) {
	GumboVector* tbody_child = &tbody->v.element.children;
	for (int i = 0; i < tbody_child->length; i++) {
		GumboNode* tr = (GumboNode*)tbody_child->data[i];
		if (tr->type == GUMBO_NODE_ELEMENT && tr->v.element.tag == GUMBO_TAG_TR) {
			GumboVector* tr_child = &tr->v.element.children;
			notice temp;
			int td_num = 0;
			temp.category = category;
			for (int j = 0; j < tr_child->length; j++) {
				GumboNode* td = (GumboNode*)tr_child->data[j];
				if (td->type == GUMBO_NODE_ELEMENT && td->v.element.tag == GUMBO_TAG_TD) {
					GumboVector* td_child = &td->v.element.children;
					if (td_num == 1) { //타이틀
						for (int k = 0; k < td_child->length; k++) {
							GumboNode* a = (GumboNode*)td_child->data[k];
							if (a->type == GUMBO_NODE_ELEMENT && a->v.element.tag == GUMBO_TAG_A) {
								GumboAttribute* a_title = gumbo_get_attribute(&a->v.element.attributes, "title");
								if (a_title != NULL) {
									const char* str = a_title->value;
									temp.title = Hangul.get(EncodeCharToWchar(str));
								}
							}
						}
					}
					else if (td_num == 2) { //작성자
						for (int k = 0; k < td_child->length; k++) {
							GumboNode* a = (GumboNode*)td_child->data[k];
							if (a->type == GUMBO_NODE_ELEMENT && a->v.element.tag == GUMBO_TAG_SPAN) {
								GumboAttribute* span_title = gumbo_get_attribute(&a->v.element.attributes, "title");
								if (span_title != NULL) {
									const char* str = span_title->value;
									temp.name = Hangul.get(EncodeCharToWchar(str));
								}
							}
						}
					}
					else if (td_num == 3) { //작성일
						GumboNode* td_text = (GumboNode*)td_child->data[0];
						const char* str = td_text->v.text.text;
						int year, mon, day;
						sscanf(str, "%d-%d-%d", &year, &mon, &day);
						temp.date = year * 10000 + mon * 100 + day;
					}
					else if (td_num == 4) { //조회수
						GumboNode* td_text = (GumboNode*)td_child->data[0];
						temp.view = atoi(td_text->v.text.text);
					}
					else if (td_num == 5) { //첨부파일 링크
						for (int k = 0; k < td_child->length; k++) {
							GumboNode* a = (GumboNode*)td_child->data[k];
							if (a->type == GUMBO_NODE_ELEMENT && a->v.element.tag == GUMBO_TAG_A) {
								GumboAttribute* a_href = gumbo_get_attribute(&a->v.element.attributes, "href");
								if (a_href != NULL) {
									const char* str = a_href->value;
									temp.url = Hangul.get(EncodeCharToWchar(str));
								}
							}
						}
					}
					td_num++;
				}
			}
			title.push_back(temp);
		}
	}
	return 0;
}

int find_tbody(GumboNode* node, const wchar_t* category) {
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}
	else if (node->v.element.tag == GUMBO_TAG_TBODY) {
		add_title(node, category);
		return 1;
	}

	GumboVector* children = &node->v.element.children;
	for (int i = 0; i < children->length; ++i) {
		if (find_tbody(static_cast<GumboNode*>(children->data[i]), category) == 1)
			break;
	}
	return 0;
}


int parser_notice_knu_1() {
	string html;
	curl_http_get(L"http://www.kunsan.ac.kr/board/list.kunsan?boardId=BBS_0000008&menuCd=DOM_000000105001001000&contentsSid=211&startPage=1&orderBy=REGISTER_DATE+DESC&listCel=1&sso=ok&categoryCode1=&searchType=DATA_TITLE&keyword=&listRow=100", html);

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody(parse->root, L"공지");
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int parser_notice_knu_2() {
	string html;
	curl_http_get(L"http://www.kunsan.ac.kr/board/list.kunsan?boardId=BBS_0000009&menuCd=DOM_000000105001002000&contentsSid=212&startPage=1&orderBy=&listCel=1&sso=ok&searchType=DATA_TITLE&keyword=&listRow=100", html);

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody(parse->root, L"학사/장학");
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int parser_notice_knu_3() {
	string html;
	curl_http_get(L"http://www.kunsan.ac.kr/board/list.kunsan?boardId=BBS_0000010&menuCd=DOM_000000105001003000&contentsSid=213&startPage=1&orderBy=&listCel=1&sso=ok&searchType=DATA_TITLE&keyword=&listRow=100", html);

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody(parse->root, L"모집/안내/공고");
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int parser_notice_knu_4() {
	string html;
	curl_http_get(L"http://www.kunsan.ac.kr/board/list.kunsan?boardId=BBS_0000011&menuCd=DOM_000000105001004000&contentsSid=214&startPage=1&orderBy=&listCel=1&sso=ok&searchType=DATA_TITLE&keyword=&listRow=100", html);

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody(parse->root, L"행사/뉴스");
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int parser_notice_knu_5() {
	string html;
	curl_http_get(L"http://www.kunsan.ac.kr/board/list.kunsan?boardId=BBS_0000012&menuCd=DOM_000000105001005000&contentsSid=215&startPage=1&orderBy=&listCel=1&sso=ok&searchType=DATA_TITLE&keyword=&listRow=100", html);

	GumboOutput* parse = gumbo_parse(html.c_str());
	find_tbody(parse->root, L"교육/연구");
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}