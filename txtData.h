#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

#define LINE_FAIL -1

struct tagNote
{
	int _line;
	float _time;
	float _end;
};

class txtData : public singletonBase<txtData>
{
public:
	HRESULT init();
	void release();

	//세이브
#ifdef _DEBUG
	void txtSave(LPCSTR saveFileName, vector<string> vStr);
	vector<string> txtLoad(LPCSTR loadFileName);
#else
	void txtSave(LPCWSTR saveFileName, vector<string> vStr);
	vector<string> txtLoad(LPCWSTR loadFileName);
#endif
	char* vectorArrayCombine(vector<string> vArray);

	//로드
	//vector<vector<string>>txtLoad(const char* loadFileName);//txt를 Load해옴
	vector<string> charArraySeparationComma(char charArray[]);//문자열을 쉼표 단위로 띄어논다.
	vector<string> charArraySeparationEnter(char charArray[]);//문자열을 엔터 단위로 띄어논다.
	tagNote findNoteInfo(char charArray[]);//한줄에서 노트의 정보를 받아온다.

	txtData();
	~txtData();
};