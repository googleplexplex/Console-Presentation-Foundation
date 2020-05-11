#include <iostream>
#include <windows.h>
//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//HWND  consoleHWND = (HWND)consoleHandle;
HWND consoleHWND = GetConsoleWindow();
HANDLE consoleHandle = (HANDLE)consoleHandle;
HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND stdHWND = (HWND)stdHandle;
#include "elements\Button.hpp"
#include "elements\ListBox.hpp"
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

int main(void)
{
	ListBox testLabel({ 1, 1 }, 10, 5);

	testLabel.Draw();
	testLabel.addItem((char*)"Item1");
	testLabel.Draw();
	testLabel.addItem((char*)"Item2");
	testLabel.Draw();
	testLabel.addItem((char*)"Item3");
	testLabel.Draw();

	eventDispatcherMainLoop();

	return 0;
}