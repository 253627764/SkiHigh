#ifndef __COIN_H__
#define __COIN_H__

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class Coin : public CCPhysicsSprite
{
private:
	Coin(void);
	~Coin(void);

public:
	virtual bool init();
	static Coin* create(CCPoint pos);
	CREATE_FUNC(Coin);
};

#endif // COIN_H__
