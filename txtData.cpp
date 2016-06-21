#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{

	return S_OK;
}


void txtData::release()
{

}
#ifdef _DEBUG
void txtData::txtSave(LPCSTR saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[128];
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

//로드

vector<string> txtData::txtLoad(LPCSTR loadFileName)
{
	HANDLE file;

	char str[65536];
	DWORD read;

	memset(str, 0, 65536);

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 65536, &read, NULL);
	CloseHandle(file);

	return charArraySeparationEnter(str);
}
#else
//세이브
void txtData::txtSave(LPCWSTR saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[128];
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

//로드

vector<string> txtData::txtLoad(LPCWSTR loadFileName)
{
	HANDLE file;

	char str[65536];
	DWORD read;

	memset(str, 0, 65536);

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 65536, &read, NULL);
	CloseHandle(file);

	return charArraySeparationEnter(str);
}
#endif//로드, 세이브

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];

	ZeroMemory(str, sizeof(str));

	for (int i = 0;i < vArray.size(); i++)
	{
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) strcat(str, ",");
	}

	return str;
}

vector<string> txtData::charArraySeparationEnter(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = "\r\n";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

vector<string> txtData::charArraySeparationComma(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);//token은 charArray를 separator로 분해
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

tagNote txtData::findNoteInfo(char charArray[])
{
	tagNote temp = { LINE_FAIL, 0.0f, 0.0f };
	vector<string> vStr = charArraySeparationComma(charArray);
	char str[64];
	if (vStr.size() < 6)
		return temp;
	temp._line = atoi(vStr[0].c_str()) / 128;
	temp._time = (float)atoi(vStr[2].c_str()) / 1000;
	sprintf(str, vStr[5].c_str());
	temp._end = (float)atoi(strtok(str, ":")) / 1000;
	if (temp._end < FLOAT_EPSILON)//long = 0;
		temp._end = temp._time;

	return temp;
}