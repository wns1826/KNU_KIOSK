#pragma once
class HANGUL
{
public:
	HANGUL();
	wstring set(wstring);
	wstring get(wstring);
	wstring del_space(wstring);
	~HANGUL();

private:
	vector<wstring> data;
};

