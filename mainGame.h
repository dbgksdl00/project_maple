#pragma once
#include "gameNode.h"
#include "gameScene.h"

class mainGame : public gameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(float timeDelta);
	virtual void render(void);


	
	mainGame();
	~mainGame();
};

/*
Ŭ���� �������� ¥������ �սôپƾ�!!
ver. ������ ���丮

mainGame -> ���Ŵ����� �۵���ų��... �ٸ����� ���� �ʴ´پƾ�


�ϴ� �� ���������� ¥��.����

IntroScene -> ���� ���۰� ���ÿ� �ΰ� ����ش�. �Ϻ� ������ ������ �ε��� �̺κп��� ó���Ѵ�.
loadingScene -> ������ ������ �ε��� ����Ѵ�
loginScene -> �α����� ó���Ѵ�.
selectScene -> ĳ���� ����â
makeCharScene -> ĳ���� ����â(enum �������·� ���� �ȿ��� �׳� ���Ŭ������ ����������...)
mapMoveScene -> ���̵��� ���ÿ� �׸ʿ� ����, ������ ������ �ε��ؿ´�.
gameScene -> �� ���Ӿ�




*/