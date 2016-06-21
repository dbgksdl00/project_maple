#pragma once
#include "singletonBase.h"
//==================================================================
//		## txtData ## (텍스트데이타)
//==================================================================

struct tagIniData
{
	const char* section;
	const char* key;
	const char* value;
};

class iniData : public singletonBase <iniData>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<tagIniData>::iterator arrIniDataIter;
	typedef vector<arrIniData> arrIniDatas;
	typedef vector<arrIniData>::iterator arrIniDatasIter;

private:
	arrIniDatas _vIniData;

public:
	HRESULT init(void);
	void release(void);

	//데이타 추가하기 (섹션, 키, 값)
	void addData(char* section, char* key, char* value);
	//세이브(파일이름) => 파일이름만 넣어도 (파일이름.ini) 파일로 자동 저장된다
	void iniSave(char* fileName);

	//문자값 로드하기(파일이름, 섹션, 키에 따른 문자값 받아오기)
	char* loadDataString(char* fileName, char* section, char* key);
	//정수값 로드하기(파일이름, 섹션, 키에 따른 정수값 받아오기)
	int loadDataInteger(char* fileName, char* section, char* key);


	iniData();
	~iniData();
};

