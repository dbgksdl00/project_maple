#pragma once

class player;

enum tagNorTileState : char
{
	NTST_NULL,
	NTST_STAND,
	NTST_LU, NTST_LD, NTST_RU, NTST_RD
};

enum tagLinkTileState : char
{
	LTST_TILEEND,
	LTST_LEFT,
	LTST_RIGHT
};

struct tagNormalTile//포인터로 선언하여, NULL값이면 자동패스
{
	tagNorTileState state;
	unsigned char bottom;//bottom값의 프레임 + 존재여부
	unsigned char frame;//프레임
};

struct tagLinkTile//포인터로 선언하여, NULL값이면 자동 패스
{
	tagLinkTileState state;
	unsigned char bottom;//bottom값의 프레임 + 존재 여부
	unsigned char frame;
};

struct tagTilesStruct//타일들의 집합
{
	tagNormalTile** tile;
	tagLinkTile** link;
	unsigned char sizex;
	unsigned char sizey;
	unsigned short tileNumber;
	int x;
	int y;
};

class tiles
{
private:
	vector<tagTilesStruct> _tile;
	player* _player;

public:
	HRESULT init();
	void release();
	void update(float timeDelta);
	void render(int arrNum);

	int getTileSize(){ return _tile.size(); }
	tagTilesStruct getTiles(int arrNum){ return _tile[arrNum]; }

	void setPlayerLink(player* player){ _player = player; }

	tiles();
	~tiles();
private:
	void tileSet();
	inline tagNormalTile* setNormalTile(tagNorTileState st, unsigned char bottom, unsigned char frame)
	{
		tagNormalTile* temp = new tagNormalTile;
		temp->bottom = bottom;
		temp->frame = frame;
		temp->state = st;

		return temp;
	}
	inline tagLinkTile* setLinkTile(tagLinkTileState st, unsigned char bottom, unsigned char frame)
	{
		tagLinkTile* temp = new tagLinkTile;
		temp->bottom = bottom;
		temp->state = st;
		temp->frame = frame;

		return temp;
	}

	inline void norTileBottomRender(int i, int y, int x)
	{
		if (i >= _tile.size())
		{
#ifdef _DEBUG
			system("cls");
			cout << "ERROR : tile.size를 벗어났습니다" << endl;
#endif
			return;
		}
		tagNormalTile* temp = _tile[i].tile[y * _tile[i].sizex + x];
		if (!temp) return;//빈 타일일 경우
		if (temp->bottom)//bottom에 값이 있을경우
		{
			char str[128];
			sprintf(str, "tile_woodMarble_EnHD_%d", temp->bottom - 1);
			PNGMANAGER->render(str, _tile[i].x + 90 * x, _tile[i].y + 60 * y);
		}
	}
	inline void linkTileBottomRender(int i, int y, int x)
	{
		if (i >= _tile.size())
		{
#ifdef _DEBUG
			system("cls");
			cout << "ERROR : tile.size를 벗어났습니다" << endl;
#endif
			return;
		}
		tagLinkTile* temp = _tile[i].link[y * (_tile[i].sizex + 1) + x];
		if (!temp) return;//빈 타일일 경우
		if (temp->bottom)//bottom에 값이 있을경우
		{
			char str[128];
			sprintf(str, "tile_woodMarble_EdD_%d", temp->bottom - 1);
			PNGMANAGER->render(str, _tile[i].x + 90 * x, _tile[i].y + 60 * y);
		}
	}

	inline void norTileRender(int i, int y, int x)
	{
		if (i >= _tile.size())
		{
#ifdef _DEBUG
			system("cls");
			cout << "ERROR : tile.size를 벗어났습니다" << endl;
#endif
			return;
		}
		tagNormalTile* temp = _tile[i].tile[y * _tile[i].sizex + x];
		if (!temp) return;//빈 타일일 경우
		char str[128];
		switch (temp->state)
		{
		case NTST_NULL:
			sprintf(str, "tile_woodMarble_Bse_%d", temp->frame);
			break;
		case NTST_STAND:
			sprintf(str, "tile_woodMarble_EnHU_%d", temp->frame);
			break;
		case NTST_LU:
			sprintf(str, "tile_woodMarble_SILU");
			break;
		case NTST_LD:
			sprintf(str, "tile_woodMarble_SILD");
			break;
		case NTST_RU:
			sprintf(str, "tile_woodMarble_SIRU");
			break;
		case NTST_RD:
			sprintf(str, "tile_woodMarble_SIRD");
			break;
		}
		PNGMANAGER->render(str, _tile[i].x + 90 * x, _tile[i].y + 60 * y);
	}
	inline void linkTileEndRender(int i, int y, int x)
	{
		tagLinkTile* temp = _tile[i].link[y * (_tile[i].sizex + 1) + x];
		char str[128];
		sprintf(str, "tile_woodMarble_EdU_%d", temp->frame);
		PNGMANAGER->render(str, _tile[i].x + 90 * x, _tile[i].y + 60 * y);
	}
	inline void linkTileRender(int i, int y, int x)
	{
		tagLinkTile* temp = _tile[i].link[y * (_tile[i].sizex + 1) + x];
		char str[128];
		temp->state == LTST_LEFT ? sprintf(str, "tile_woodMarble_EnVL_%d", temp->frame) : sprintf(str, "tile_woodMarble_EnVR_%d", temp->frame);
		PNGMANAGER->render(str, _tile[i].x + 90 * x, _tile[i].y + 60 * y);
	}
};