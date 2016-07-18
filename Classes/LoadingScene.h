#ifndef _LOADING_SCENE_H_
#define _LOADING_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class LoadingScene : public LayerColor
{
public:
	static Scene* createScene();
	CREATE_FUNC(LoadingScene);

	LoadingScene();
	~LoadingScene();

private:
	bool init();

	void addResources();
	void pushBackResourceIntoVec(const std::string filePath);

	void startLoadResources();

	void updateTime(float dt);

private:

	void captureCallback1(bool bValue, const std::string& str);

private:
	Label*	m_pLabel;

	std::vector<std::string> m_vecFilePaths;

	const static int WaitTime;

	float m_fTime;

	int m_iLoadProgress;

};


#endif