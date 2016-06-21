#include "stdafx.h"
#include "gameScene.h"


gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	_map = new gameMap;

	_map->init();

	return S_OK;
}

void gameScene::release()
{
	_map->release();
}

void gameScene::update(float timeDelta)
{
	_map->update(timeDelta);
}

void gameScene::render()
{
	_map->render();
}
