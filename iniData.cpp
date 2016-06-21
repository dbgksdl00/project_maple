#include "stdafx.h"
#include "iniData.h"
iniData::iniData()
{
}
iniData::~iniData()
{
}
//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ##
//==================================================================
HRESULT iniData::init(void)
{
	return S_OK;
}

void iniData::release(void)
{
}

//����Ÿ �߰��ϱ� (����, Ű, ��)
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

//���̺�(�����̸�) => �����̸��� �־ (�����̸�.ini) ���Ϸ� �ڵ� ����ȴ�
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

//���ڰ� �ε��ϱ�(�����̸�, ����, Ű�� ���� ���ڰ� �޾ƿ���)
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

//������ �ε��ϱ�(�����̸�, ����, Ű�� ���� ������ �޾ƿ���)
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
