#ifndef _FLIPNODE_H_
#define _FLIPNODE_H_

#include "cocos2d.h"
USING_NS_CC;

//////////////////////////////////////////////////////////////////////////
//这是用来实现类似翻转卡片效果的Node，可以设置多个方向
//////////////////////////////////////////////////////////////////////////

enum enFlipDirection{
	RIGHT_TO_LEFT,
	LEFT_TO_RIGHT,
	UP_TO_DOWN,
	DOWN_TO_UP,
};

class FlipNode : public Node
{
public:
	FlipNode();
	static FlipNode* create(const char* beforeSprName, const char* afterSprName, enFlipDirection iDirection = LEFT_TO_RIGHT);
	static FlipNode* create(Sprite* beforeSpr, Sprite* afterSpr, enFlipDirection iDirection = LEFT_TO_RIGHT);

private:
	bool init(const char* beforeSprName, const char* afterSprName, enFlipDirection iDirection);
	bool init(Sprite* beforeSpr, Sprite* afterSpr, enFlipDirection iDirection);


	void flipAniEndCallback();
public:
	void startFlip(float fTime);
	void startFlip();

	void stopFlipActions();
private:
	float	m_fAniTime;
	enFlipDirection		m_iDirection;		

	Sprite* m_pBefore;
	Sprite* m_pAfter;
};





#endif