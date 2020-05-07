#include <iostream>
#include <windows.h>
//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//HWND  consoleHWND = (HWND)consoleHandle;
HWND consoleHWND = GetConsoleWindow();
HANDLE consoleHandle = (HANDLE)consoleHandle;
HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND stdHWND = (HWND)stdHandle;
#include "buttons.hpp"
#include "interactionShell.hpp"
using namespace std;

#define printBool(x) (x)?printf("true "):printf("false")

void onButtonClicked(POINT clickedPos)
{
	cout << "Click was in " << clickedPos.x << " " << clickedPos.y << endl;
}

int main(void)
{
	button buttonTest({ 1, 1 }, { 3, 3 }, &onButtonClicked, (char*)"Bton", blue, red);
	buttonTest.Draw();

	return 0;
}