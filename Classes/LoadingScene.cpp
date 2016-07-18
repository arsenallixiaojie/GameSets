#include "LoadingScene.h"
#include "Tools.h"
#include "GameScene.h"


const int LoadingScene::WaitTime = 2.0f;

LoadingScene::LoadingScene()
{
	m_fTime = 0;
	m_iLoadProgress = 0;
}

LoadingScene::~LoadingScene()
{

}

Scene* LoadingScene::createScene()
{
	auto _s = Scene::create();
	LoadingScene* _l = LoadingScene::create();
	_s->addChild(_l);
	return _s;
}



bool LoadingScene::init()
{
	if (!LayerColor::initWithColor(Color4B(241, 225, 214, 255)))
	{
		return false;
	}

	auto screenSize = Director::getInstance()->getWinSize();

	m_pLabel = Label::createWithSystemFont("Loading 0 %", "", 30);
	m_pLabel->setColor(Color3B(0, 0, 0));
	m_pLabel->setPosition(Vec2(screenSize.width/2, 50));
	addChild(m_pLabel);

	auto pLogo = Sprite::create("loading_logo.png");
	pLogo->setOpacity(0);
	pLogo->setPosition(Vec2(screenSize.width/2, screenSize.height/2));
	pLogo->runAction(FadeIn::create(1.0f));
	addChild(pLogo);

	schedule(schedule_selector(LoadingScene::updateTime), 1.0f);

	addResources();
	startLoadResources();

// 	std::string path;
// 	getWritePath(path);
// 	path += "Test/";
// 	log("write path = %s", path.c_str());
// 
// 	SharedTools::ensureDirectoryExists(path.c_str());



	return true;
}

void LoadingScene::addResources()
{
	pushBackResourceIntoVec("test2.plist");
	pushBackResourceIntoVec("Hero.plist");
}

void LoadingScene::pushBackResourceIntoVec(const std::string filePath)
{
	m_vecFilePaths.push_back(filePath);
}

void LoadingScene::startLoadResources()
{
	int nSize = m_vecFilePaths.size();
	int curCount = 0;
	char s[32];
	for (auto it = m_vecFilePaths.begin(); it != m_vecFilePaths.end(); it++)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(*it);
		log("result = %d", SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded(*it));

		curCount++;
		m_iLoadProgress = curCount * 1.0f / nSize * 100;
		snprintf(s, sizeof(s), "Loading %d %%", m_iLoadProgress);
		m_pLabel->setString(s);
	}
}

void LoadingScene::updateTime(float dt)
{
	m_fTime += 1.0f;
	log("time = %f", m_fTime);

	if (m_fTime >= WaitTime)
	{
		if (m_iLoadProgress >= 100)
		{
			unschedule(schedule_selector(LoadingScene::updateTime));
			Director::getInstance()->replaceScene(GameScene::createScene());
		}
	}
}


