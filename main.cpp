#include <iostream>
#define SHOW_MOUSE
#include "include.hpp"
using namespace std;

int main(void)
{
	Grid mainCont(4, 5, true);
	mainCont.setWidth(2, 2);
	mainCont.setAsMainContainer();

	TextBox testTextBox((char*)"hi", 512, false, blue, red);
	testTextBox.setParent(&mainCont);

	eventDispatcherMainLoop();

	return 0;
}