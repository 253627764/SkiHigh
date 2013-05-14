#include "GameController.h"
#include "Steven.h"


GameController::GameController(void) :
mTouching(false)
{
}


GameController::~GameController(void)
{
}

GameController* GameController::sharedGameController()
{
	static GameController* pRet = NULL;
	if (!pRet)
	{
		pRet = GameController::create();
	}
	return pRet;
}

bool GameController::init()
{
	setTouchEnabled(true);
	scheduleUpdate();
	return true;
}

bool GameController::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	mTouching = true;
	
	//controll steven
	Steven* steven = Steven::sharedSteven();
	if (!steven->flying())
	{
		steven->jump(10);
	}

	return true;
}

void GameController::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	mTouching = false;
}

void GameController::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void GameController::update( float delta )
{
	Steven* steven = Steven::sharedSteven();
	if (steven->flying() && mTouching)
	{
		steven->rotationBy(120 * delta);
	}
}

