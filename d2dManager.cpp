#include "stdafx.h"
#include "d2dManager.h"

d2dManager::d2dManager()
{
}

d2dManager::~d2dManager()
{
}

HRESULT d2dManager::init()
{
	//다이렉트 2d 이닛
	InitializeD2D();

	//렌더타겟 이닛
	InitializeRT();
	return S_OK;
}

void d2dManager::release()
{
	//deleteAll();
}

void d2dManager::begin(HDC getMemdc)
{
	g_ipDCRT->BindDC(getMemdc, &RectMake(0, 0, WINSIZEX, WINSIZEY));
	g_ipDCRT->BeginDraw();
}
void d2dManager::end()
{
	g_ipDCRT->EndDraw();
}

//이미지

imageInfo d2dManager::addImage(string strKey, LPCWSTR fileName, int x, int y)
{
	imageInfo temp = findImage(strKey);
	//동일한 이미지 있는지 찾는다
	//ID2D1Bitmap* img = findImage(strKey);

	//키값과 같은 이미지가 있다면 추가하지 않고 그 이미지를 리턴
	if (temp.image) return temp;

	//이미지 생성
	temp.image = CreateD2DBitmapFromFile(fileName);

	if (FAILED(CreateD2DBitmapFromFile(fileName)))
	{
		SAFE_DELETE(temp.image);

		return IMAGE_NULL;
	}
	temp.offsetX = x;
	temp.offsetY = y;

	_mImageList.insert(make_pair(strKey, temp));

	return temp;
}


//이미지 찾는 함수
imageInfo d2dManager::findImage(string strKey)
{
	//해당키가 있는지 여부를 검사한다
	mapD2ImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}

	return IMAGE_NULL;
}

//이미지 지우는 함수
BOOL d2dManager::deleteImage(string strKey)
{
	//해당 키값이 존재하는지 검사
	mapD2ImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		//key->second->release();
		SAFE_DELETE(key->second.image);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

BOOL d2dManager::deleteAll(void)
{
	mapD2ImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second.image != NULL)
		{
			SAFE_DELETE(iter->second.image);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}

	}

	_mImageList.clear();

	return TRUE;
}

void d2dManager::render(string strKey, int destX, int destY, float opacity)
{
	imageInfo img = findImage(strKey);
	if (img.image){
		::D2D1_RECT_F dxArea1 = ::D2D1::Rect(destX + img.offsetX, destY + img.offsetY, int(destX + img.offsetX + img.image->GetSize().width), int(destY + img.offsetY + img.image->GetSize().height));
		g_ipDCRT->DrawBitmap(img.image, dxArea1, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, (const D2D1_RECT_F*)0);
	}
}

void d2dManager::render(string strKey, int destX, int destY, int width, int height, float opacity)
{
	imageInfo img = findImage(strKey);
	if (img.image){
		::D2D1_RECT_F dxArea1 = ::D2D1::Rect(destX + img.offsetX, destY + img.offsetY, int(destX + width + img.offsetX), int(destY + height + img.offsetY));
		g_ipDCRT->DrawBitmap(img.image, dxArea1, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, (const D2D1_RECT_F*)0);
	}
}

void d2dManager::render(string strKey, int destX, int destY, float width, float height, float opacity)
{
	imageInfo img = findImage(strKey);
	if (img.image){
		::D2D1_RECT_F dxArea1 = ::D2D1::Rect(destX + img.offsetX, destY + img.offsetY, int(destX + img.offsetX + img.image->GetSize().width * width), int(destY + img.offsetY + img.image->GetSize().height * height));
		g_ipDCRT->DrawBitmap(img.image, dxArea1, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, (const D2D1_RECT_F*)0);
	}
}

