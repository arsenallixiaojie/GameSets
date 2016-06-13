#include "FlipNode.h"

FlipNode::FlipNode()
{
	m_fAniTime = 2.0f;
	m_iDirection = RIGHT_TO_LEFT;
}


FlipNode* FlipNode::create(const char* beforeSprName, const char* afterSprName, enFlipDirection iDirection)
{
	FlipNode* fn = new FlipNode;
	if (fn && fn->init(beforeSprName, afterSprName, iDirection))
	{
		fn->autorelease();
		return fn;
	}
	CC_SAFE_DELETE(fn);
	return nullptr;
}

FlipNode* FlipNode::create(Sprite* beforeSpr, Sprite* afterSpr, enFlipDirection iDirection)
{
	FlipNode* fn = new FlipNode;
	if (fn && fn->init(beforeSpr, afterSpr, iDirection))
	{
		fn->autorelease();
		return fn;
	}
	CC_SAFE_DELETE(fn);
	return nullptr;
}

bool FlipNode::init(const char* beforeSprName, const char* afterSprName, enFlipDirection iDirection)
{
	if (!Node::init())
		return false;

	return init(Sprite::create(beforeSprName), Sprite::create(afterSprName), iDirection);
}

bool FlipNode::init(Sprite* beforeSpr, Sprite* afterSpr, enFlipDirection iDirection)
{
	if (!Node::init())
		return false;

	if (beforeSpr == nullptr || afterSpr == nullptr)
	{
		return false;
	}

	m_iDirection = iDirection;

	m_pBefore = beforeSpr;
	m_pAfter = afterSpr;

	addChild(m_pBefore);
	addChild(m_pAfter);
	m_pAfter->setVisible(false);

	switch (m_iDirection)
	{
	case LEFT_TO_RIGHT:
		m_pAfter->setRotation3D(Vec3(0, -90, 0));
		break;
	case RIGHT_TO_LEFT:
		m_pAfter->setRotation3D(Vec3(0, 90, 0));
		break;
	case UP_TO_DOWN:
		m_pAfter->setRotation3D(Vec3(-90, 0, 0));
		break;
	case DOWN_TO_UP:
		m_pAfter->setRotation3D(Vec3(90, 0, 0));
		break;
	default:
		break;
	}

	return true;
}

void FlipNode::startFlip(float fTime){
	m_fAniTime = fTime; 

	CCASSERT(m_fAniTime >= 0, "Animation time should large than 0 or equal 0");
	CCASSERT(m_iDirection >= RIGHT_TO_LEFT && m_iDirection <= DOWN_TO_UP, "Direction value is not true!");

	startFlip();
}
void FlipNode::startFlip(){
	stopFlipActions();

	Vec3 v3;
	switch (m_iDirection)
	{
	case LEFT_TO_RIGHT:
		v3 = Vec3(0, 90, 0);
		break;
	case RIGHT_TO_LEFT:
		v3 = Vec3(0, -90, 0);
		break;
	case UP_TO_DOWN:
		v3 = Vec3(90, 0, 0);
		break;
	case DOWN_TO_UP:
		v3 = Vec3(-90, 0, 0);
		break;
	default:
		break;
	}


	auto rotate1 = RotateBy::create(m_fAniTime/2, v3);

	auto seq1 = Sequence::create( rotate1, Hide::create(), nullptr);

	auto rotate2 = rotate1->clone();
	
	auto seq2 = Sequence::create(DelayTime::create(m_fAniTime / 2), Show::create(), rotate2, nullptr);

	m_pBefore->runAction(seq1);
	m_pAfter->runAction(seq2);

	runAction(Sequence::create(DelayTime::create(m_fAniTime), CallFunc::create(CC_CALLBACK_0(FlipNode::flipAniEndCallback, this)), nullptr));
}

void FlipNode::stopFlipActions(){
	m_pAfter->stopAllActions();
	m_pBefore->stopAllActions();
	stopAllActions();

	m_pBefore->setVisible(true);
	m_pBefore->setRotation3D(Vec3(0, 0, 0));
	m_pAfter->setVisible(false);
	switch (m_iDirection)
	{
	case LEFT_TO_RIGHT:
		m_pAfter->setRotation3D(Vec3(0, -90, 0));
		break;
	case RIGHT_TO_LEFT:
		m_pAfter->setRotation3D(Vec3(0, 90, 0));
		break;
	case UP_TO_DOWN:
		m_pAfter->setRotation3D(Vec3(-90, 0, 0));
		break;
	case DOWN_TO_UP:
		m_pAfter->setRotation3D(Vec3(90, 0, 0));
		break;
	default:
		break;
	}
}

void FlipNode::flipAniEndCallback(){
	Sprite* temp = m_pAfter;
	m_pAfter = m_pBefore;
	m_pBefore = temp;
}