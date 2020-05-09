#include <iostream>
#include <windows.h>
//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//HWND  consoleHWND = (HWND)consoleHandle;
HWND consoleHWND = GetConsoleWindow();
HANDLE consoleHandle = (HANDLE)consoleHandle;
HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND stdHWND = (HWND)stdHandle;
#include "buttons.hpp"
#include "label.hpp"
#include "interactionShell.hpp"
#include "eventDispatcher.hpp"
using namespace std;

#define printBool(x) (x)?printf("true "):printf("false")

int clickCount = 0;
void onButtonClicked(void* obj, POINT clickedPos)
{
	clickCount++;
}

void onMyButtonClicked(void* objPtr, POINT clickedPos);
class myButton : public button
{
public:
	unsigned int clicksCount = 0;
	myButton(POINT _pos, POINT _size, char* _text = (char*)"Button", symbolColor _textColor = white, symbolColor _foneColor = black, symbolColor _frameColor = null)
		: button(_pos, _size, _text, &onMyButtonClicked, _textColor, _foneColor, _frameColor) {}
};
void onMyButtonClicked(void* objPtr, POINT clickedPos)
{
	myButton* obj = (myButton*)(objPtr);
	obj->clicksCount++;
}

int main(void)
{
	label testLabel({ 1, 1 });
	testLabel.Draw();

	eventDispatcherMainLoop();

	return 0;
}