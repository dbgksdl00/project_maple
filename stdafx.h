// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include <vector>

using namespace std;

#include "utils.h"
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "d2dManager.h"
#include "txtData.h"

using namespace frameWork;
//========================================
//  ## 디파인문 선언 ##
//========================================

#define WINNAME (LPTSTR)(TEXT("Project_maple"))

//#define FULLSCREEN

#ifdef FULLSCREEN
	#define WINSTARTX 0
	#define WINSTARTY 0
	#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
	#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)
#else
	#define WINSTARTX 100
	#define WINSTARTY 25
	#define WINSIZEX 700
	#define WINSIZEY 600
#endif
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//========================================
// ## 매크로 함수 ##
//========================================

#define SAFE_DELETE(p)			{if(p) { delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) { delete[](p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->Release(); (p) = NULL;}}

inline void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[])
{
	int nLen = (int)strlen(pstrSrc) + 1;
	mbstowcs(pwstrDest, pstrSrc, nLen);
}

// LPCWSTR to char
inline void WCharToChar(const wchar_t* pwstrSrc, char pstrDest[])
{
	int nLen = (int)wcslen(pwstrSrc);
	wcstombs(pstrDest, pwstrSrc, nLen + 1);
}

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define PNGMANAGER d2dManager::getSingleton()
#define TXTDATA txtData::getSingleton()


//========================================
// ## 전역 변수 선언 ##
//========================================

extern POINT _ptMouse;
extern HINSTANCE _hInstance;
extern HWND _hWnd;
