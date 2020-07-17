#pragma once
#include "core\controlElement.hpp"
#include "core\containerElement.hpp"
#include "shell\interactionShell.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"

unsigned int eventDispatcherDelay = 50;
bool needToDrawAll = true;

dynamicArray<controlElement*> elementsInFocus;
void Default_System_OnFocus(void* elementPtr, point clickedPos)
{
	elementsInFocus.add(static_cast<controlElement*>(elementPtr));
}

UserInputStruct prevDispatchUserInput;
point prevDispathConsoleSize = emptyPoint;
void eventDispatcherMainLoop()
{
	while (true)
	{
		//Get all user Actions
		UserInputStruct UserInput = getInput();
		point ConsoleSize = getPresentConsoleSize();
		UserActivityStruct UserActivity = getUserActivity(prevDispatchUserInput, UserInput, prevDispathConsoleSize, ConsoleSize);
		prevDispathConsoleSize = ConsoleSize;
		prevDispatchUserInput = UserInput;

		if (mainContainer->Handled)
		{
			//Focus events
			dynamicArray<controlElement*> prevElementsInFocus;
			prevElementsInFocus = elementsInFocus;
			elementsInFocus.clean();
			mainContainer->onFocus.call(mainContainer, UserInput.mouseConsolePos);
			for (int i = 0; i < prevElementsInFocus.count; i++)
			{
				if (elementsInFocus[i] != prevElementsInFocus[i] && prevElementsInFocus[i] != NULL)
				{
					prevElementsInFocus[i]->onFocusLost.call(prevElementsInFocus[i], UserInput.mouseConsolePos);
					break;
				}
			}

			//Keyboard events
			if (UserActivity.keyboardStateChanged)
			{
				if (UserInput.keyboardPress)
					mainContainer->onKeyDown.call(mainContainer, UserInput.keyboardPressedKey);
				else
					mainContainer->onKeyUp.call(mainContainer, UserInput.keyboardPressedKey);
			}

			//Mouse events
			if (UserActivity.mouseLeftButtonStateChanged)
			{
				if (UserInput.mouseLeftPressed)
				{
					mainContainer->onClick.call(mainContainer, UserInput.mouseConsolePos);
					mainContainer->onLeftButtonDown.call(mainContainer, UserInput.mouseConsolePos);
				}
				else {
					mainContainer->onLeftButtonUp.call(mainContainer, UserInput.mouseConsolePos);
				}
			}
			if (UserActivity.mouseRightButtonStateChanged)
			{
				if (UserInput.mouseRightPressed)
				{
					mainContainer->onClick.call(mainContainer, UserInput.mouseConsolePos);
					mainContainer->onRightButtonDown.call(mainContainer, UserInput.mouseConsolePos);
				}
				else {
					mainContainer->onRightButtonUp.call(mainContainer, UserInput.mouseConsolePos);
				}
			}
		}

		//Output
		if (UserActivity.consoleWindowResized)
		{
			rectangle consoleSizeRect = { {0,0}, ConsoleSize };
			consoleErase(consoleSizeRect);

			mainContainer->setSize(ConsoleSize);
			needToDrawAll = true;
		}

		mainContainer->beforeDraw.call(mainContainer);
		if (needToDrawAll)
		{
			drawAllElements();
			elementsToRedraw.clean();
			needToDrawAll = false;
		}
		else
			redrawAllElements();
		mainContainer->afterDraw.call(mainContainer);

#ifdef SHOW_MOUSE
		showCursor(toPoint(getMouseConsolePos()));
#endif

		Sleep(eventDispatcherDelay);
	}
}