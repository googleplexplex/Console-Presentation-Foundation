#include <iostream>
#include "include.hpp"
using namespace std;

int main(void)
{
	StackPanel mainCont({ 0, 0 }, { 15, 15 }, Horizontal);
	setMainContainer(&mainCont);

	StackPanel firstVerticalCont({ 0, 0 }, { 15, 15 }, Vertical, red);
	firstVerticalCont.setParent(&mainCont);

	StackPanel secondVerticalCont({ 0, 0 }, { 15, 15 }, Vertical, blue);
	secondVerticalCont.setParent(&mainCont);

	Button testButton1({ 0, 0 }, { 5, 15 }, (char*)"TestButton");
	testButton1.setParent(&firstVerticalCont);

	eventDispatcherMainLoop();

	return 0;
}