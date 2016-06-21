#pragma once
#include "singletonBase.h"
//==================================================================
//		## txtData ## (�ؽ�Ʈ����Ÿ)
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

	//����Ÿ �߰��ϱ� (����, Ű, ��)
	void addData(char* section, char* key, char* value);
	//���̺�(�����̸�) => �����̸��� �־ (�����̸�.ini) ���Ϸ� �ڵ� ����ȴ�
	void iniSave(char* fileName);

	//���ڰ� �ε��ϱ�(�����̸�, ����, Ű�� ���� ���ڰ� �޾ƿ���)
	char* loadDataString(char* fileName, char* section, char* key);
	//������ �ε��ϱ�(�����̸�, ����, Ű�� ���� ������ �޾ƿ���)
	int loadDataInteger(char* fileName, char* section, char* key);


	iniData();
	~iniData();
};

