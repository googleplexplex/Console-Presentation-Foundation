#include <iostream>
#include "include.hpp"
using namespace std;


int main(void)
{
	ListBox test({ 1, 1 }, 15, 5, white, red);
	test.addItem((char*)"Item1");
	test.addItem((char*)"Item2");
	test.addItem((char*)"Item3");

	eventDispatcherMainLoop();

	return 0;
}