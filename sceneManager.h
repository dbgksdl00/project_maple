#pragma once
#include "singletonBase.h"
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<char*, gameNode*> mapSceneList;
	typedef map<char*, gameNode*>::iterator mapSceneIter;

	
private:
	static gameNode* _currentScene;	//���� ��
	static gameNode* _loadingScene;	//�ε� ��
	static gameNode* _readyScene;	//��ü ��� ��

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	sceneManager();
	~sceneManager();

	HRESULT init(void);
	void release(void);
	void update(float timeDelta);
	void render(void);

	//�� �߰�
	gameNode* addScene(char* sceneName, gameNode* scene);

	//�ε��� �߰�
	gameNode* addLoadingScene(char* loadingSceneName, gameNode* scene);

	//�� ü����
	HRESULT changeScene(char* sceneName);
	HRESULT changeScene(char* sceneName, char* loadingSceneName);

	//�ε� �����带 ���� �Լ�
	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

