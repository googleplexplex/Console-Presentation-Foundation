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

	TextBox testTextBox({ 0,0 }, { 5, 5 }, (char*)"TextBox", blue, red);
	testTextBox.setParent(&mainCont);

	eventDispatcherMainLoop();

	return 0;
}