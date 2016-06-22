#include "stdafx.h"
#include "tiles.h"
#include "player.h"

tiles::tiles()
{
}


tiles::~tiles()
{
}

HRESULT tiles::init()
{
	//BaseTile
	PNGMANAGER->addImage("tile_woodMarble_Bse_0", L"./image/tile/woodMarble/Bse-0.png");
	PNGMANAGER->addImage("tile_woodMarble_Bse_1", L"./image/tile/woodMarble/Bse-1.png");
	PNGMANAGER->addImage("tile_woodMarble_Bse_2", L"./image/tile/woodMarble/Bse-2.png");
	PNGMANAGER->addImage("tile_woodMarble_Bse_3", L"./image/tile/woodMarble/Bse-3.png");
	PNGMANAGER->addImage("tile_woodMarble_Bse_4", L"./image/tile/woodMarble/Bse-4.png");
	PNGMANAGER->addImage("tile_woodMarble_Bse_5", L"./image/tile/woodMarble/Bse-5.png");
	//TopTile
	PNGMANAGER->addImage("tile_woodMarble_EnHU_0", L"./image/tile/woodMarble/EnHU-0.png", 0, 60 - 33);
	PNGMANAGER->addImage("tile_woodMarble_EnHU_1", L"./image/tile/woodMarble/EnHU-1.png", 0, 60 - 33);
	PNGMANAGER->addImage("tile_woodMarble_EnHU_2", L"./image/tile/woodMarble/EnHU-2.png", 0, 60 - 34);
	PNGMANAGER->addImage("tile_woodMarble_EnHU_3", L"./image/tile/woodMarble/EnHU-3.png", 0, 60 - 33);
	//BottomTile
	PNGMANAGER->addImage("tile_woodMarble_EnHD_0", L"./image/tile/woodMarble/EnHD-0.png", 0, 60);
	PNGMANAGER->addImage("tile_woodMarble_EnHD_1", L"./image/tile/woodMarble/EnHD-1.png", 0, 60);
	PNGMANAGER->addImage("tile_woodMarble_EnHD_2", L"./image/tile/woodMarble/EnHD-2.png", 0, 60);
	PNGMANAGER->addImage("tile_woodMarble_EnHD_3", L"./image/tile/woodMarble/EnHD-3.png", 0, 60);
	//TopLinkTile
	PNGMANAGER->addImage("tile_woodMarble_EdU_0", L"./image/tile/woodMarble/EdU-0.png", -29, 60 - 32);
	PNGMANAGER->addImage("tile_woodMarble_EdU_1", L"./image/tile/woodMarble/EdU-1.png", -29, 60 - 34);
	PNGMANAGER->addImage("tile_woodMarble_EdU_2", L"./image/tile/woodMarble/EdU-2.png", -29, 60 - 34);
	PNGMANAGER->addImage("tile_woodMarble_EdU_3", L"./image/tile/woodMarble/EdU-3.png", -29, 60 - 33);
	//LeftLink
	PNGMANAGER->addImage("tile_woodMarble_EnVL_0", L"./image/tile/woodMarble/EnVL-0.png", -28);
	PNGMANAGER->addImage("tile_woodMarble_EnVL_1", L"./image/tile/woodMarble/EnVL-1.png", -31);
	//RightLink
	PNGMANAGER->addImage("tile_woodMarble_EnVR_0", L"./image/tile/woodMarble/EnVR-0.png");
	PNGMANAGER->addImage("tile_woodMarble_EnVR_1", L"./image/tile/woodMarble/EnVR-1.png");
	//BottomLinkTile
	PNGMANAGER->addImage("tile_woodMarble_EdD_0", L"./image/tile/woodMarble/EdD-0.png", -24, 60);
	PNGMANAGER->addImage("tile_woodMarble_EdD_1", L"./image/tile/woodMarble/EdD-1.png", -23, 60);
	PNGMANAGER->addImage("tile_woodMarble_EdD_2", L"./image/tile/woodMarble/EdD-2.png", -24, 60);
	PNGMANAGER->addImage("tile_woodMarble_EdD_3", L"./image/tile/woodMarble/EdD-3.png", -24, 60);

	PNGMANAGER->addImage("tile_woodMarble_SILU", L"./image/tile/woodMarble/SILU.png", 0, -30);
	PNGMANAGER->addImage("tile_woodMarble_SILD", L"./image/tile/woodMarble/SILD.png");
	PNGMANAGER->addImage("tile_woodMarble_SIRU", L"./image/tile/woodMarble/SIRU.png", 0, -30);
	PNGMANAGER->addImage("tile_woodMarble_SIRD", L"./image/tile/woodMarble/SIRD.png");

	tileSet();
	//tileSet();

	return S_OK;
}

