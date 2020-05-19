#pragma once
#include "core\controlElement.hpp"
#include "shell\interactionShell.hpp"
#include "helpers\dynamicArray.hpp"

const unsigned int eventDispatcherDelay = 50;


void eventDispatcherMainLoop()
{
	while (true)
	{
		point mouseConsolePos = toPoint(getMouseConsolePos());

		callDelegate(mainContainer->onFocusSystemDelegate, mainContainer);
		if (mouseLeftButtonState)
		{
			callDelegate(mainContainer->onClickSystemDelegate, mainContainer, mouseConsolePos);
			callDelegate(mainContainer->onLeftButtonDownSystemDelegate, mainContainer, mouseConsolePos);
		}
		if (mouseRightButtonState)
		{
			callDelegate(mainContainer->onRightButtonDownSystemDelegate, mainContainer, mouseConsolePos);
		}

		//consoleClearElements();
		consoleClearAll();
		showCursor(consoleSizeRectangle(), toPoint(getMouseConsolePos()));
		drawAllElements();
		Sleep(eventDispatcherDelay);
	}
}