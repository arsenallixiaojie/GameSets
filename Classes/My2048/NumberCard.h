#ifndef _NUMBERCARD_H_
#define _NUMBERCARD_H_

#include "cocos2d.h"
USING_NS_CC;

class NumberCard : public Node
{
public:
	NumberCard();
	~NumberCard();

	static const float CardLengthOfSide;

	CREATE_FUNC(NumberCard);

	void setNumber(int var);
	int getNumber(){ return m_iNum; };
private:
	bool init();

	LayerColor*		m_bgLayer;

	Label*			m_numLabel;

	int				m_iNum;
};


#endif