#include <iostream>
#include "include.hpp"
using namespace std;

int main(void)
{
	StackPanel mainCont({ 0, 0 }, { 15, 15 }, Horizontal);
	setMainContainer(&mainCont);

	TextBlock testTextBock({ 0, 0 }, (char*)"TB1");
	testTextBock.setText("TxtBlc1");
	testTextBock.setParent(&mainCont);

	Button testButton({ 0, 0 }, { 5, 15 }, (char*)"TestB", NULL, blue, red);
	testButton.setParent(&mainCont);

	eventDispatcherMainLoop();

	return 0;
}