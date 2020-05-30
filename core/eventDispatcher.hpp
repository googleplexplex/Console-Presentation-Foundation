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
		//Get I/O
		point mouseConsolePos = toPoint(getMouseConsolePos());
		char keyboardPressedKey = 0;
		bool keyboardPress = keyboardHit();
		if (keyboardPress)
			keyboardPressedKey = getInputedChar();

		//Focus events
		dynamicArray<controlElement*> prevElementsInFocus;
		prevElementsInFocus = elementsInFocus;
		elementsInFocus.clean();
		callDelegate<void*, point>(mainContainer->onFocusSystemDelegate, mainContainer, mouseConsolePos);
		for (int i = 0; i < prevElementsInFocus.count; i++)
		{
			if (elementsInFocus[i] != prevElementsInFocus[i] && prevElementsInFocus[i] != NULL)
			{
				callDelegate<void*, point>(prevElementsInFocus[i]->onFocusLostSystemDelegate, prevElementsInFocus[i], mouseConsolePos);
				break;
			}
		}

		//Keyboard events
		if (keyboardPress)
		{
			callDelegate<void*, char>(mainContainer->onKeyDownSystemDelegate, mainContainer, keyboardPressedKey);
		}

		//Mouse events
		if (mouseLeftButtonState)
		{
			callDelegate<void*, point>(mainContainer->onClickSystemDelegate, mainContainer, mouseConsolePos);
			callDelegate<void*, point>(mainContainer->onLeftButtonDownSystemDelegate, mainContainer, mouseConsolePos);
		}
		if (mouseRightButtonState)
		{
			callDelegate<void*, point>(mainContainer->onRightButtonDownSystemDelegate, mainContainer, mouseConsolePos);
		}

		//Pain events
		consoleClearAll();
		//consoleClearElements(consoleSizeRectangle());
		showCursor(consoleSizeRectangle(), toPoint(getMouseConsolePos()));
		drawAllElements();
		Sleep(eventDispatcherDelay);
	}
}