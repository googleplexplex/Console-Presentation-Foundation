#include <iostream>
#include "include.hpp"
using namespace std;

void onMyButtonClicked(void* objPtr, point clickedPos);
class myButton : public Button
{
public:
	unsigned int clicksCount = 0;
	myButton(point _pos, point _size, char* _text = (char*)"Button", symbolColor _textColor = white, symbolColor _foneColor = black, symbolColor _frameColor = null)
		: Button(_pos, _size, _text, &onMyButtonClicked, _textColor, _foneColor, _frameColor) {}
};
void onMyButtonClicked(void* objPtr, point clickedPos)
{
	myButton* obj = (myButton*)(objPtr);
	obj->clicksCount++;
}


int main(void)
{
	ListBox test({ 1, 1 }, 15, 5);
	test.addItem((char*)"Item1");
	test.addItem((char*)"Item2");
	test.addItem((char*)"Item3");

	eventDispatcherMainLoop();

	return 0;
}