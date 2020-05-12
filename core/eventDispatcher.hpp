#pragma once
#include "helpers\dynamicArray.hpp"
#include "shell\interactionShell.hpp"
#include "core\controlElement.hpp"

const unsigned int eventDispatcherDelay = 10;

void eventDispatcherSend_Focus(dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		presentElementPtr->onFocus_Delegate(presentElementPtr);
	}
}
void eventDispatcherSend_LeftButtonClick(POINT clickedPos, dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		POINT presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		presentElementPtr->onClick_Delegate(presentElementPtr, presentElementClickPos);
	}
}
void eventDispatcherSend_RightButtonClick(POINT clickedPos, dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		POINT presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		presentElementPtr->onClick_Delegate(presentElementPtr, presentElementClickPos); //TOFIX
	}
}
void eventDispatcherMainLoop()
{
	while (true)
	{
		POINT mouseConsolePos = getMouseConsolePos();
		dynamicArray<controlElement*> controlElementsInClickedPos = getControlElementIn(mouseConsolePos);

		eventDispatcherSend_Focus(controlElementsInClickedPos);
		if (mouseLeftButtonState)
			eventDispatcherSend_LeftButtonClick(mouseConsolePos, controlElementsInClickedPos);
		if (mouseRightButtonState)
			eventDispatcherSend_RightButtonClick(mouseConsolePos, controlElementsInClickedPos);

		ConsoleClear();
		showCursor();
		drawAllElements();
		Sleep(eventDispatcherDelay);
	}
}