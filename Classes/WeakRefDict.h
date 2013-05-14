#ifndef __WEAKREFDICT_H__
#define __WEAKREFDICT_H__

#include "cocos2d.h"
using namespace cocos2d;

class WeakRefDict : public CCObject
{
	typedef struct
	{
		CCObject* value;
		bool bWeak;
	} Value;
	typedef std::map<std::string, Value> Dict;
	
	Dict dict;
public:
	~WeakRefDict(void)
	{
		for (auto it=dict.begin(); it!=dict.end(); it++)
		{
			if (!it->second.bWeak)
			{
				it->second.value->release();
			}
		}
		dict.clear();
	}

	void setObject(CCObject* value, const std::string& key, bool bWeakRef = true)
	{
		auto it = dict.find(key);
		if( it != dict.end())
		{
			if (!it->second.bWeak)
			{
				it->second.value->release();
			}
			dict.erase(it);
		}

		Value _new;
		_new.value = value;
		_new.bWeak = bWeakRef;
		if (!_new.bWeak)
		{
			_new.value->retain();
		}
		dict.insert(std::pair<std::string, Value>(key, _new));
	}

	CCObject* objectForKey(const std::string& key)
	{
		auto it = dict.find(key);
		if (it == dict.end())
		{
			return NULL;
		}
		else
		{
			return it->second.value;
		}
	}

	void removeObjectForKey(const std::string& key)
	{
		auto it = dict.find(key);
		if (it == dict.end())
		{
			return;
		}
		else
		{
			if (!it->second.bWeak)
			{
				it->second.value->release();
			}
			dict.erase(it);
		}
	}

};

#endif // WEAKREFDICT_H__
