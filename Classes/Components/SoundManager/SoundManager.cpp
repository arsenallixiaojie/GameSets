#include "SoundManager.h"
#include "audio/include/SimpleAudioEngine.h"

using namespace CocosDenshion;

SoundManager* SoundManager::_instance = nullptr;

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	if (_instance)
	{
		delete _instance;
	}
	_instance = nullptr;
}


SoundManager* SoundManager::createManager()
{
	if (_instance)
	{
		return _instance;
	}
	auto _ins = new SoundManager();
	if (!_ins)
	{
		delete _ins;
		return nullptr;
	}
	_instance = _ins;
	return _instance;
}



void SoundManager::preloadBackgroundMusic(const char* filePath)
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(filePath);
}

void SoundManager::playBackgroundMusic(const char* filePath, bool loop /*= false*/)
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath, loop);
}

void SoundManager::stopBackgroundMusic(bool releaseData /*= false*/)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(releaseData);
}

void SoundManager::pauseBackgroundMusic()
{
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::resumeBackgroundMusic()
{
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void SoundManager::rewindBackgroundMusic()
{
	SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
}

bool SoundManager::willPlayBackgroundMusic()
{
	return SimpleAudioEngine::getInstance()->willPlayBackgroundMusic();
}

bool SoundManager::isBackgroundMusicPlaying()
{
	return SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
}

float SoundManager::getBackgroundMusicVolume()
{
	return SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
}

void SoundManager::setBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

float SoundManager::getEffectsVolume()
{
	return SimpleAudioEngine::getInstance()->getEffectsVolume();
}

void SoundManager::pauseEffect(unsigned int soundId)
{
	SimpleAudioEngine::getInstance()->pauseEffect(soundId);
}

void SoundManager::pauseAllEffects()
{
	SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void SoundManager::resumeEffect(unsigned int soundId)
{
	SimpleAudioEngine::getInstance()->resumeEffect(soundId);
}

void SoundManager::resumeAllEffects()
{
	SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void SoundManager::stopEffect(unsigned int soundId)
{
	SimpleAudioEngine::getInstance()->stopEffect(soundId);
}

void SoundManager::stopAllEffects()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void SoundManager::preloadEffect(const char* filePath)
{
	SimpleAudioEngine::getInstance()->preloadEffect(filePath);
}

unsigned int SoundManager::playEffect(const char* filePath, bool loop /*= false*/, float pitch /*= 1.0f*/, float pan /*= 0.0f*/, float gain /*= 1.0f*/)
{
	return SimpleAudioEngine::getInstance()->playEffect(filePath, loop, pitch, pan, gain);
}

void SoundManager::setEffectVolume(float fVolume)
{
	SimpleAudioEngine::getInstance()->setEffectsVolume(fVolume);
}

