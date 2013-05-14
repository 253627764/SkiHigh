#ifndef __STEVENCONTACTLISTENER_H__
#define __STEVENCONTACTLISTENER_H__

#include "Box2d/Box2D.h"

class StevenContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	

private:
	void stevenContactHill(b2Body* steven, b2Body* hill, const b2Contact* contact );
	void stevenContactCoin(b2Body* steven, b2Body* coin, const b2Contact* contact );
};

#endif // STEVENCONTACTLISTENER_H__
