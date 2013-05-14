#include "SceneManage.h"
#include "SkiHighLayer.h"
#include "Scene.h"
#include "Steven.h"
#include "VisibleRect.h"

SceneManage::SceneManage(void)
{
	mHills = new CCArray();
}

SceneManage::~SceneManage(void)
{
	mHills->release();
}

SceneManage* SceneManage::sharedSceneManage()
{
	static SceneManage* pRet = NULL;
	if (!pRet)
	{
		pRet = SceneManage::create();
		pRet->scheduleUpdate();
	}
	return pRet;
}

void SceneManage::update( float delta )
{
	SkiHighLayer* ski = SkiHighLayer::sharedSkiHighLayer();

	if (mHills->count() == 0)
	{
		Scene* scene = Scene::create("SnowHill_2");
		ski->addChild(scene);
		mHills->addObject(scene);
	}

	Scene* scene = static_cast<Scene*>(mHills->objectAtIndex(0));
	if (scene->leaveScreen())
	{
		mHills->removeObject(scene);
		ski->removeChild(scene);
	}

	scene = static_cast<Scene*>(mHills->objectAtIndex(mHills->count()-1));
	if (scene->enterScreen())
	{
		Scene* newscene = Scene::create("SnowHill_2",scene);
		ski->addChild(newscene);
		mHills->addObject(newscene);
		newscene->setPosition(scene->getWorldPosition(scene->mEndPoint));
	}


/*	
	CCLOG("scene:%f,%f",scene->getPositionX(), scene->getPositionY());
	CCLOG("steven:%f,%f",Steven::sharedSteven()->getPositionX(), Steven::sharedSteven()->getPositionY());
	CCLOG("visibleRect:%f,%f",VisibleRect::center().x, VisibleRect::center().y);
	CCLOG("layer:%f,%f",SkiHighLayer::sharedSkiHighLayer()->getPositionX(), SkiHighLayer::sharedSkiHighLayer()->getPositionY());
	*/
}
