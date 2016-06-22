#pragma once

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
			
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);

	virtual void release(void);
	virtual void update(float timeDelta) {}
	virtual void render(void) {}

	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


	gameNode();
	virtual ~gameNode();
};

