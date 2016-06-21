//��������� ����ϰڽ��ϴ�

#include "stdafx.h"
#include "mainGame.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//���������� ����Ѵ�
HINSTANCE _hInstance;
HWND _hWnd;

POINT _ptMouse = { 0, 0 };

mainGame _mg;

//�Լ� ������Ÿ�� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;		//�ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
	WNDCLASS wndClass;	//�������� ������ �����ϱ� ���� ����ü

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��׶��� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;								//Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ������

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//Ǯ��ũ��
#ifdef FULLSCREEN
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 800;
	dm.dmPelsHeight = 600;
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//���� ȭ������ �ǵ��ư��� �ڵ�
	if(((ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)))
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//������ ���帶ũ �Ǽ�
	_hWnd = CreateWindow(
		WINNAME,						//������ Ŭ���� �̸�
		WINNAME,						//������ Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�
		WS_POPUPWINDOW | WS_MAXIMIZE,	//������ ��Ÿ��
		WINSTARTX,						//������ â ���� X��ǥ
		WINSTARTY,						//������ â ���� Y��ǥ
		GetSystemMetrics(SM_CXSCREEN),	//������ â ����ũ��
		GetSystemMetrics(SM_CYSCREEN),	//������ â ����ũ��
		NULL,							//�θ� ������ ����
		(HMENU)NULL,					//�޴��ڵ�
		hInstance,						//�ν��Ͻ� ������ ����
		NULL);

		setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
#else
	//������ ���帶ũ �Ǽ�
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ���� �̸�
		WINNAME,				//������ Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�
		WS_OVERLAPPEDWINDOW,	//������ ��Ÿ��
		WINSTARTX,				//������ â ���� X��ǥ
		WINSTARTY,				//������ â ���� Y��ǥ
		WINSIZEX,				//������ â ����ũ��
		WINSIZEY,				//������ â ����ũ��
		NULL,					//�θ� ������ ����
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ������ ����
		NULL);

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

#endif


	//������ â�� ����ش�
	ShowWindow(_hWnd, cmdShow);

	/* ���ӿ� �������� �϶��Ҷ����� ������ �� ��
	
	*/

	if (FAILED(_mg.init()))
	{
		//���ΰ����� �ʱ�ȭ �����ϸ� �ٷ� �����Ŵ

		return 0;
	}
	bool _isHardware;//���� �ý��� ��������
	__int64 _periodFrequency;

	float _timeScale = 0.001f;
	__int64 _curTime;
	__int64 _lastTime;

	const float dt = 1.0f/ 60.0f;//���� ������(1�� / 60FPS / timeScale)
	float _mTime = 0.0f;//���� �ִ� �ð�
	float _gameTime = 0.0f;
#ifdef _DEBUG
	int _FPS = 0;
	float _FPSTime = 0.0f;
#endif
	bool _update = false;
	PNGMANAGER->addImage("background", L"./image/background.bmp");

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))//��ȯ���� bool���� �Լ��� ����, ���� Ÿ�̸� ������ �Ǵ��� Ȯ���ϴ� �Լ��� ����.
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);//������ �ȴٸ�, ���� �ð��� �ҷ��´�.

		_timeScale = 1.0f / _periodFrequency;//�Ʒ��ʿ� �и������� ������ �ʸ� ������ ����ٴ°����� ����, _periodFrequency�� �ʴ� ȭ���� �󸶳� ���ŵɼ� �ִ����� �ҷ��µ� �ϴ�.
	}
	else
	{
		_isHardware = false;

		//�и� ������ ������ �ʸ� ������ ����
		_lastTime = timeGetTime();//�����ð��� �ҷ��´�.
		_timeScale = 0.001f;//ȭ�鰻�ű����� �ð�
	}
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			_isHardware ? QueryPerformanceCounter((LARGE_INTEGER*)&_curTime) : _curTime = timeGetTime();//���׿�����
			_mTime += (_curTime - _lastTime) * _timeScale;
			_lastTime = _curTime;

			while (_mTime >= dt)
			{
				_mg.update(dt);
				_mTime -= dt;
				_gameTime += dt;
				_update = true;
#ifdef _DEBUG
				_FPSTime += dt;
				_FPS++;
#endif
			}
			if (_update)
			{
				PNGMANAGER->begin(_mg.getHDC());
				InvalidateRect(_hWnd, NULL, FALSE);
				PNGMANAGER->render("background", 0, 0, WINSIZEX, WINSIZEY);
				_update = false;
				_mg.render();
				PNGMANAGER->end();
			}
#ifdef _DEBUG
			if (_FPSTime > 1.0f)
			{
				//cout << _FPS << endl;
				_FPS = 0;
				_FPSTime -= 1.0f;
			}
#endif
		}
	}
	
	//�޼��� ����
	/*
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//Ű���� �Է� �޽����� ó���Ѵ�
		DispatchMessage(&message);	//������ ������� �޽����� ������ �ش�
	}
	*/

	//�޽��� �� �� �� ����
	_mg.release();

	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}


void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//���۾� ������ ������ �۾� �������� ũ�⸸ �����ش�
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}