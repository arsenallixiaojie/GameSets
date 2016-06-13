#include "RotateWithAction.h"

RotateWithAction::~RotateWithAction(){
	CC_SAFE_RELEASE(pInnerAction);
}

RotateWithAction* RotateWithAction::create(ActionInterval* pAction){
	RotateWithAction* action = new RotateWithAction;
	if (action && action->initWithAction(pAction))
	{
		action->autorelease();
		return action;
	}
	CC_SAFE_DELETE(action);
	return nullptr;
}
bool RotateWithAction::initWithAction(ActionInterval* pAction){
	pAction->retain();
	pInnerAction = pAction;
	return true;
}

RotateWithAction* RotateWithAction::clone() const{
	auto a = new (std::nothrow)RotateWithAction;
	a->initWithAction(pInnerAction->clone());
	a->autorelease();
	return a;
}
RotateWithAction* RotateWithAction::reverse() const{
	return RotateWithAction::create(pInnerAction->reverse());
}
void RotateWithAction::startWithTarget(Node *target){
	pInnerTarget = target;
	Action::startWithTarget(target);
	pInnerAction->startWithTarget(target);
}
void RotateWithAction::stop(){
	pInnerAction->stop();
	Action::stop();
}
void RotateWithAction::step(float dt){
	Vec2 prePos = pInnerTarget->getPosition();
	pInnerAction->step(dt);
	Vec2 curPos = pInnerTarget->getPosition();

	float tan = -(curPos.y - prePos.y) / (curPos.x - prePos.x);
	float degree = atan(tan);
	degree = degree / 3.14159f * 180;
	pInnerTarget->setRotation(degree);
}
bool RotateWithAction::isDone() const{
	return pInnerAction->isDone();
}

void RotateWithAction::setInnerAction(ActionInterval* pAction){
	if (pInnerAction != pAction)
	{
		CC_SAFE_RELEASE(pInnerAction);
		pInnerAction = pAction;
		CC_SAFE_RETAIN(pInnerAction);
	}
}