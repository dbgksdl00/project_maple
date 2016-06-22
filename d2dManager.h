#pragma once
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"WindowsCodecs.lib")
#include <wincodec.h>
#include <wincodecsdk.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <cassert>

#include "singletonBase.h"

#include <vector>
#include <map>

struct imageInfo
{
	ID2D1Bitmap* image;
	int offsetX;
	int offsetY;
};

#define IMAGE_NULL {NULL, NULL, NULL}

class d2dManager : public singletonBase<d2dManager>
{
public:
	typedef map<string, imageInfo> mapD2ImageList;
	typedef map<string, imageInfo>::iterator mapD2ImageIter;

private:
	mapD2ImageList _mImageList;	//맵으로 구현된 이미지 리스트


	ID2D1Factory*				g_ipD2DFactory;
	ID2D1DCRenderTarget*		g_ipDCRT;
	IWICImagingFactory*			g_ipWICFactory;


public:
	HRESULT init();
	void release();


	void begin(HDC getMemdc);
	void end();

	//이미지 추가
	imageInfo addImage(string strKey, LPCWSTR fileName, int x = 0, int y = 0);//일단 오프셋 개념은 냄겨두장 ㅇ3ㅇ


	////이미지 찾는 함수
	imageInfo findImage(string strKey);

	////이미지 지우는 함수
	BOOL deleteImage(string strKey);

	BOOL deleteAll(void);

	////렌더함수
	void render(string strKey, int destX, int destY, float opacity = 1.0);
	void render(string strKey, int destX, int destY, int width, int height, float opacity = 1.0f);
	void render(string strKey, int destX, int destY, float width, float height, float opacity = 1.0f);
	void frameRender(string strKey, int destX, int destY, int currentFrameX, int currentFrameY, int maxFrameX, int maxFrameY, float opacity = 1.0);

	//핵심
	void InitializeD2D();
	void InitializeRT();
	ID2D1Bitmap* CreateD2DBitmapFromFile(LPCWSTR pImageFullPath);

	d2dManager();
	~d2dManager();
};