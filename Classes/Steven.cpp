#include "Steven.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

const float Steven::mRadius = 32;

Steven::Steven(void)
{
}
Steven::~Steven()
{
	b2Helper::destroyBody(getB2Body());
}

Steven* Steven::sharedSteven()
{
	static Steven* pRet = NULL;
	if (!pRet)
	{
		pRet = Steven::create();
	}
	return pRet;
}


bool Steven::init()
{
	//physics
	CCPoint p = ccp(100,100);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x/G.PTM_RATIO, p.y/G.PTM_RATIO);
	bodyDef.fixedRotation = false;
	b2Body *body = b2Helper::createBody(&bodyDef, "steven");
	b2Helper::setUserData(body, this, "sprite");

	// Define another box shape for our dynamic body.
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = mRadius/G.PTM_RATIO;
	body->CreateFixture(&dynamicBox,1);

	//animation
	this->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("steven_ski_0.png"));
	this->setB2Body(body);
	this->setPTMRatio(G.PTM_RATIO);
	this->setPosition(p);
	this->scheduleUpdate();
	this->ski();
	return true;
}

void Steven::update( float delta )
{
	//keep speed 
	b2Body* body = getB2Body();
	b2Vec2 v = body->GetLinearVelocity();
	b2Vec2 impulse = skiSpeed(v);
	impulse *= body->GetMass();
	//b2Vec2 impulse = b2Vec2( (10 - v.x)*body->GetMass(), 0);
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter());

	////compute distance to hill
	b2Vec2 rayStart = this->m_pB2Body->GetWorldCenter();
	b2Vec2 rayEnd = b2Vec2(rayStart.x, rayStart.y - 100);
	class RayCastCallback : public b2RayCastCallback
	{
		virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
		{
			CCString* name = b2Helper::getBodyName(fixture->GetBody());
			if (name->compare("hill") == 0)
			{
				Steven* steven = Steven::sharedSteven();
				steven->mSkiHigh = (steven->m_pB2Body->GetWorldCenter().y - point.y) * G.PTM_RATIO - mRadius;
				return 0;
			}
			return 1;
		}
	} callback;
	G.world->RayCast(&callback,rayStart, rayEnd);

	//auto rotation in sky
	if (flying())
	{
		rotationBy(-30 * delta);
	}
	if (flying() && mStatus == StevenStatus::SS_Ski)
	{
		fly();
	}
}

void Steven::jump( float v_y )
{
	if (mStatus == StevenStatus::SS_Fall)
		return;

	b2Vec2 impules = b2Vec2(0, m_pB2Body->GetMass()* (v_y - m_pB2Body->GetLinearVelocity().y));
	m_pB2Body->ApplyLinearImpulse(impules, m_pB2Body->GetWorldCenter());
}

void Steven::rotationBy( float angle )
{
	float now = this->getRotation();
	setRotation(angle + this->getRotation());
}

bool Steven::flying()
{
	return mSkiHigh > 10;
}

void Steven::ski()
{
	if (this->mStatus == StevenStatus::SS_Ski)
		return;

	this->mStatus = StevenStatus::SS_Ski;
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("steven_ski");
	this->stopAllActions();
	this->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
}

void Steven::fall()
{
	this->mStatus = StevenStatus::SS_Fall;
	this->stopAllActions();
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("steven_pujie");
	CCAction* action = CCSequence::create(CCAnimate::create(animation), CCCallFunc::create(this, callfunc_selector(Steven::ski)), NULL);
	this->runAction(action);
}

void Steven::fly()
{
	this->mStatus = StevenStatus::SS_Fly;
	//this->stopAllActions();
}

b2Vec2 Steven::skiSpeed(b2Vec2 now)
{
	switch (mStatus)
	{
	case StevenStatus::SS_Fall:
		CCLOG("fall");
		return b2Vec2(0-now.x,0);
	case StevenStatus::SS_Ski:
		CCLOG("ski, %f", tanf(getRotation() *3.14 / 180) * 10.0f);
		return b2Vec2(10-now.x, tanf(getRotation() *3.14 / 180) * 10 - now.y);
	default:
		CCLOG("other");
		return b2Vec2(10 - now.x, 0);
	}
	
}














