#include "DoItLater.h"

DoItLater::DoItLater(void)
{
}


DoItLater::~DoItLater(void)
{
	what_to_do();
}

void DoItLater::create( boost::function<void()> what_to_do )
{
	DoItLater* instanse = new DoItLater();
	instanse->what_to_do = what_to_do;
	instanse->autorelease();
}
