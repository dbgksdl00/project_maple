#pragma once

class player
{
private:
	
public:
	HRESULT init();
	void release();
	void update(float timeDelta);
	void render();

	player();
	~player();
};