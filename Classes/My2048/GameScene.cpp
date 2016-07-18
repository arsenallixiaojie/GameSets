#include "GameScene.h"
#include "NumberCard.h"
#include "SoundManager.h"
#include "ScrollNumber.h"

const int GameScene::m_iCardGap = 6;

GameScene::GameScene()
{
	m_isCanUndo = false;
	m_pScrollScore = nullptr;
	m_iScore = 0;
}

GameScene::~GameScene()
{

}

Scene* GameScene::createScene()
{
	Scene* s = Scene::create();
	GameScene* gs = GameScene::create();
	s->addChild(gs);
	return s;
}


bool GameScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
		return false;

	m_visibleSize = Director::getInstance()->getVisibleSize();

	srand((int)time(0));

	initMenu();
	initCards();
	initScrollScore();

	autoCreateNumber();
	autoCreateNumber();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *touch, Event *unused_event){return onTouchBegan(touch, unused_event); };
	listener->onTouchMoved = [this](Touch *touch, Event *unused_event){onTouchMoved(touch, unused_event); };
	listener->onTouchEnded = [this](Touch *touch, Event *unused_event){onTouchEnded(touch, unused_event); };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameScene::initMenu(){
	Menu* pMemu = Menu::create();
	pMemu->setPosition(Vec2(0, 0));
	addChild(pMemu);

	auto label = Label::createWithTTF("Reset", "fonts/arial.ttf", 30);
	MenuItemLabel* pReset = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::resetBtnCallback, this));
	pReset->setColor(Color3B(0,0,0));
	pReset->setPosition(Vec2(m_visibleSize.width/2, m_visibleSize.height - 50));
	pMemu->addChild(pReset);

	auto pUndoLabel = Label::createWithTTF("Undo", "fonts/arial.ttf", 30);
	MenuItemLabel* pUndo = MenuItemLabel::create(pUndoLabel, CC_CALLBACK_1(GameScene::undoBtnCallback, this));
	pUndo->setColor(Color3B(0, 0, 0));
	pUndo->setPosition(Vec2(m_visibleSize.width / 2 + 80, m_visibleSize.height - 50));
	pMemu->addChild(pUndo);
}

void GameScene::initCards(){
	NumberCard* card = nullptr;
	float posY = m_visibleSize.height - 200;

	Vec2 centerPos;
	Vec2 targetPos;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			card = NumberCard::create();
			card->setPosition(i*NumberCard::CardLengthOfSide + (i + 1)*m_iCardGap, posY - j*(m_iCardGap + NumberCard::CardLengthOfSide));
			card->setNumber(0);
			
			centerPos = Vec2(m_visibleSize.width / 2 - NumberCard::CardLengthOfSide / 2, posY - 1.5*(m_iCardGap + NumberCard::CardLengthOfSide));
			targetPos = Vec2(i*NumberCard::CardLengthOfSide + (i + 1)*m_iCardGap, posY - j*(m_iCardGap + NumberCard::CardLengthOfSide));
			card->startShowAction(centerPos, targetPos);

			m_pCards[i][j] = card;
			addChild(card);
		}
	}
}


void GameScene::initScrollScore()
{
	m_pScrollScore = ScrollNumber::create(5, 24);
	m_pScrollScore->setNumber(m_iScore);
	m_pScrollScore->setPosition(Vec2(m_visibleSize.width/2, 50));
	addChild(m_pScrollScore);
}


void GameScene::autoCreateNumber(){
	int x = rand() % 4;
	int y = rand() % 4;
	if (m_pCards[x][y]->getNumber() > 0)
	{
		autoCreateNumber();
	}
	else
	{
		m_pCards[x][y]->setNumber(rand()%10<1?4:2);
	}
}


void GameScene::resetBtnCallback(Ref* obj){
	Vec2 centerPos;
	Vec2 targetPos;
	float posY = m_visibleSize.height - 200;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_pCards[i][j]->setNumber(0);
			centerPos = Vec2(m_visibleSize.width / 2 - NumberCard::CardLengthOfSide / 2, posY - 1.5*(m_iCardGap + NumberCard::CardLengthOfSide));
			targetPos = Vec2(i*NumberCard::CardLengthOfSide + (i + 1)*m_iCardGap, posY - j*(m_iCardGap + NumberCard::CardLengthOfSide));
			m_pCards[i][j]->resetAction(centerPos, targetPos);
		}
	}

	autoCreateNumber();
	autoCreateNumber();
}

void GameScene::undoBtnCallback(Ref* obj)
{
	log("GameScene::undoBtnCallback");
	if (!m_isCanUndo)
		return;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_pCards[i][j]->setNumber(m_pLastCards[i][j]);
		}
	}
}

void GameScene::checkIsGameOver(){
	bool isGameOver = true;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_pCards[i][j]->getNumber() == 0 ||
				(i > 0 && m_pCards[i][j]->getNumber() == m_pCards[i-1][j]->getNumber()) ||
				(i < 3 && m_pCards[i][j]->getNumber() == m_pCards[i+1][j]->getNumber()) || 
				(j > 0 && m_pCards[i][j]->getNumber() == m_pCards[i][j-1]->getNumber()) || 
				(j < 3 && m_pCards[i][j]->getNumber() == m_pCards[i][j+1]->getNumber()))
			{
				isGameOver = false;
			}
		}
	}
	


}


