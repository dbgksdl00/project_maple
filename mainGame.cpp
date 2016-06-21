#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

////////////////////생성자 소멸자 쓰지않는다 //////////////


//초기화 하는 함수
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->init();

	SCENEMANAGER->addScene("gameScene", new gameScene);

	SCENEMANAGER->changeScene("gameScene");

	return S_OK;
}


//메모리 해제 해주는 함수
void mainGame::release(void)
{
	
}


//연산해주는 함수
void mainGame::update(float timeDelta)
{
	gameNode::update(timeDelta);
	KEYMANAGER->update();

	SCENEMANAGER->update(timeDelta);
}


//그려주는 함수
void mainGame::render(void)
{
	SCENEMANAGER->render();
}

