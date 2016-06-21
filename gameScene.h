#pragma once
#include "gameNode.h"
#include "gameMap.h"

class gameScene : public gameNode
{
private:
	gameMap* _map;
public:
	HRESULT init();
	void release();
	void update(float timeDelta);
	void render();

	gameScene();
	~gameScene();
};

