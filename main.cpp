#include <iostream>
#include "include.hpp"
using namespace std;

int main(void)
{
	Grid mainCont(5, 5);
	mainCont.setWidth(2, 2);
	mainCont.setAsMainContainer();

	TextBox testTextBox((char*)"hi", 512, false, blue, red);
	testTextBox.setParent(&mainCont);

	eventDispatcherMainLoop();

	return 0;
}