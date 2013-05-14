#ifndef __B2HELPER_H__
#define __B2HELPER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Global.h"
#include "WeakRefDict.h"
using namespace cocos2d;

class b2Helper
{
public:
	static b2Body* createBody(const b2BodyDef* def, std::string name)
	{
		WeakRefDict* dict = new WeakRefDict();
		b2Body* body = G.world->CreateBody(def); 
		body->SetUserData(dict);
		dict->setObject(CCString::create(name), "name", false);
		return body;
	}

	static void destroyBody(b2Body* body)
	{
		WeakRefDict* data = static_cast<WeakRefDict*>(body->GetUserData());
		CC_SAFE_RELEASE(data);
		G.world->DestroyBody(body);
	}

	static void setUserData(b2Body* body, CCObject* data, const std::string& key)
	{
		WeakRefDict* dict = static_cast<WeakRefDict*>(body->GetUserData());
		dict->setObject(data, key);
	}

	template <class T>
	static T* getUserData(b2Body* body, const std::string& name)
	{
		WeakRefDict* dict = static_cast<WeakRefDict*>(body->GetUserData());
		if (dict != NULL)
		{
			return dynamic_cast<T*>(dict->objectForKey(name));
		}
		return NULL;
	}

	static void removeUserData(b2Body* body, const std::string& name)
	{
		CCDictionary* dict = static_cast<CCDictionary*>(body->GetUserData());
		dict->removeObjectForKey(name);
	}

	static CCString* getBodyName(b2Body* body)
	{
		return getUserData<CCString>(body, "name");
	}
};

#endif // B2HELPER_H__
