#ifndef __PHYSICDATA_H__
#define __PHYSICDATA_H__
#include "cocos2d.h"
#include "tinyxml2.h"
using namespace cocos2d;
using namespace tinyxml2;

class PhysicData : public CCDictionary
{
public:
	static PhysicData* sharedPhysicData();
	void initWithXml(const char* filename);
};

class PhysicDataScene : public CCArray
{
public:
	void initWithXmlNode(const XMLNode* node);
};

class PhysicDataHill;
class PhysicDataTree;
class PhysicDataObject : public CCObject
{
protected:
	std::string type;
protected:
	PhysicDataObject(){}

public:
	static PhysicDataObject* create(const std::string& type);
	const std::string& Type() {return type;}
	virtual void initWithXmlNode(const XMLNode* node) = 0;
};

struct Triangle
{
	CCPoint p[3];
};

class PhysicDataHill : public PhysicDataObject
{
public:
	PhysicDataHill(){}
	virtual void initWithXmlNode(const XMLNode* node);

	std::vector<Triangle> mHillModel;
	CCPoint mStartPoint;
	CCPoint mEndPoint;
};

class PhysicDataTree : public PhysicDataObject
{
public:
	PhysicDataTree(){}
	virtual void initWithXmlNode(const XMLNode* node);
	
	CCPoint pos;
	float angle;
};

class PhysicDataCoin : public PhysicDataObject
{
public:
	PhysicDataCoin(){}
	virtual void initWithXmlNode(const XMLNode* node);
	CCPoint pos;
};

#endif // PHYSICDATA_H__