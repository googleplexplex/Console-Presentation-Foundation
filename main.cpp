#include <iostream>
#include "include.hpp"
using namespace std;

int main(void)
{
	Grid mainCont(5, 5, true);
	mainCont.setWidth(2, 2);
	mainCont.setAsMainContainer();

	//...

	eventDispatcherMainLoop();

	return 0;
}