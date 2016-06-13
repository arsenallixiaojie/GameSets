#ifndef _SCROLLNUMBER_H_
#define _SCROLLNUMBER_H_

//////////////////////////////////////////////////////////////////////////
//����ʵ�����ֹ�������������ˢ�·���
//////////////////////////////////////////////////////////////////////////


#include "cocos2d.h"
USING_NS_CC;

class ScrollNumberCol;

class ScrollNumber : public Node
{
public:
	~ScrollNumber();

	//iNumberCut ��λ����iNumberSize �������С
	static ScrollNumber* create(int iNumberCut = 4, int iNumberSize = 20);

	CC_SYNTHESIZE(int, m_numberCnt, NumberCut);

	void setNumber(int var);
private:
	bool init(int iNumberCut, int iNumberSize);

private:
	std::vector<ScrollNumberCol*> m_Labels;
};



class ScrollNumberCol : public Node
{
public:
	static ScrollNumberCol* create(int iNumberSize);

	void setNumber(int var);
private:
	bool init(int iNumberSize);

private:
	Node* m_visibleNode;

	int m_iNumber;
};



#endif