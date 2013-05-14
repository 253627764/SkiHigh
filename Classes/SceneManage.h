#ifndef __SCENEHILLMANAGE_H__
#define __SCENEHILLMANAGE_H__

#include "cocos2d.h"
using namespace cocos2d;

class SceneManage : public CCNode
{
	CCArray* mHills;
private:
	SceneManage(void);
	~SceneManage(void);

public:
	static SceneManage* sharedSceneManage();
	
	virtual void update(float delta);
	CREATE_FUNC(SceneManage);
};

#endif // SCENEHILLMANAGE_H__
