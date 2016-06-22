#pragma once

class tiles;

struct tagPlayer
{
	RECT rc;
	float rc_centerx;
	float rc_bottomy;
	float xspeed;
	float yspeed;
};

class player
{
private:
	tagPlayer _player;
	tiles* _tile;

public:
	HRESULT init();
	void release();
	void update(float timeDelta);
	void render();

	void playerMove();

	void setTileLink(tiles* tile){ _tile = tile; }
	
	player();
	~player();
};