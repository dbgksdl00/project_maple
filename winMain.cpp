//헤더파일을 사용하겠습니다

#include "stdafx.h"
#include "mainGame.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//전역변수를 사용한다
HINSTANCE _hInstance;
HWND _hWnd;

POINT _ptMouse = { 0, 0 };

mainGame _mg;

//함수 프로토타입 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;		//운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	WNDCLASS wndClass;	//윈도우의 정보를 저장하기 위한 구조체

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 백그라운드 색상
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//윈도우 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//윈도우 아이콘
	wndClass.hInstance = hInstance;									//윈도우 인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = WINNAME;								//클래스 이름
	wndClass.lpszMenuName = NULL;									//메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스따일

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//풀스크린
#ifdef FULLSCREEN
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 800;
	dm.dmPelsHeight = 600;
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//원래 화면으로 되돌아가는 코드
	if(((ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)))
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//윈도우 랜드마크 건설
	_hWnd = CreateWindow(
		WINNAME,						//윈도우 클래스 이름
		WINNAME,						//윈도우 타이틀 바에 나타낼 문자열
		WS_POPUPWINDOW | WS_MAXIMIZE,	//윈도우 스타일
		WINSTARTX,						//윈도우 창 시작 X좌표
		WINSTARTY,						//윈도우 창 시작 Y좌표
		GetSystemMetrics(SM_CXSCREEN),	//윈도우 창 가로크기
		GetSystemMetrics(SM_CYSCREEN),	//윈도우 창 세로크기
		NULL,							//부모 윈도우 유무
		(HMENU)NULL,					//메뉴핸들
		hInstance,						//인스턴스 윈도우 지정
		NULL);

		setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
#else
	//윈도우 랜드마크 건설
	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스 이름
		WINNAME,				//윈도우 타이틀 바에 나타낼 문자열
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일
		WINSTARTX,				//윈도우 창 시작 X좌표
		WINSTARTY,				//윈도우 창 시작 Y좌표
		WINSIZEX,				//윈도우 창 가로크기
		WINSIZEY,				//윈도우 창 세로크기
		NULL,					//부모 윈도우 유무
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 윈도우 지정
		NULL);

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

#endif


	//윈도우 창을 띄워준다
	ShowWindow(_hWnd, cmdShow);

	/* 게임용 봉인해제 하라할때까지 봉인해 둘 것
	
	*/

	if (FAILED(_mg.init()))
	{
		//메인게임이 초기화 실패하면 바로 종료시킴

		return 0;
	}
	bool _isHardware;//고성능 시스템 지원여부
	__int64 _periodFrequency;

	float _timeScale = 0.001f;
	__int64 _curTime;
	__int64 _lastTime;

	const float dt = 1.0f/ 60.0f;//기준 프레임(1초 / 60FPS / timeScale)
	float _mTime = 0.0f;//남아 있는 시간
	float _gameTime = 0.0f;
#ifdef _DEBUG
	int _FPS = 0;
	float _FPSTime = 0.0f;
#endif
	bool _update = false;
	PNGMANAGER->addImage("background", L"./image/background.bmp");

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))//반환값이 bool값인 함수로 봐서, 고성능 타이머 지원이 되는지 확인하는 함수로 보임.
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);//지원이 된다면, 최종 시간을 불러온다.

		_timeScale = 1.0f / _periodFrequency;//아래쪽에 밀리세컨드 단위로 초를 강제로 맞춘다는것으로 보아, _periodFrequency는 초당 화면이 얼마나 갱신될수 있는지를 불러온듯 하다.
	}
	else
	{
		_isHardware = false;

		//밀리 세컨드 단위로 초를 강제로 맞춤
		_lastTime = timeGetTime();//최종시간을 불러온다.
		_timeScale = 0.001f;//화면갱신까지의 시간
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
			_isHardware ? QueryPerformanceCounter((LARGE_INTEGER*)&_curTime) : _curTime = timeGetTime();//삼항연산자
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
	
	//메세지 루프
	/*
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//키보드 입력 메시지를 처리한다
		DispatchMessage(&message);	//실제로 윈도우로 메시지를 전달해 준다
	}
	*/

	//메시지 다 돈 후 해제
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

	//비작업 영역을 제외한 작업 영역안의 크기만 맞춰준다
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}