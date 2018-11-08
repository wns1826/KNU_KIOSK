#include "stdafx.h"
#include "header.h"

HANGUL::HANGUL()
{
}

wstring HANGUL::set(wstring w_str) {
	wstring word;
	wchar_t temp[1024];
	int index;
	for (int i = 0; i < w_str.length(); i++) {
		if (0x00A1 <= w_str[i] && w_str[i] <= 0x10FFFF) {
			if (word.length() == 0)
				index = i;
			word += w_str[i];
		}
		else if (word.length() != 0) {
			w_str.erase(index, word.length());
			wsprintf(temp, L"{@Kiosk_Hangul_%d}", data.size());
			w_str.insert(index, temp);
			data.push_back(word);
			word = L"";
		}	
	}
	return w_str;
}

wstring HANGUL::get(wstring w_str) {
	//return w_str;
	
	int index = 0;
	int num, num_len;
	while (true) {
		index = w_str.find(L"{@Kiosk_Hangul_", index);
		if (index == string::npos)
			break;

		num = num_len = 0;
		for (int i = index + 15;; i++) {
			if (L'0' <= w_str[i] && w_str[i] <= L'9') {
				num *= 10;
				num += w_str[i] - L'0';
				num_len++;
			}
			else if (w_str[i] == '}' && num_len != 0) {
				if (num < data.size()) {
					w_str.erase(index, 16 + num_len);
					w_str.insert(index, data[num]);
				}
				break;
			}
			else {
				index++;
				break;
			}
		}
	}
	return w_str;
}

HANGUL::~HANGUL()
{
}
