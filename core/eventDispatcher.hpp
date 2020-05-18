#pragma once
#include "core\controlElement.hpp"
#include "shell\interactionShell.hpp"
#include "helpers\dynamicArray.hpp"

const unsigned int eventDispatcherDelay = 50;

void eventDispatcherSend_Focus(dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		callDelegate(presentElementPtr->onFocusSystemDelegate, presentElementPtr);
		presentElementPtr->onFocusEvent.call(presentElementPtr);
	}
}
void eventDispatcherSend_FocusLost(dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		callDelegate(presentElementPtr->onFocusSystemDelegate, presentElementPtr);
		presentElementPtr->onFocusLostEvent.call(presentElementPtr);
	}
}
void eventDispatcherSend_Click(point clickedPos, dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		point presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		callDelegate(presentElementPtr->onClickSystemDelegate, presentElementPtr, presentElementClickPos);
		presentElementPtr->onClickEvent.call(presentElementPtr, presentElementClickPos);
	}
}
void eventDispatcherSend_LeftButtonDown(point clickedPos, dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		point presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		callDelegate(presentElementPtr->onLeftButtonDownSystemDelegate, presentElementPtr, presentElementClickPos);
		presentElementPtr->onLeftButtonDownEvent.call(presentElementPtr, presentElementClickPos);
	}
}
void eventDispatcherSend_LeftButtonUp(point clickedPos, dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		point presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		callDelegate(presentElementPtr->onLeftButtonUpSystemDelegate, presentElementPtr, presentElementClickPos);
		presentElementPtr->onLeftButtonUpEvent.call(presentElementPtr, presentElementClickPos);
	}
}
void eventDispatcherSend_RightButtonDown(point clickedPos, dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		point presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		callDelegate(presentElementPtr->onRightButtonDownSystemDelegate, presentElementPtr, presentElementClickPos); //TODO
		presentElementPtr->onRightButtonDownEvent.call(presentElementPtr, presentElementClickPos);
	}
}
void eventDispatcherSend_RightButtonUp(point clickedPos, dynamicArray<controlElement*>& elements)
{
	for (int i = 0; i < elements.count; i++)
	{
		controlElement* presentElementPtr = (controlElement*)elements[i];
		point presentElementClickPos = { clickedPos.x - presentElementPtr->pos.x, clickedPos.y - presentElementPtr->pos.y };
		callDelegate(presentElementPtr->onRightButtonUpSystemDelegate, presentElementPtr, presentElementClickPos); //TODO
		presentElementPtr->onRightButtonUpEvent.call(presentElementPtr, presentElementClickPos);
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
		{
			eventDispatcherSend_Click(mouseConsolePos, controlElementsInClickedPos);
			eventDispatcherSend_LeftButtonDown(mouseConsolePos, controlElementsInClickedPos);
		}
		if (mouseRightButtonState)
		{
			eventDispatcherSend_RightButtonDown(mouseConsolePos, controlElementsInClickedPos);
		}

		//consoleClearElements();
		consoleClearAll();
		showCursor(toPoint(getMouseConsolePos()));
		drawAllElements();
		Sleep(eventDispatcherDelay);
	}
}