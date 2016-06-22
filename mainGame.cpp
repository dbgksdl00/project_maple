#include "stdafx.h"
#include "mainGame.h"

HRESULT mainGame::init(void)
{

	// sprite = new sprite;
	// sprite->init( ) ;
	// this->AddChild( sprite );
	gameNode::init(true);
	SCENEMANAGER->init();
	SCENEMANAGER->addScene("gameScene", new gameScene);
	SCENEMANAGER->changeScene("gameScene");
	return S_OK;
}

void mainGame::update(float timeDelta)
{
	gameNode::update(timeDelta);
	KEYMANAGER->update();

	SCENEMANAGER->update(timeDelta);
}

void mainGame::render(void)
{
	SCENEMANAGER->render();
}

