#pragma once
#include "helpers\dynamicArray.hpp"
#include "shell\interactionShell.hpp"
#include "core\controlElement.hpp"

const unsigned int eventDispatcherDelay = 10;

void eventDispatcher_LeftButtonClick(POINT clickedPos)
{
	dynamicArray<controlElement*> controlElementsInClickedPos = getControlElementIn(clickedPos);

	for (int i = 0; i < controlElementsInClickedPos.count; i++)
	{
		controlElement* presentElementPtr = getControlElement(i);
		POINT presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		presentElementPtr->click(presentElementClickPos);
	}
}
void eventDispatcher_RightButtonClick(POINT clickedPos)
{
	dynamicArray<controlElement*> controlElementsInClickedPos = getControlElementIn(clickedPos);

	for (int i = 0; i < controlElementsInClickedPos.count; i++)
	{
		controlElement* presentElementPtr = getControlElement(i);
		presentElementPtr->click(clickedPos);
	}
}
void eventDispatcherMainLoop()
{
	while (true)
	{
		if (mouseLeftButtonState)
		{
			POINT mouseConsolePos = getMouseConsolePos();
			eventDispatcher_LeftButtonClick(mouseConsolePos);
		}
		if (mouseRightButtonState)
		{
			POINT mouseConsolePos = getMouseConsolePos();
			eventDispatcher_RightButtonClick(mouseConsolePos);
		}

		system("cls");
		showCursor();
		drawAllElements();
		Sleep(eventDispatcherDelay);
	}
}