#pragma once
#include "dynamicArray.hpp"
#include "interactionShell.hpp"
#include "controlElement.hpp"

void eventDispatcher_LeftButtonClick(POINT clickedPos)
{
	dynamicArray<controlElement*> controlElementsInClickedPos = getControlElementIn(clickedPos);

	for (int i = 0; i < controlElementsInClickedPos.count; i++)
	{
		controlElement* presentElementPtr = getControlElement(i);
		presentElementPtr->onClick_Delegate(clickedPos);
	}
}
void eventDispatcher_RightButtonClick(POINT clickedPos)
{
	dynamicArray<controlElement*> controlElementsInClickedPos = getControlElementIn(clickedPos);

	for (int i = 0; i < controlElementsInClickedPos.count; i++)
	{
		controlElement* presentElementPtr = getControlElement(i);
		presentElementPtr->onClick_Delegate(clickedPos);
	}
}
void eventDispatcherMainLoop()
{
	while (true)
	{
		if (mouseLeftButtonState)
			eventDispatcher_LeftButtonClick(getMouseGlobalPos());
		if (mouseRightButtonState)
			eventDispatcher_RightButtonClick(getMouseGlobalPos());
	}
}