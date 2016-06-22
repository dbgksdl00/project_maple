#include "stdafx.h"
#include "player.h"
#include "tiles.h"

player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	PNGMANAGER->addImage("player_temp", L"./image/player/player.png");

	_player.rc_centerx = WINSIZEX / 2;
	_player.rc_bottomy = WINSIZEY / 2 - 60;

	_player.rc = RectMakeBottom(_player.rc_centerx, _player.rc_bottomy, 40, 100);

	return S_OK;
}

void player::release()
{

}

void player::update(float timeDelta)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player.rc_centerx -= 160 * timeDelta;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.rc_centerx += 160 * timeDelta;
	}

	_player.rc = RectMakeBottom(_player.rc_centerx, _player.rc_bottomy, 40, 100);
}

void player::render()
{
	PNGMANAGER->render("player_temp", _player.rc.left, _player.rc.top);
}
