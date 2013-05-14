#include "LoadAnimation.h"
#include "cocos2d.h"
using namespace cocos2d;


static void loadStevenAnimation()
{
	//set seach path
	CCFileUtils::sharedFileUtils()->addSearchPath("steven\\");
	CCSpriteFrameCache* framecache = CCSpriteFrameCache::sharedSpriteFrameCache();

	//ski
	framecache->addSpriteFramesWithFile("steven\\steven.plist");
	CCArray* animFrames = CCArray::create();
	char str[50];
	for (int i=0; i<28; i++)
	{
		sprintf(str, "steven_ski_%d.png", i);
		CCSpriteFrame* frame = framecache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.05f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "steven_ski");
	animFrames->removeAllObjects();

	//pujie
	for (int i=0; i<8; i++)
	{
		sprintf(str, "steven_pujie_%d.png", i);
		CCSpriteFrame* frame = framecache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	for (int i=0; i<2; i++)
	{
		sprintf(str, "steven_pujie_7.png");
		CCSpriteFrame* frame = framecache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	animation = CCAnimation::createWithSpriteFrames(animFrames, 0.15f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "steven_pujie");
	animFrames->removeAllObjects();
}

void LoadAnimation::loadAnimation()
{
	loadStevenAnimation();
}
