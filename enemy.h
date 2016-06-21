#pragma once

class enemy
{
private:

public:
	HRESULT init();
	void release();
	void update(float timeDelta);
	void render();

	enemy();
	~enemy();
};