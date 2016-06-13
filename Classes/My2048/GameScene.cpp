#include "GameScene.h"
#include "NumberCard.h"

GameScene::GameScene()
{

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

	auto label = Label::createWithTTF("Reset", "fonts/HandWrite.ttf", 30);
	MenuItemLabel* pReset = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::resetBtnCallback, this));
	pReset->setColor(Color3B(0,0,0));
	pReset->setPosition(Vec2(m_visibleSize.width/2, m_visibleSize.height - 50));
	pMemu->addChild(pReset);
}

void GameScene::initCards(){
	NumberCard* card = nullptr;
	float gap = 6.0f;
	float posY = m_visibleSize.height - 200;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			card = NumberCard::create();
			card->setPosition(i*NumberCard::CardLengthOfSide + (i+1)*gap, posY - j*(gap + NumberCard::CardLengthOfSide));
			addChild(card);

			m_pCards[i][j] = card;
		}
	}
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
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_pCards[i][j]->setNumber(0);
		}
	}

	autoCreateNumber();
	autoCreateNumber();
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
		//消抖
		return;
	}

	if (abs(disX) > abs(disY))
	{
		//水平方向
		if (disX > 2)
		{
			//向右
			if (slideToRight())
			{
				autoCreateNumber();
				checkIsGameOver();
			}
		}
		else
		{
			//向左
			if (slideToLeft())
			{
				autoCreateNumber();
				checkIsGameOver();
			}
		}
	}
	else
	{
		//垂直方向
		if (disY > 2)
		{
			//向上
			if (slideToTop())
			{
				autoCreateNumber();
				checkIsGameOver();
			}
		}
		else
		{
			//向下
			if (slideToBottom())
			{
				autoCreateNumber();
				checkIsGameOver();
			}
		}
	}
}

bool GameScene::slideToLeft(){
	log("GameScene::slideToLeft");
	bool isDo = false;

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
						m_pCards[i][j]->setNumber(m_pCards[i][j]->getNumber() + m_pCards[k][j]->getNumber());
						m_pCards[k][j]->setNumber(0);
						isDo = true;
					}

					break;
				}
			}
		}
	}

	return isDo;
}
bool GameScene::slideToRight(){
	log("GameScene::slideToRight");

	bool isDo = false;

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
						m_pCards[i][j]->setNumber(m_pCards[i][j]->getNumber() + m_pCards[k][j]->getNumber());
						m_pCards[k][j]->setNumber(0);
						isDo = true;
					}

					break;
				}
			}
		}
	}

	return isDo;
}
bool GameScene::slideToTop(){
	log("GameScene::slideToTop");
	bool isDo = false;

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
						m_pCards[i][j]->setNumber(m_pCards[i][j]->getNumber() + m_pCards[i][k]->getNumber());
						m_pCards[i][k]->setNumber(0);
						isDo = true;
					}

					break;
				}
			}
		}
	}

	return isDo;
}
bool GameScene::slideToBottom(){
	log("GameScene::slideToBottom");
	bool isDo = false;

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
						m_pCards[i][j]->setNumber(m_pCards[i][j]->getNumber() + m_pCards[i][k]->getNumber());
						m_pCards[i][k]->setNumber(0);
						isDo = true;
					}

					break;
				}
			}
		}
	}

	return isDo;
}