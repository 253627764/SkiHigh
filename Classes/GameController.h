#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "cocos2d.h"
using namespace cocos2d;

class GameController : public CCLayer
{
	bool mTouching;
private:
	GameController(void);
	~GameController(void);
	
public:
	static GameController* sharedGameController();
	virtual bool init();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void update(float delta);

	CREATE_FUNC(GameController);
};

#endif // GAMECONTROLLER_H__
