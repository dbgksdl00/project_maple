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

	//���̺�
#ifdef _DEBUG
	void txtSave(LPCSTR saveFileName, vector<string> vStr);
	vector<string> txtLoad(LPCSTR loadFileName);
#else
	void txtSave(LPCWSTR saveFileName, vector<string> vStr);
	vector<string> txtLoad(LPCWSTR loadFileName);
#endif
	char* vectorArrayCombine(vector<string> vArray);

	//�ε�
	//vector<vector<string>>txtLoad(const char* loadFileName);//txt�� Load�ؿ�
	vector<string> charArraySeparationComma(char charArray[]);//���ڿ��� ��ǥ ������ �����.
	vector<string> charArraySeparationEnter(char charArray[]);//���ڿ��� ���� ������ �����.
	tagNote findNoteInfo(char charArray[]);//���ٿ��� ��Ʈ�� ������ �޾ƿ´�.

	txtData();
	~txtData();
};