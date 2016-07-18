#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class NumberCard;
class ScrollNumber;

typedef enum enDirection
{
	enToLeft,
	enToRight,
	enToTop,
	enToBottom
};

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

	void initScrollScore();

	void autoCreateNumber();

private:
	void resetBtnCallback(Ref* obj);

	void undoBtnCallback(Ref* obj);
private:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

private:
	bool toLeft();
	bool toRight();
	bool toTop();
	bool toBottom();

	void switchDirection(enDirection direction);

	void checkIsGameOver();
private:
	Size m_visibleSize;

	Vec2 m_beginPoint;

	bool m_isCanUndo;

private:
	ScrollNumber* m_pScrollScore;

	int m_iScore;

private:
	int m_pLastCards[4][4];

	NumberCard* m_pCards[4][4];

private:
	const static int m_iCardGap;   //卡片之间的间隙距离
};

#endif