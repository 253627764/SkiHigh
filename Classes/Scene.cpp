#include "Scene.h"
#include "Global.h"
#include "SkiHighLayer.h"
#include "VisibleRect.h"
#include "Steven.h"
#include "Coin.h"
#include "b2Helper.h"


Scene::Scene(void)
{
	mStartPoint.x = 100000;
	mEndPoint.x = -100000;
}

Scene::~Scene(void)
{
	destroyPhysicsWorld();
}

Scene* Scene::create(const char* name, Scene* lastScene )
{
	std::string file = std::string("hill\\") + std::string(name) + ".png";;
	Scene* pRet = Scene::create();
	CCPoint startPoint;
	if (lastScene)
		startPoint = lastScene->getWorldPosition(lastScene->mEndPoint);
	else
		startPoint = ccp(0,0);
	pRet->initWithFile(file.c_str());
	pRet->setAnchorPoint(ccp(0,1));
	pRet->mPhysicData =  dynamic_cast<PhysicDataScene*>(PhysicData::sharedPhysicData()->objectForKey(std::string(name)));
	pRet->setPosition(startPoint);
	pRet->createPhysicsWolrd();
	return pRet;
}

void Scene::createPhysicsWolrd()
{
	CCObject * pObj;
	CCARRAY_FOREACH(mPhysicData, pObj)
	{
		PhysicDataObject* pd = dynamic_cast<PhysicDataObject*>(pObj);
		if (!pd)
			continue;
		if (pd->Type() == "hill")
		{
			addHill(pd);
		}
		else if (pd->Type() == "tree")
		{
			addTree(pd);
		}
		else if (pd->Type() == "coin")
		{
			addCoin(pd);
		}
	}
}

void Scene::destroyPhysicsWorld()
{
	for (auto it = mHillBodys.begin(); it != mHillBodys.end(); it++)
	{
		b2Helper::destroyBody(*it);
	}
	mHillBodys.clear();
}

void Scene::addHill( PhysicDataObject* hillData )
{
	//startPoint;
	float ratio = G.PTM_RATIO;
	b2Vec2 startPoint(getPositionX()/ratio, getPositionY()/ratio);

	//set start point and end point
	PhysicDataHill* hd = dynamic_cast<PhysicDataHill*>(hillData);
	if (hd->mStartPoint.x < this->mStartPoint.x)
		this->mStartPoint = hd->mStartPoint;
	if (hd->mEndPoint.x > this->mEndPoint.x)
		this->mEndPoint = hd->mEndPoint;

	//body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	b2Body* body = b2Helper::createBody(&bodyDef, "hill");
	mHillBodys.insert(body);

	//set user data
	//b2Helper::setUserData(body, this, "sprite");

	//fixtureDef
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;
	fixtureDef.friction=0;
	fixtureDef.restitution = 0;

	for (int i=0; i<hd->mHillModel.size(); i++)
	{
		const Triangle& tri = hd->mHillModel[i];

		b2PolygonShape polygonShape;
		b2Vec2 vertices[3];
		for (int n=0; n<3; n++)
		{
			vertices[2-n].Set(tri.p[n].x/ratio, tri.p[n].y/ratio);
			vertices[2-n] += startPoint;
		}
		polygonShape.Set(vertices,3);
		fixtureDef.shape = &polygonShape;
		body->CreateFixture(&fixtureDef);
	}
}

void Scene::addTree( PhysicDataObject* treeData )
{
	PhysicDataTree* td = dynamic_cast<PhysicDataTree*>(treeData);
}

void Scene::addCoin(PhysicDataObject* coinData)
{
	//set start point and end point
	PhysicDataCoin* cd = dynamic_cast<PhysicDataCoin*>(coinData);

	//animation
	float xx = cd->pos.x + getPositionX();
	float yy = cd->pos.y + getPositionY();

	Coin* coin = Coin::create(ccp(xx, yy));
	SkiHighLayer::sharedSkiHighLayer()->addChild(coin);
}

bool Scene::leaveScreen()
{
	float start = SkiHighLayer::sharedSkiHighLayer()->getPositionX();
	float x = getWorldPosition(mEndPoint).x;

	if (start + getWorldPosition(mEndPoint).x < 0)
		return true;
	else
		return false;
}

bool Scene::enterScreen()
{
	float start = SkiHighLayer::sharedSkiHighLayer()->getPositionX();
	if ( start + getWorldPosition(mEndPoint).x < VisibleRect::getVisibleRect().size.width)
		return true;
	else
		return false;
}

CCPoint Scene::getWorldPosition(const CCPoint& point)
{
	return ccp(point.x + getPositionX(), point.y + getPositionY());
}

