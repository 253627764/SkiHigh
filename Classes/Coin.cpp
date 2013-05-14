#include "Coin.h"
#include "b2Helper.h"


Coin::Coin(void)
{
}


Coin::~Coin(void)
{
	b2Helper::destroyBody(getB2Body());
}

bool Coin::init()
{
	initWithFile("item\\coin.png");
	return true;
}

Coin* Coin::create( CCPoint pos )
{
	Coin* pRet = Coin::create();
	if (pRet != NULL)
	{
		//physics
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position = b2Vec2(pos.x/G.PTM_RATIO, pos.y/G.PTM_RATIO);
		b2Body* body = b2Helper::createBody(&bodyDef, "coin");
		b2Helper::setUserData(body, pRet, "sprite");

		b2CircleShape shape;
		shape.m_radius = 16 / G.PTM_RATIO;

		b2FixtureDef fix;		fix.density = 1;		fix.isSensor = true;		fix.shape = &shape;
		body->CreateFixture(&fix);

		//animation
		pRet->setB2Body(body);
		pRet->setPTMRatio(G.PTM_RATIO);
		pRet->setPosition(pos);
	}
	return pRet;
}
