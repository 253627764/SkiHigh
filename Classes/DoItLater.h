#ifndef __DOITLATER_H__
#define __DOITLATER_H__

#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "cocos2d.h"
using namespace cocos2d;

class DoItLater : public CCObject
{
	boost::function<void()> what_to_do;
private:
	DoItLater(void);
	~DoItLater(void);

public:
	static void create(boost::function<void()> what_to_do);
};

#endif // DOITLATER_H__
