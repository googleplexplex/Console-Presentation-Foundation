#include <iostream>
#include "include.hpp"
using namespace std;

int main(void)
{
	UniformGrid mainCont({ 0, 0 }, { 0, 0 }, black);
	mainCont.setRowsColumnsCount(3, 3);
	mainCont.setHeight(0, 2);
	setMainContainer(mainCont);

	TextBlock testTextBlock({ 0, 0 }, (char*)"TB1");
	testTextBlock.setText("TxtBlc1");
	mainCont.addControlElement(testTextBlock, 0, 0);

	TextBox testTextBox({ 0, 0 }, { 5, 5 }, (char*)"TextBox", blue, red);
	testTextBox.ReadOnly = true;
	mainCont.addControlElement(testTextBox, 0, 1);

	eventDispatcherMainLoop();

	return 0;
}