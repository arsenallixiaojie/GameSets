#include "ScrollNumber.h"


ScrollNumber::~ScrollNumber(){
	m_Labels.clear();
}

ScrollNumber* ScrollNumber::create(int iNumberCut, int iNumberSize){
	ScrollNumber* sn = new ScrollNumber;
	if (sn && sn->init(iNumberCut, iNumberSize))
	{
		sn->autorelease();
		return sn;
	}
	CC_SAFE_DELETE(sn);
	return nullptr;
}

bool ScrollNumber::init(int iNumberCut, int iNumberSize){
	if (!Node::init())
		return false;

	m_numberCnt = iNumberCut;
	
	DrawNode* stencil = DrawNode::create();
	stencil->drawSolidRect(Vec2(0, 0), Vec2(m_numberCnt*iNumberSize, iNumberSize), Color4F(1.0f, 1.0f, 1.0f, 1.0f));
	stencil->setPosition(0, 0);

	ClippingNode* cpn = ClippingNode::create(stencil);
	cpn->setPosition(Vec2(0, 0));
	addChild(cpn);

	for (int i = 0; i < m_numberCnt; i++)
	{
		//个位为零，从右到左递增
		ScrollNumberCol* col = ScrollNumberCol::create(iNumberSize);
		col->setPosition(Vec2(iNumberSize * (m_numberCnt - i - 1), 0));
		col->setTag(i);
		cpn->addChild(col);
		m_Labels.push_back(col);
	}

	return true;
}

void ScrollNumber::setNumber(int var){
	int Max = pow(10, m_numberCnt);
	CCASSERT(var < Max, "The Number should be less than Max");

	int dev = 0;
	int n = 0;
	for (int i = 0; i < m_numberCnt; i++)
	{
		dev = pow(10, i + 1);
		n = (var % dev) / pow(10, i);
		m_Labels[i]->setNumber(n);
	}
}






ScrollNumberCol* ScrollNumberCol::create(int iNumberSize){
	ScrollNumberCol* snc = new ScrollNumberCol;
	if (snc && snc->init(iNumberSize))
	{
		snc->autorelease();
		return snc;
	}
	CC_SAFE_DELETE(snc);
	return nullptr;
}
bool ScrollNumberCol::init(int iNumberSize){
	if (!Node::init())
		return false;

	m_iNumber = 0;
	m_visibleNode = Node::create();
	m_visibleNode->setPosition(Vec2(0,0));
	addChild(m_visibleNode);

	char str[4];
	for (int i = 0; i < 10; i++)
	{
		snprintf(str, sizeof(str), "%d", i);
		LabelTTF* num = LabelTTF::create(str, "", iNumberSize);
		num->setTag(i);
		num->setAnchorPoint(Vec2(0, 0));
		num->setPosition(0, i*iNumberSize);
		m_visibleNode->addChild(num);
	}

	return true;
}

void ScrollNumberCol::setNumber(int var){
	m_iNumber = var;
	stopAllActions();
	auto num = m_visibleNode->getChildByTag(var);
	Vec2 v = Vec2(m_visibleNode->getPositionX(), -num->getPositionY());
	m_visibleNode->runAction(MoveTo::create(0.5f, v));
}
