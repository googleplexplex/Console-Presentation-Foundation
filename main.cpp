#include <iostream>
#include <windows.h>
//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//HWND  consoleHWND = (HWND)consoleHandle;
HWND consoleHWND = GetConsoleWindow();
HANDLE consoleHandle = (HANDLE)consoleHandle;
HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND stdHWND = (HWND)stdHandle;
#include "core\event.hpp"
#include "elements\Button.hpp"
#include "elements\CheckBox.hpp"
#include "core\EventDispatcher.hpp"
using namespace std;

void onMyButtonClicked(void* objPtr, POINT clickedPos);
class myButton : public Button
{
public:
	unsigned int clicksCount = 0;
	myButton(POINT _pos, POINT _size, char* _text = (char*)"Button", symbolColor _textColor = white, symbolColor _foneColor = black, symbolColor _frameColor = null)
		: Button(_pos, _size, _text, &onMyButtonClicked, _textColor, _foneColor, _frameColor) {}
};
void onMyButtonClicked(void* objPtr, POINT clickedPos)
{
	myButton* obj = (myButton*)(objPtr);
	obj->clicksCount++;
}

void testFunc1(int arg)
{
	return;
}
void testFunc2(int arg)
{
	return;
}
void testFunc3(int arg)
{
	return;
}

int main(void)
{
	event<int> eventTest;
	eventTest += eventTest;

	eventDispatcherMainLoop();

	return 0;
}