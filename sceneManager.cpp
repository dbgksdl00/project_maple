#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//로딩 쓰레드를 위한 함수
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체될 init함수를 실행
	sceneManager::_readyScene->init();

	//현재 씬을 교체될 씬으로 바꿔줌
	sceneManager::_currentScene = sceneManager::_readyScene;

	//로딩씬을 해제 한다
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}


HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;


	return S_OK;
}
void sceneManager::release(void)
{
	//맵 전체를 돌면서 지워준다(씬들을)
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		//지워지면 반복자를 증가시키지 않는다
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else
		{
			++miSceneList;
		}
	}

	_mSceneList.clear();
}

void sceneManager::update(float timeDelta)
{
	if (_currentScene) _currentScene->update(timeDelta);
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

//씬 추가
gameNode* sceneManager::addScene(char* sceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//로딩씬 추가
gameNode* sceneManager::addLoadingScene(char* loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

//씬 체인지
HRESULT sceneManager::changeScene(char* sceneName)
{
	//바꾸려하는 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	//바꾸지 못하면 false
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸면 오케이
	if (find->second == _currentScene) return S_OK;

	//변경되는 씬을 초기화
	if (SUCCEEDED(find->second->init()))
	{
		//기존의 씬이 있으면 그 씬을 해제해줌
		if (_currentScene) _currentScene->release();
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(char* sceneName, char* loadingSceneName)
{
	//바꾸려하는 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	//바꾸지 못하면 false
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸면 오케이
	if (find->second == _currentScene) return S_OK;

	//바꾸려하는 씬을 찾는다
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);
	
	//변경되는 씬을 초기화
	if (SUCCEEDED(find->second->init()))
	{
		//기존의 씬이 있으면 그 씬을 해제해줌
		if (_currentScene) _currentScene->release();
		
		//바뀌기 전 로딩씬 보여줌
		_loadingScene = findLoading->second;

		//로딩 끝난 후 변경 될 씬 셋팅
		_readyScene = find->second;

		
		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadThreadID));
	}

	return E_FAIL;
}

