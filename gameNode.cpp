#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

//�ʱ�ȭ ���ִ� �Լ�
HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);

		KEYMANAGER->init();
		SOUNDMANAGER->init();
		PNGMANAGER->init();
		TXTDATA->init();
	}

	return S_OK;
}

//�޸� ���� ���ִ� �Լ�
void gameNode::release(void)
{

	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		PNGMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
	
}

//���� ��� �Լ�
void gameNode::update(float timeDelta)
{

}


//�׷��ִ� �Լ�
void gameNode::render(void)
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	//HDC hdc;


	switch (iMessage)
	{
		case WM_PAINT:
		{
			//hdc = BeginPaint(hWnd, &ps);

			//this->render();

			//EndPaint(hWnd, &ps);
		}
		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
			
		break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
		break;
		case WM_GETMINMAXINFO://ȭ��ũ�⸦ �̴�� �������ش�.
			((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WINSIZEX;
			((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WINSIZEY;
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = WINSIZEX;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = WINSIZEY;
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;

	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}