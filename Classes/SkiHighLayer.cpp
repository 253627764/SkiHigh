#include "SkiHighLayer.h"
#include "Steven.h"
#include "Scene.h"
#include "Global.h"
#include "SceneManage.h"
#include "cocos-ext.h"
#include "GLES-Render.h"
using namespace cocos2d::extension;

#define PTM_RATIO (32)

CCNode* sfollowNode = NULL;

SkiHighLayer::SkiHighLayer(void)
{
}

bool SkiHighLayer::init()
{
	GLESDebugDraw * m_debugDraw = new GLESDebugDraw( PTM_RATIO );
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	m_debugDraw->SetFlags(flags);
	G.world->SetDebugDraw(m_debugDraw);

	//setTouchEnabled( true );
	//setAccelerometerEnabled( true );
	setAnchorPoint(ccp(0.2,0.5));
	addChild(Steven::sharedSteven(),100);

	//set anchor
	setAnchorPoint(ccp(0,00));

	//follow
	sfollowNode = CCNode::create();
	addChild(sfollowNode);
	runAction(CCFollow::create(sfollowNode));

	//scene manage
	addChild(SceneManage::sharedSceneManage());

	scheduleUpdate();
	return true;
}

SkiHighLayer* SkiHighLayer::sharedSkiHighLayer()
{
	static SkiHighLayer* pRet = NULL;
	if (!pRet)
	{
		pRet = SkiHighLayer::create();
	}
	return pRet;
}

void SkiHighLayer::update( float delta )
{
	//update follow note
	Steven* steven = Steven::sharedSteven();
	sfollowNode->setPosition(ccp(steven->getPositionX() + 412, steven->getPositionY()));

	//update physic world
	int velocityIterations = 8;
	int positionIterations = 1;
	G.world->Step(delta, velocityIterations, positionIterations);
}

#ifdef DEBUG
void SkiHighLayer::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	G.world->DrawDebugData();
	kmGLPopMatrix();
}
#endif

