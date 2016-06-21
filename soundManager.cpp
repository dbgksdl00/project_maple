#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	: _system(NULL),
	_sound(NULL),
	_channel(NULL)
{
}


soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	//사운드 시스템 생성
	System_Create(&_system);

	//채널수 초기화(설정)
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//채널, 사운드 동적할당(필수)
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	//스택메모리 밀어준다
	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));


	return S_OK;
}

void soundManager::release()
{

}

void soundManager::update()
{

}

void soundManager::render()
{

}

void soundManager::addSound(char* keyName, char* soundName, bool bgm, bool loop)
{
	//루프 여부
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName, FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName, FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		_system->createStream(soundName, FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//맵에 사운드를 키값과 함꼐 넣어줌
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));


}

void soundManager::play(char* keyName, float volume) //0.0 ~ 1.0 0 ~ 255
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이 해줌
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);

			//볼륨 셋팅
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::stop(char* keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(char* keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(char* keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

void soundManager::setVolume(char* keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

//재생중읜지?
bool soundManager::isPlaySound(char* keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

//일시정지중인지?
bool soundManager::isPauseSound(char* keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}