#pragma once
class HANGUL
{
public:
	HANGUL();
	wstring set(wstring);
	wstring get(wstring);
	~HANGUL();

private:
	vector<wstring> data;
};

