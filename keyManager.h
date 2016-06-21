#pragma once
#include "singletonBase.h"

//눌러질 수 있는 키 전부 등록
#define KEYMAX 256

enum KEYSTATE
{
	KS_NONE, KS_DOWN, KS_STAY, KS_UP
};

class keyManager : public singletonBase<keyManager>
{
private:
	bool	_keyState[KEYMAX];
	bool	_prevKeyState[KEYMAX];

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	inline bool isOnceKeyDown(int key){ if (_keyState[key] && !_prevKeyState[key]) return true;	return false; }
	inline bool isStayKeyDown(int key){ if (_keyState[key]) return true; return false; }
	inline bool isOnceKeyUp(int key){ if (!_keyState[key] && _prevKeyState[key]) return true; return false; }

	inline int getKeyState(int key)
	{
		int iState;
		_keyState[key] ? (_prevKeyState[key] ? iState = KS_STAY : iState = KS_DOWN)
			: (_prevKeyState[key] ? iState = KS_UP : iState = KS_NONE);
		return iState;
	}

	inline bool isToggleKey(int key) { if (GetKeyState(key) & 0x0001) return true; return false; }

	keyManager();
	~keyManager();
};

