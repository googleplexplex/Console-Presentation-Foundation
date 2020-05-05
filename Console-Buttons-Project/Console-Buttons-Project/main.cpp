#include <iostream>
#include "buttons.hpp"
using namespace std;

#define printBool(x) (x)?printf("true "):printf("false")

void onLeftButtonClick(POINT pos)
{
	return;
}
void onRightButtonClick(POINT pos)
{
	return;
}

void onButtonPressed(POINT clickedPos)
{
	cout << "Click was in " << clickedPos.x << " " << clickedPos.y << endl;
}

int main(void)
{
	buttonPress buttonTest({ 1, 1 }, { 3, 3 }, &onButtonPressed, (char*)"Button", blue, red, blue);
	buttonTest.Draw();

	return 0;
}