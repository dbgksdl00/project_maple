#include "stdafx.h"
#include "iniData.h"
iniData::iniData()
{
}
iniData::~iniData()
{
}
//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ##
//==================================================================
HRESULT iniData::init(void)
{
	return S_OK;
}

void iniData::release(void)
{
}

//데이타 추가하기 (섹션, 키, 값)
void iniData::addData(char* section, char* key, char* value)
{
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);
}

//세이브(파일이름) => 파일이름만 넣어도 (파일이름.ini) 파일로 자동 저장된다
void iniData::iniSave(char* fileName)
{
	char str[256];
	char dir[254];
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].section, vData[0].key, vData[0].value, str);
		vData.clear();
	}
	_vIniData.clear();
}

//문자값 로드하기(파일이름, 섹션, 키에 따른 문자값 받아오기)
char* iniData::loadDataString(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[254];
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[64] = { NULL };
	GetPrivateProfileString(section, key, "", data, 64, str);

	return data;
}

//정수값 로드하기(파일이름, 섹션, 키에 따른 정수값 받아오기)
int iniData::loadDataInteger(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[254];
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	return	GetPrivateProfileInt(section, key, 0, str);
}
