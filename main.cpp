#include <iostream>
#include "include.hpp"
using namespace std;


int main(void)
{
	TextBlock test1({ 20, 1 });
	test1.setText("aa1");

	ListBox test2({ 1, 1 }, 15, 5, white, red);
	test2.addItem("Item1");
	test2.addItem("Item2");
	test2.addItem("Item3");

	eventDispatcherMainLoop();

	return 0;
}