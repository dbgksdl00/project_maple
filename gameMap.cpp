#include "stdafx.h"
#include "gameMap.h"

gameMap::gameMap()
{
}


gameMap::~gameMap()
{
}

HRESULT gameMap::init()
{
	_player = new player;
	_enemy = new enemy;
	_tiles = new tiles;

	_player->init();
	_enemy->init();
	_tiles->init();

	return S_OK;
}

void gameMap::release()
{
	_player->release();
	_enemy->release();
	_tiles->release();
}

void gameMap::update(float timeDelta)
{
	_player->update(timeDelta);
	_enemy->update(timeDelta);
	_tiles->update(timeDelta);
}

void gameMap::render()
{
	_player->render();
	_enemy->render();
	for (int i = 0; i < _tiles->getTileSize(); i++)
	{
		_tiles->render(i);
	}
}
