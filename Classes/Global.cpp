#include "Global.h"
#include "StevenContactListener.h"

Global G;




Global::Global()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	world->SetContactListener(&contact);
}

Global::~Global()
{
	delete world;
}