void GameScene::switchDirection(enDirection direction)
{
	bool isDo = false;
	switch (direction)
	{
	case enToLeft:
		isDo = toLeft();
		break;
	case enToRight:
		isDo = toRight();
		break;
	case enToTop:
		isDo = toTop();
		break;
	case enToBottom:
		isDo = toBottom();
		break;
	default:
		break;
	}

	if (isDo)
	{
		m_isCanUndo = true;
		m_pScrollScore->setNumber(m_iScore);
		autoCreateNumber();
		checkIsGameOver();
	}
}


bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){
	m_beginPoint = touch->getLocation();
	
	return true;
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event){
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event){
	Vec2 endPoint = touch->getLocation();
	float disX = endPoint.x - m_beginPoint.x;
	float disY = endPoint.y - m_beginPoint.y;

	if (abs(disX) < 2 && abs(disY) <2)
	{
		//Ïû¶¶
		return;
	}

	if (abs(disX) > abs(disY))
		switchDirection( disX > 2 ? enToRight : enToLeft);
	else
		switchDirection( disY > 2 ? enToTop : enToBottom);
}

bool GameScene::toLeft(){
	log("GameScene::toLeft");
	bool isDo = false;

	int temp[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			temp[i][j] = m_pCards[i][j]->getNumber();

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int k = i + 1; k < 4; k++)
			{
				if (m_pCards[k][j]->getNumber() > 0)
				{
					if (m_pCards[i][j]->getNumber() <= 0)
					{
						m_pCards[i][j]->setNumber(m_pCards[k][j]->getNumber());
						m_pCards[k][j]->setNumber(0);
						i--;
						isDo = true;
					}
					else if (m_pCards[i][j]->getNumber() == m_pCards[k][j]->getNumber())
					{
						m_iScore += m_pCards[k][j]->getNumber();
						m_pCards[i][j]->setNumber(m_pCards[i][j]->getNumber() + m_pCards[k][j]->getNumber());
						m_pCards[k][j]->setNumber(0);
						isDo = true;
					}

					break;
				}
			}
		}
	}

	if (isDo)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m_pLastCards[i][j] = temp[i][j];
	}

	return isDo;
}
bool GameScene::toRight(){
	log("GameScene::toRight");

	bool isDo = false;

	int temp[4][4];
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		temp[i][j] = m_pCards[i][j]->getNumber();

	for (int j = 0; j < 4; j++)
	{
		for (int i = 3; i >= 0; i--)
		{
			for (int k = i - 1; k >= 0; k--)
			{
				if (m_pCards[k][j]->getNumber() > 0)
				{
					if (m_pCards[i][j]->getNumber() <= 0)
					{
						m_pCards[i][j]->setNumber(m_pCards[k][j]->getNumber());
						m_pCards[k][j]->setNumber(0);
						i++;
						isDo = true;
					}
					else if (m_pCards[i][j]->getNumber() == m_pCards[k][j]->getNumber())
					{
						m_iScore += m_pCards[k][j]->getNumber();
						m_pCards[i][j]->setNumber(m_pCards[i][j]->getNumber() + m_pCards[k][j]->getNumber());
						m_pCards[k][j]->setNumber(0);
					
						isDo = true;
					}

					break;
				}
			}
		}
	}

	if (isDo)
	{
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_pLastCards[i][j] = temp[i][j];
	}

	return isDo;
}
bool GameScene::toTop(){
	log("GameScene::toTop");
	bool isDo = false;

	int temp[4][4];
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		temp[i][j] = m_pCards[i][j]->getNumber();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = j + 1; k < 4; k++)
			{
				if (m_pCards[i][k]->getNumber() > 0)
				{
					if (m_pCards[i][j]->getNumber() <= 0)
					{
						m_pCards[i][j]->setNumber(m_pCards[i][k]->getNumber());
						m_pCards[i][k]->setNumber(0);
						j--;
						isDo = true;
					}
					else if (m_pCards[i][j]->getNumber() == m_pCards[i][k]->getNumber())
					{
						m_iScore += m_pCards[i][k]->getNumber();
						m_pCards[i][j]->setNumber(m_pCards[i][j]->getNumber() + m_pCards[i][k]->getNumber());
						m_pCards[i][k]->setNumber(0);
						isDo = true;
					}

					break;
				}
			}
		}
	}

	if (isDo)
	{
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_pLastCards[i][j] = temp[i][j];
	}

	return isDo;
}
bool GameScene::toBottom(){
	log("GameScene::toBottom");
	bool isDo = false;

	int temp[4][4];
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		temp[i][j] = m_pCards[i][j]->getNumber();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			for (int k = j - 1; k >= 0; k--)
			{
				if (m_pCards[i][k]->getNumber() > 0)
				{
					if (m_pCards[i][j]->getNumber() <= 0)
					{
						m_pCards[i][j]->setNumber(m_pCards[i][k]->getNumber());
						m_pCards[i][k]->setNumber(0);
						j++;
						isDo = true;
					}
					else if (m_pCards[i][j]->getNumber() == m_pCards[i][k]->getNumber())
					{
						m_iScore += m_pCards[i][k]->getNumber();
						m_pCards[i][j]->setNumber(m_pCards[i][j]->getNumber() + m_pCards[i][k]->getNumber());
						m_pCards[i][k]->setNumber(0);
						isDo = true;
					}

					break;
				}
			}
		}
	}

	if (isDo)
	{
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_pLastCards[i][j] = temp[i][j];
	}

	return isDo;
}


