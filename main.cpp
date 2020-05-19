#include <iostream>
#include "include.hpp"
using namespace std;


int main(void)
{
	Canvas mainCont({ 0, 0 }, { 15, 15 });
	setMainContainer((controlElement*)&mainCont);


	TextBlock test1({ 20, 1 });
	test1.setText("aa1");
	test1.setParent((controlElement*)&mainCont);

	ListBox test2({ 1, 1 }, 15, 5, white, red);
	test2.addItem("Item1");
	test2.addItem("Item2");
	test2.addItem("Item3");
	test2.setParent((controlElement*)&mainCont);

	eventDispatcherMainLoop();

	return 0;
}