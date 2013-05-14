#ifndef __SKIHIGHLAYER_H__
#define __SKIHIGHLAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
using namespace cocos2d;

class SkiHighLayer : public CCLayer 
{
private:
	SkiHighLayer(void);

public: 
	static SkiHighLayer* sharedSkiHighLayer();
	virtual bool init(); 
	virtual void update(float delta);

#ifdef DEBUG
	virtual void draw();
#endif

	CREATE_FUNC(SkiHighLayer);
};

#endif // SKIHIGHLAYER_H__
