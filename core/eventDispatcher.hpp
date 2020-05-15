#pragma once
#include "helpers\dynamicArray.hpp"
#include "shell\interactionShell.hpp"
#include "core\controlElement.hpp"
#include "shell\graphics.hpp"

const unsigned int eventDispatcherDelay = 10;

void eventDispatcherSend_Focus(dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		presentElementPtr->onFocusEvent.call(presentElementPtr);
	}
}
void eventDispatcherSend_LeftButtonClick(point clickedPos, dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		point presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		presentElementPtr->onClickEvent.call(presentElementPtr, presentElementClickPos);
	}
}
void eventDispatcherSend_RightButtonClick(point clickedPos, dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		point presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		presentElementPtr->onClickEvent.call(presentElementPtr, presentElementClickPos); //TOFIX
	}
}
void eventDispatcherMainLoop()
{
	while (true)
	{
		point mouseConsolePos = toPoint(getMouseConsolePos());
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