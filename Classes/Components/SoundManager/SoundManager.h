#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_


#include "cocos2d.h"

USING_NS_CC;


class SoundManager
{
public:
	static SoundManager* createManager();
	static SoundManager* getSingletonPtr(){ return _instance; };

	SoundManager();
	~SoundManager();


public:
	//±≥æ∞“Ù¿÷

	void preloadBackgroundMusic(const char* filePath);

	void playBackgroundMusic(const char* filePath, bool loop = false);

	void stopBackgroundMusic(bool releaseData = false);

	void pauseBackgroundMusic();

	void resumeBackgroundMusic();

	void rewindBackgroundMusic();

	bool willPlayBackgroundMusic();

	bool isBackgroundMusicPlaying();

	float getBackgroundMusicVolume();

	void setBackgroundMusicVolume(float volume);


	//“Ù–ß

	float getEffectsVolume();

	void setEffectVolume(float fVolume);

	unsigned int playEffect(const char* filePath, bool loop = false,
		float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);

	void pauseEffect(unsigned int soundId);

	void pauseAllEffects();

	void resumeEffect(unsigned int soundId);

	void resumeAllEffects();

	void stopEffect(unsigned int soundId);

	void stopAllEffects();
	
	void preloadEffect(const char* filePath);

private:
	static SoundManager* _instance;
};


#endif