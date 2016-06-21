#pragma once
#include "player.h"
#include "enemy.h"
#include "tiles.h"

class gameMap
{
private:
	enemy* _enemy;
	player* _player;
	tiles* _tiles;
public:
	HRESULT init();
	void release();
	void update(float timeDelta);
	void render();

	gameMap();
	~gameMap();
};