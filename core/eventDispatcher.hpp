#pragma once
#include "core\controlElement.hpp"
#include "core\containerElement.hpp"
#include "shell\interactionShell.hpp"
#include "helpers\dynamicArray.hpp"

const unsigned int eventDispatcherDelay = 50;


void eventDispatcherMainLoop()
{
	while (true)
	{
		point mouseConsolePos = toPoint(getMouseConsolePos());

		callDelegate(mainContainer->onFocusSystemDelegate, mainContainer, mouseConsolePos);
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