#ifndef __STEVEN_H__
#define __STEVEN_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "b2Helper.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class Steven : public CCPhysicsSprite
{
	enum StevenStatus
	{
		SS_Ski,
		SS_Fall,
		SS_Fly,
	};

	static const float mRadius; 
	float mSkiHigh;
	StevenStatus mStatus;

	friend class GameController;
private:
	Steven(void);
	~Steven();

public:
	static Steven* sharedSteven();
	bool flying();
	b2Vec2 skiSpeed(b2Vec2 now);

	//ÌøÔ¾
	void jump(float v_y);

	//Ski
	void ski();

	//µøµ¹
	void fall();

	//»¬Ïè
	void fly();

	void rotationBy(float angle);

	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(Steven);
};

#endif // STEVEN_H__
