#include <iostream>
#include "include.hpp"
using namespace std;

int main(void)
{
	UniformGrid mainCont({ 0, 0 }, { 0, 0 }, black);
	mainCont.setRowsColumnsCount(3, 3);
	setMainContainer(mainCont);

	TextBlock testTextBlock({ 0, 0 }, (char*)"TB1");
	testTextBlock.setText("TxtBlc1");
	mainCont.addChild(testTextBlock);

	TextBox testTextBox({ 0, 0 }, { 5, 5 }, (char*)"TextBox", blue, red);
	testTextBox.ReadOnly = true;
	mainCont.addChild(testTextBox);

	eventDispatcherMainLoop();

	return 0;
}