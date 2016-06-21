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
클래스 구조도를 짜보도록 합시다아아!!
ver. 메이플 스토리

mainGame -> 씬매니저를 작동시킬뿐... 다른일은 하지 않는다아앗


일단 씬 구조도부터 짜자.ㅂㄷ

IntroScene -> 게임 시작과 동시에 로고를 띄워준다. 일부 빠르게 가능한 로딩은 이부분에서 처리한다.
loadingScene -> 게임의 시작전 로딩을 담당한다
loginScene -> 로그인을 처리한다.
selectScene -> 캐릭터 선택창
makeCharScene -> 캐릭터 생성창(enum 생성상태로 여기 안에서 그냥 사용클래스를 정의해주자...)
mapMoveScene -> 맵이동과 동시에 그맵에 몬스터, 구조물 정보를 로딩해온다.
gameScene -> 실 게임씬




*/