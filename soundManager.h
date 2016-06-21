#pragma once
#include "singletonBase.h"
#include <map>

//fmod.hpp
#include "inc/fmod.hpp"

//lib��ũ
#pragma comment (lib, "lib/fmodex_vc.lib")

//���� ����
#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER EXTRACHANNELBUFFER + SOUNDBUFFER

using namespace FMOD;

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<char*, Sound**> arrSounds;
	typedef map<char*, Sound**>::iterator arrSoundsIter;
	typedef map<char*, Channel**> arrChannels;
	typedef map<char*, Channel**>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void addSound(char* keyName, char* soundName, bool bgm, bool loop);
	void play(char* keyName, float volume = 1.0f); //0.0 ~ 1.0 0 ~ 255
	void stop(char* keyName);
	void pause(char* keyName);
	void resume(char* keyName);
	void setVolume(char* keyName, float volume = 1.0f);

	//���������?
	bool isPlaySound(char* keyName);

	//�Ͻ�����������?
	bool isPauseSound(char* keyName);


	soundManager();
	~soundManager();
};

