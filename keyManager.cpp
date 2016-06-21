#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager(void)
{
}


keyManager::~keyManager(void)
{
}

HRESULT keyManager::init(void)
{
	memset(_keyState, false, sizeof(_keyState));
	memset(_prevKeyState, false, sizeof(_prevKeyState));

	return S_OK;
}

void keyManager::release(void)
{

}

void keyManager::update(void)
{
	memcpy(_prevKeyState, _keyState, sizeof(_prevKeyState));

	for (short i = 0; i < 256; ++i)
	{
		_keyState[i] = GetAsyncKeyState(i) & 0x8000;
	}
}