void d2dManager::frameRender(string strKey, int destX, int destY, int currentFrameX, int currentFrameY, int maxFrameX, int maxFrameY, float opacity)
{
	imageInfo img = findImage(strKey);
	if (img.image){
		D2D1_RECT_F dxArea1 = D2D1::Rect(destX + img.offsetX, destY + img.offsetY, int(destX + img.offsetX + img.image->GetSize().width/maxFrameX), int(destY + img.offsetY + img.image->GetSize().height/maxFrameY));
		D2D1_RECT_F dxSour = D2D1::Rect(currentFrameX*img.image->GetSize().width / maxFrameX, currentFrameY*img.image->GetSize().height / maxFrameY, (currentFrameX + 1)*img.image->GetSize().width / maxFrameX, (currentFrameY + 1)*img.image->GetSize().height / maxFrameY);
		g_ipDCRT->DrawBitmap(img.image, dxArea1, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxSour);
	}
}


//코어 함수
void d2dManager::InitializeD2D(void)
{

	HRESULT hr = E_FAIL;

	//-----------------------------------------------------------------------
	//	D2D Factory 를 생성한다.
	//-----------------------------------------------------------------------
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&g_ipD2DFactory);
	assert(hr == S_OK);

	//-----------------------------------------------------------------------
	//	Windows Imaging Component Factory 를 생성한다.
	//-----------------------------------------------------------------------
	hr = ::CoCreateInstance(CLSID_WICImagingFactory,
		NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&g_ipWICFactory));
	assert(hr == S_OK);
}

void d2dManager::InitializeRT()
{

	//assert(::g_ipDCRT == nullptr);

	HRESULT hr = E_FAIL;
	RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);


	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(
		DXGI_FORMAT_B8G8R8A8_UNORM,
		D2D1_ALPHA_MODE_IGNORE),
		0,
		0,
		D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE,
		D2D1_FEATURE_LEVEL_DEFAULT
		);

	//hr = m_pD2DFactory->CreateDCRenderTarget(&props, &m_pDCRT);
	hr = g_ipD2DFactory->CreateDCRenderTarget(&props, &g_ipDCRT);
	assert(hr == S_OK);
}//여기까지도

ID2D1Bitmap* d2dManager::CreateD2DBitmapFromFile(LPCWSTR pImageFullPath)//이놈이 문제네
{
	assert(pImageFullPath != nullptr);
	assert(g_ipWICFactory != nullptr);

	HRESULT hr = E_FAIL;

	//----------------------------------------------------------------
	//	디코더를 생성한다.
	//----------------------------------------------------------------
	IWICBitmapDecoder* ipDecoderPtr = nullptr;
	hr = g_ipWICFactory->CreateDecoderFromFilename(pImageFullPath, nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&ipDecoderPtr);
	assert(hr == S_OK);

	//----------------------------------------------------------------
	//	디코더에서 프레임을 얻는다.
	//----------------------------------------------------------------
	IWICBitmapFrameDecode* ipFramePtr = nullptr;
	hr = ipDecoderPtr->GetFrame(0, &ipFramePtr);
	assert(hr == S_OK);

	//----------------------------------------------------------------
	//	프레임을 기반으로 해서 포맷 컨버터를 만든다.
	//----------------------------------------------------------------
	//SAFE_DELETE:(g_ipConvertedSrcBmp);
	IWICFormatConverter*		g_ipConvertedSrcBmp;
	hr = g_ipWICFactory->CreateFormatConverter(&g_ipConvertedSrcBmp);
	assert(hr == S_OK);


	hr = g_ipConvertedSrcBmp->Initialize(ipFramePtr,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom);
	assert(hr == S_OK);

	//----------------------------------------------------------------
	//	컨버트된 데이터를 기반으로 해서 실제 비트맵을 만든다.
	//----------------------------------------------------------------
	ID2D1Bitmap* g_ipD2DBitmap;
	//SAFE_DELETE(g_ipD2DBitmap);


	hr = g_ipDCRT->CreateBitmapFromWicBitmap(g_ipConvertedSrcBmp,
		nullptr,
		&g_ipD2DBitmap);
	assert(hr == S_OK);

	//SAFE_DELETE(ipDecoderPtr);
	//SAFE_DELETE(ipFramePtr);

	return g_ipD2DBitmap;
}