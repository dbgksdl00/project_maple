#pragma once
#include "gameNode.h"
#include "gameScene.h"

class mainGame : public gameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void) {}
	virtual void update(float timeDelta);
	virtual void render(void);

	mainGame() {}
	~mainGame() {}
};