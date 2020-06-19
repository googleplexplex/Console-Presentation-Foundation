#include <iostream>
#include "include.hpp"
using namespace std;

int main(void)
{
	Grid mainCont;
	mainCont.setRowsColumnsCount(5, 5);
	mainCont.setWidth(2, 2);
	mainCont.ShowGridLines = true;
	setMainContainer(mainCont);

	//...

	eventDispatcherMainLoop();

	return 0;
}