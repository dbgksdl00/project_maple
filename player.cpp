#include "stdafx.h"
#include "player.h"

player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	PNGMANAGER->addImage("player_temp", L"./image/player/player.png");

	return S_OK;
}

void player::release()
{

}

void player::update(float timeDelta)
{
	
}

void player::render()
{
	//PNGMANAGER->render("player_temp", _player->rc.left, _player->rc.top);
}
