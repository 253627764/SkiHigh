#ifndef __SNOWHILL_H__
#define __SNOWHILL_H__

#include "cocos2d.h"
#include "PhysicData.h"
#include "Box2D/Box2D.h"
using namespace cocos2d;

class Scene : public CCSprite
{
	friend class SceneManage;
	PhysicDataScene* mPhysicData;
	CCPoint mStartPoint;
	CCPoint mEndPoint;
	std::set<b2Body*> mHillBodys;
private:
	Scene(void);
	~Scene(void);

public:
	static Scene* create(const char* name, Scene* lastScene = NULL);
	void removeBody(b2Body* body);
	bool leaveScreen();
	bool enterScreen();

private:
	CCPoint getWorldPosition(const CCPoint& point);
	void createPhysicsWolrd();
	void destroyPhysicsWorld();
	void addHill(PhysicDataObject* hillData);
	void addTree(PhysicDataObject* treeData);
	void addCoin(PhysicDataObject* coinData);
	CREATE_FUNC(Scene);
};

#endif // SNOWHILL_H__
