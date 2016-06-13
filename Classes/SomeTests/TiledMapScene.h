#ifndef _TILEDMAP_SCENE_H_
#define _TILEDMAP_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;


class TiledMapScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(TiledMapScene);

private:
	virtual bool init();

	Sprite* m_Player;

	TMXLayer* m_metaLayer;
};


#endif