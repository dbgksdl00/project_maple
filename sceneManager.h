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
	static gameNode* _currentScene;	//현재 씬
	static gameNode* _loadingScene;	//로딩 씬
	static gameNode* _readyScene;	//교체 대기 씬

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

	//씬 추가
	gameNode* addScene(char* sceneName, gameNode* scene);

	//로딩씬 추가
	gameNode* addLoadingScene(char* loadingSceneName, gameNode* scene);

	//씬 체인지
	HRESULT changeScene(char* sceneName);
	HRESULT changeScene(char* sceneName, char* loadingSceneName);

	//로딩 쓰레드를 위한 함수
	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

