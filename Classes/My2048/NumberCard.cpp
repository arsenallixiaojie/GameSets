#include "NumberCard.h"


const float NumberCard::CardLengthOfSide = 60.0f;

NumberCard::NumberCard(){

}
NumberCard::~NumberCard(){

}

bool NumberCard::init(){
	if (!Node::init())
		return false;

	setCascadeOpacityEnabled(true);

	m_bgLayer = LayerColor::create(Color4B(200, 190, 180, 255), CardLengthOfSide, CardLengthOfSide);
	m_bgLayer->setPosition(0, 0);
	addChild(m_bgLayer);

	m_numLabel = Label::createWithSystemFont("0", "", 40);
	m_numLabel->setPosition(Vec2(CardLengthOfSide/2, CardLengthOfSide/2));
	addChild(m_numLabel);

	return true;
}

void NumberCard::setNumber(int var){
	m_numLabel->setVisible(var != 0);

	m_iNum = var;

	char s[8];
	snprintf(s, sizeof(s), "%d", var);
	m_numLabel->setString(s);

	if (m_iNum >= 0 && m_iNum < 100)
		m_numLabel->setSystemFontSize(40);
	else if (m_iNum >= 100 && m_iNum < 1000)
		m_numLabel->setSystemFontSize(30);
	else
		m_numLabel->setSystemFontSize(20);

	if (m_iNum == 0)
		m_bgLayer->setColor(Color3B(200, 190, 180));
	else if (m_iNum == 2)
		m_bgLayer->setColor(Color3B(240, 230, 220));
	else if (m_iNum == 4)
		m_bgLayer->setColor(Color3B(240, 220, 200));
	else if (m_iNum == 8)
		m_bgLayer->setColor(Color3B(240, 180, 120));
	else if (m_iNum == 16)
		m_bgLayer->setColor(Color3B(240, 140, 90));
	else if (m_iNum == 32)
		m_bgLayer->setColor(Color3B(240, 120, 90));
	else if (m_iNum == 64)
		m_bgLayer->setColor(Color3B(240, 90, 60));
	else if (m_iNum == 128)
		m_bgLayer->setColor(Color3B(240, 90, 60));
	else if (m_iNum == 256)
		m_bgLayer->setColor(Color3B(240, 200, 70));
	else if (m_iNum == 512)
		m_bgLayer->setColor(Color3B(240, 200, 70));
	else if (m_iNum == 1024)
		m_bgLayer->setColor(Color3B(0, 130, 0));
	else if (m_iNum == 2048)
		m_bgLayer->setColor(Color3B(0, 130, 0));
	else
		m_bgLayer->setColor(Color3B(20, 190, 10));
}

void NumberCard::startShowAction(Vec2 centerPos, Vec2 targetPos)
{

	setOpacity(0);

	auto fadeIn = FadeIn::create(0.8f);
	auto moveToCenter = MoveTo::create(0.2f, centerPos);
	auto delayTime = DelayTime::create(0.2f);
// 	auto showLabel = CallFunc::create([this](){
// 		m_numLabel->setVisible(true);
// 		m_numLabel->setOpacity(0);
// 		m_numLabel->runAction(FadeIn::create(0.2f));
// 	});
	auto moveToPos = MoveTo::create(0.2f, targetPos);

	runAction(Sequence::create(fadeIn, moveToCenter, delayTime, moveToPos, nullptr));
}

void NumberCard::resetAction(Vec2 centerPos, Vec2 targetPos)
{
	auto moveToCenter = MoveTo::create(0.2f, centerPos);
	auto delayTime = DelayTime::create(0.2f);
// 	auto showLabel = CallFunc::create([this](){
// 		m_numLabel->setVisible(true);
// 		m_numLabel->setOpacity(0);
// 		m_numLabel->runAction(FadeIn::create(0.2f));
// 	});
	auto moveToPos = MoveTo::create(0.2f, targetPos);

	runAction(Sequence::create(moveToCenter, delayTime, moveToPos, nullptr));
}
