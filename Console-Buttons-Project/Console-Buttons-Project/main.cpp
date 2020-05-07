#include <iostream>
#include <windows.h>
//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//HWND  consoleHWND = (HWND)consoleHandle;
HWND consoleHWND = GetConsoleWindow();
HANDLE consoleHandle = (HANDLE)consoleHandle;
HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND stdHWND = (HWND)stdHandle;
#include "buttons.hpp"
#define DEBUG
#include "interactionShell.hpp"
#include "eventDispatcher.hpp"
using namespace std;

#define printBool(x) (x)?printf("true "):printf("false")

int clickCount = 0;
void onButtonClicked(POINT clickedPos)
{
	//cout << "Click was in " << clickedPos.x << " " << clickedPos.y << endl;
	clickCount++;
}

int main(void)
{

	button buttonTest({ 1, 1 }, { 3, 3 }, &onButtonClicked, (char*)"Bton", blue, red);
	buttonTest.Draw();

	eventDispatcherMainLoop();

	return 0;
}