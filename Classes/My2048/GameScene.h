#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class NumberCard;

class GameScene : public LayerColor
{
public:
	GameScene();
	~GameScene();

	static Scene* createScene();
	CREATE_FUNC(GameScene);
private:
	bool init();

	void initCards();

	void initMenu();

	void autoCreateNumber();

	void resetBtnCallback(Ref* obj);

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	bool slideToLeft();
	bool slideToRight();
	bool slideToTop();
	bool slideToBottom();

	void checkIsGameOver();
private:
	NumberCard* m_pCards[4][4];

	Size m_visibleSize;

	Vec2 m_beginPoint;
};

#endif