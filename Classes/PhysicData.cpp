#include "PhysicData.h"

class PhysicDataAutoInit
{
public:
	PhysicDataAutoInit()
	{
		data = new PhysicData();
		data->initWithXml("hill/SnowHill_2.xml");
	}
	~PhysicDataAutoInit()
	{
		data->release();
	}
	PhysicData* data;
};

PhysicDataAutoInit physicDataAutoInit;

PhysicData* PhysicData::sharedPhysicData()
{
	return physicDataAutoInit.data;
}

void PhysicData::initWithXml( const char* filename )
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);
	for (const XMLNode* node = doc.FirstChild(); node;node = node->NextSibling())
	{
		PhysicDataScene* scene = new PhysicDataScene();
		scene->initWithXmlNode(node);
		this->setObject(scene, std::string(node->Value()));
		scene->release();
	}
}

void PhysicDataScene::initWithXmlNode( const XMLNode* scenenode )
{
	for (const XMLNode* node = scenenode->FirstChild(); node; node = node->NextSibling())
	{
		std::string tag(node->Value());
		PhysicDataObject* obj = PhysicDataObject::create(tag);
		obj->initWithXmlNode(node);
		this->addObject(obj);
		obj->release();
	}
}

PhysicDataObject* PhysicDataObject::create( const std::string& type )
{
	PhysicDataObject* pRet = NULL;
	if (type == "hill")
	{
		pRet = new PhysicDataHill();
	}
	else if (type == "tree")
	{
		pRet = new PhysicDataTree();
	}
	else if (type == "coin")
	{
		pRet = new PhysicDataCoin();
	}
	else
	{
		return NULL;
	}
	pRet->type = type;
	return pRet;
}

void PhysicDataTree::initWithXmlNode( const XMLNode* tree )
{
	const XMLElement* ele = tree->ToElement();
	for (const XMLAttribute* attr = ele->FirstAttribute(); attr; attr = attr->Next())
	{
		std::string tag(attr->Name());
		if (tag == "x")
		{
			this->pos.x = attr->FloatValue();
		}
		if (tag == "y")
		{
			this->pos.y = attr->FloatValue();
		}
		if (tag == "angle")
		{
			this->angle = attr->FloatValue();
		}
	}
}

void PhysicDataHill::initWithXmlNode( const XMLNode* hill )
{
	mHillModel.resize(0);
	for (const XMLNode* node=hill->FirstChild(); node; node = node->NextSibling())
	{
		Triangle tri; int count = 0;
		for (auto ele = node->FirstChildElement(); ele; ele = ele->NextSiblingElement())
		{
			float x=0; float y= 0;
			for (auto attr = ele->FirstAttribute(); attr; attr = attr->Next())
			{
				if (std::string(attr->Name()) == "x")
				{
					x = attr->FloatValue();
				}
				if (std::string(attr->Name()) == "y")
				{
					y = attr->FloatValue();
				}
			}
			tri.p[count].setPoint(x,y);
			if ( ++count == 3)
				break;
		}
		mHillModel.push_back(tri);
	}

	mStartPoint.x = 100000;
	mEndPoint.x = -100000;
	for (int i=0; i<mHillModel.size(); i++)
	{
		Triangle t = mHillModel[i];
		for (int i=0; i<3; i++)
		{
			if (t.p[i].x < mStartPoint.x)
				mStartPoint = t.p[i];
			if (t.p[i].x > mEndPoint.x)
				mEndPoint = t.p[i];
		}
	}
}

void PhysicDataCoin::initWithXmlNode( const XMLNode* coin )
{
	const XMLElement* ele = coin->ToElement();
	for (const XMLAttribute* attr = ele->FirstAttribute(); attr; attr = attr->Next())
	{
		std::string tag(attr->Name());
		if (tag == "x")
		{
			this->pos.x = attr->FloatValue();
		}
		if (tag == "y")
		{
			this->pos.y = attr->FloatValue();
		}
	}
}