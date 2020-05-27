#pragma once
#include "core\controlElement.hpp"
#include "core\containerElement.hpp"
#include "shell\interactionShell.hpp"
#include "helpers\dynamicArray.hpp"

const unsigned int eventDispatcherDelay = 50;

dynamicArray<controlElement*> elementsInFocus;
void Default_System_OnFocus(void* elementPtr, point clickedPos)
{
	elementsInFocus.add((controlElement*)elementPtr);
}

void eventDispatcherMainLoop()
{
	while (true)
	{
		point mouseConsolePos = toPoint(getMouseConsolePos());

		dynamicArray<controlElement*> prevElementsInFocus;
		prevElementsInFocus.getCopyOf(elementsInFocus); //Operator

		elementsInFocus.clean();
		callDelegate(mainContainer->onFocusSystemDelegate, mainContainer, mouseConsolePos);
		for (int i = 0; i < prevElementsInFocus.count; i++)
		{
			if (elementsInFocus[i] != prevElementsInFocus[i] && prevElementsInFocus[i] != NULL)
			{
				callDelegate(prevElementsInFocus[i]->onFocusLostSystemDelegate, prevElementsInFocus[i], mouseConsolePos);
				break;
			}
		}

		if (mouseLeftButtonState)
		{
			callDelegate(mainContainer->onClickSystemDelegate, mainContainer, mouseConsolePos);
			callDelegate(mainContainer->onLeftButtonDownSystemDelegate, mainContainer, mouseConsolePos);
		}
		if (mouseRightButtonState)
		{
			callDelegate(mainContainer->onRightButtonDownSystemDelegate, mainContainer, mouseConsolePos);
		}

		consoleClearAll();
		//consoleClearElements(consoleSizeRectangle());
		showCursor(consoleSizeRectangle(), toPoint(getMouseConsolePos()));
		drawAllElements();
		Sleep(eventDispatcherDelay);
	}
}