#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "Box2D/Box2D.h"
#include "StevenContactListener.h"

class Global
{
public:
	Global();
	~Global();
	static const int PTM_RATIO = 32;
	b2World* world;

private:
	StevenContactListener contact;

};

extern Global G;

#endif // GLOBAL_H__

