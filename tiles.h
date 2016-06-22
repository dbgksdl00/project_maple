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

struct tagNormalTile//�����ͷ� �����Ͽ�, NULL���̸� �ڵ��н�
{
	tagNorTileState state;
	unsigned char bottom;//bottom���� ������ + ���翩��
	unsigned char frame;//������
};

struct tagLinkTile//�����ͷ� �����Ͽ�, NULL���̸� �ڵ� �н�
{
	tagLinkTileState state;
	unsigned char bottom;//bottom���� ������ + ���� ����
	unsigned char frame;
};

struct tagTilesStruct//Ÿ�ϵ��� ����
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
			cout << "ERROR : tile.size�� ������ϴ�" << endl;
#endif
			return;
		}
		tagNormalTile* temp = _tile[i].tile[y * _tile[i].sizex + x];
		if (!temp) return;//�� Ÿ���� ���
		if (temp->bottom)//bottom�� ���� �������
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
			cout << "ERROR : tile.size�� ������ϴ�" << endl;
#endif
			return;
		}
		tagLinkTile* temp = _tile[i].link[y * (_tile[i].sizex + 1) + x];
		if (!temp) return;//�� Ÿ���� ���
		if (temp->bottom)//bottom�� ���� �������
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
			cout << "ERROR : tile.size�� ������ϴ�" << endl;
#endif
			return;
		}
		tagNormalTile* temp = _tile[i].tile[y * _tile[i].sizex + x];
		if (!temp) return;//�� Ÿ���� ���
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