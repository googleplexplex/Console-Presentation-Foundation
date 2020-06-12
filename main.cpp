#include <iostream>
#include "include.hpp"
using namespace std;

int main(void)
{
	UniformGrid mainCont({ 0, 0 }, { 0, 0 }, black);
	mainCont.setRowsColumnsCount(3, 3);
	setMainContainer(mainCont);

	TextBlock testTextBock({ 0, 0 }, (char*)"TB1");
	testTextBock.setText("TxtBlc1");
	testTextBock.setParent(&mainCont);

	TextBox testTextBox({ 0, 0 }, { 5, 5 }, (char*)"TextBox", blue, red);
	testTextBox.ReadOnly = true;
	testTextBox.setParent(&mainCont);

	eventDispatcherMainLoop();

	return 0;
}