#include "StevenContactListener.h"
#include <math.h>
#include "b2Helper.h"
#include "Steven.h"
#include "Scene.h"
#include "SkiHighLayer.h"
#include "DoItLater.h"


void StevenContactListener::BeginContact( b2Contact* contact)
{
	b2ContactListener::BeginContact(contact);
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	b2Body* steven;
	b2Body* other;
	if (b2Helper::getBodyName(bodyA)->compare("steven") == 0)
	{
		steven = bodyA;
		other = bodyB;
	}
	else if (b2Helper::getBodyName(bodyB)->compare("steven") == 0)
	{
		steven = bodyB;
		other = bodyA;
	}
	else
	{
		return;
	}

	if (b2Helper::getBodyName(other)->compare("hill") == 0)
	{
		stevenContactHill(steven, other, contact);
	}

	if (b2Helper::getBodyName(other)->compare("coin") == 0)
	{
		stevenContactCoin(steven, other, contact);
	}

}

void StevenContactListener::stevenContactHill(b2Body* steven, b2Body* hill, const b2Contact* contact )
{
	b2WorldManifold manifold;	
	Steven* stevenSprite = Steven::sharedSteven();
	contact->GetWorldManifold(&manifold);
	float right = - asinf(manifold.normal.x) * 180 / 3.14;
	float now = stevenSprite->getRotation();

	//judge if landing success
	//stevenSprite->setRotation(right);
	DoItLater::create(boost::bind(&Steven::setRotation, stevenSprite, right));
	if (fabs(right - now) > 45)
	{
		stevenSprite->fall();
	}
	else
	{
		stevenSprite->ski();
	}
}

void StevenContactListener::stevenContactCoin(b2Body* steven, b2Body* coin, const b2Contact* contact )
{
	CCPhysicsSprite* sprite = b2Helper::getUserData<CCPhysicsSprite>(coin, "sprite");
	SkiHighLayer* layer = SkiHighLayer::sharedSkiHighLayer();
	DoItLater::create(boost::bind(&SkiHighLayer::removeChild, layer, sprite));
}
