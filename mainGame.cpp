#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

////////////////////������ �Ҹ��� �����ʴ´� //////////////


//�ʱ�ȭ �ϴ� �Լ�
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->init();

	SCENEMANAGER->addScene("gameScene", new gameScene);

	SCENEMANAGER->changeScene("gameScene");

	return S_OK;
}


//�޸� ���� ���ִ� �Լ�
void mainGame::release(void)
{
	
}


//�������ִ� �Լ�
void mainGame::update(float timeDelta)
{
	gameNode::update(timeDelta);
	KEYMANAGER->update();

	SCENEMANAGER->update(timeDelta);
}


//�׷��ִ� �Լ�
void mainGame::render(void)
{
	SCENEMANAGER->render();
}

