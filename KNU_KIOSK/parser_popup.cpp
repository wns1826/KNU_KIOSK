#include "stdafx.h"
#include "header.h"

int find_popup_ul(GumboNode *);
int add_popup_image(GumboNode *);

int parser_popup() {
	string html = curl_http_get(L"http://www.kunsan.ac.kr");

	GumboOutput* parse = gumbo_parse(html.c_str());
	//ul (class: hp_slide) -> image
	find_popup_ul(parse->root);
	gumbo_destroy_output(&kGumboDefaultOptions, parse);

	return 0;
}

int find_popup_ul(GumboNode* node) {
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}
	else if (node->v.element.tag == GUMBO_TAG_UL) {
		GumboAttribute* ul_class = gumbo_get_attribute(&node->v.element.attributes, "class");
		if (ul_class != NULL) {
			const char* str = ul_class->value;
			if (strcmp(str, "hp_slide") == 0) {
				add_popup_image(node);
				return 1;
			}
		}
	}

	GumboVector* children = &node->v.element.children;
	for (int i = 0; i < children->length; ++i) {
		if (find_popup_ul(static_cast<GumboNode*>(children->data[i])) == 1)
			break;
	}
	return 0;
}

int add_popup_image(GumboNode* node) {
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}
	else if (node->v.element.tag == GUMBO_TAG_IMG) {
		GumboAttribute* img_src = gumbo_get_attribute(&node->v.element.attributes, "src");
		if (img_src != NULL) {
			const char* str = img_src->value;
			char url[1000], file[1000];
			char *path = getenv("TEMP");
			sprintf(url, "http://www.kunsan.ac.kr%s", str);
			sprintf(file, "%s\\%knu_kiosk_popup_%d.jpg", path, knu_popup.size());

			curl_http_get_download(url, file);
			knu_popup.push_back(EncodeCharToWchar(file));
		}
	}

	GumboVector* children = &node->v.element.children;
	for (int i = 0; i < children->length; ++i) {
		if (add_popup_image(static_cast<GumboNode*>(children->data[i])) == 1)
			break;
	}
	return 0;
}