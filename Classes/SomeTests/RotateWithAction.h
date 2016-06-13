#ifndef _ROTATEWITHACTION_H_
#define _ROTATEWITHACTION_H_

#include "cocos2d.h"
USING_NS_CC;

class RotateWithAction : public ActionInterval
{
public:
	~RotateWithAction();

	virtual RotateWithAction* clone() const override;
	virtual RotateWithAction* reverse() const override;
	virtual void startWithTarget(Node *target) override;
	virtual void stop() override;
	virtual void step(float dt) override;
	virtual bool isDone() const override;

	static RotateWithAction* create(ActionInterval* pAction);
	bool initWithAction(ActionInterval* pAction);

protected:
	void setInnerAction(ActionInterval* pAction);

	Node* pInnerTarget;
	ActionInterval* pInnerAction;

};



#endif