void tiles::release()
{

}

void tiles::update(float timeDelta)
{

}

void tiles::render(int arrNum)
{
	for (int j = 0; j < _tile[arrNum].sizey; j++)
	{
		bool temp = false;
		if (!_tile[arrNum].link[j * (_tile[arrNum].sizex + 1)]);//NULL값인 경우 그냥 패스
		else//NULL이 아닌경우만
		{
			if (_tile[arrNum].link[j * (_tile[arrNum].sizex + 1)]->state == LTST_TILEEND)
				linkTileEndRender(arrNum, j, 0);
			else
				temp = true;
		}
		for (int k = 0; k < _tile[arrNum].sizex; k++)
		{
			if (!_tile[arrNum].link[j * (_tile[arrNum].sizex + 1) + k + 1])//다음 연결부가 없음
			{
				norTileBottomRender(arrNum, j, k);
				linkTileBottomRender(arrNum, j, k + 1);
				norTileRender(arrNum, j, k);//현재 타일랜더
				if (temp)
				{
					linkTileRender(arrNum, j, k);//현재 연결부 랜더
					temp = false;
				}
			}
			else
			{
				if (_tile[arrNum].link[j * (_tile[arrNum].sizex + 1) + k + 1]->state == LTST_TILEEND)//다음 연결부가 tileEnd
				{
					linkTileEndRender(arrNum, j, k + 1);
					norTileBottomRender(arrNum, j, k);
					linkTileBottomRender(arrNum, j, k + 1);
					norTileRender(arrNum, j, k);
					if (temp)
					{
						linkTileRender(arrNum, j, k);//현재 연결부 랜더
						temp = false;
					}
				}
				else
				{
					norTileBottomRender(arrNum, j, k);
					linkTileBottomRender(arrNum, j, k + 1);
					norTileRender(arrNum, j, k);
					if (temp)
					{
						linkTileRender(arrNum, j, k);//현재 연결부 랜더
						temp = false;
					}
					temp = true;//다음 연결부 세팅
				}
			}
		}
	}
}

void tiles::tileSet()
{
	tagTilesStruct temp;
	temp.sizex = 6;
	temp.sizey = 4;
	temp.link = (tagLinkTile**)malloc(sizeof(tagLinkTile*) * (temp.sizex + 1) * temp.sizey);
	temp.tile = (tagNormalTile**)malloc(sizeof(tagNormalTile*) * temp.sizex * temp.sizey);
	temp.tileNumber = 0;

	for (int i = 0; i < temp.sizey; i++)
	{
		for (int j = 0; j < temp.sizex; j++)
		{
			temp.link[i * (temp.sizex + 1) + j] = NULL;//1차원 배열로의 생성이다아아앗
			temp.tile[i * temp.sizex + j] = NULL;
		}
	}
	for (int i = 0; i < temp.sizey; i++)
	{
		temp.link[i * (temp.sizex + 1) + temp.sizex] = NULL;//위에서 못넣어준 마지막 줄까지 채워버렷
	}
	temp.x = 0;
	temp.y = 0;

	temp.link[(temp.sizex + 1) * 2 + 2] = setLinkTile(LTST_TILEEND, 4, 1);
	temp.tile[temp.sizex * 2 + 2] = setNormalTile(NTST_STAND, 1, 1);
	temp.link[(temp.sizex + 1) * 2 + 3] = setLinkTile(LTST_TILEEND, 4, 1);
	temp.link[(temp.sizex + 1) * 3 + 2] = setLinkTile(LTST_LEFT, 4, 1);
	temp.tile[temp.sizex * 3 + 2] = setNormalTile(NTST_NULL, 1, 1);
	temp.tile[temp.sizex * 3 + 3] = setNormalTile(NTST_RU, 1, 1);
	temp.tile[temp.sizex * 3 + 4] = setNormalTile(NTST_STAND, 1, 1);
	temp.link[(temp.sizex + 1) * 3 + 5] = setLinkTile(LTST_TILEEND, 4, 1);


	_tile.push_back(temp);
}