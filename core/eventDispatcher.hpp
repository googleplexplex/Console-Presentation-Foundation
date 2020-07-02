#pragma once
#include "core\controlElement.hpp"
#include "core\containerElement.hpp"
#include "shell\interactionShell.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"

const unsigned int eventDispatcherDelay = 50;

dynamicArray<controlElement*> elementsInFocus;
void Default_System_OnFocus(void* elementPtr, point clickedPos)
{
	elementsInFocus.add(static_cast<controlElement*>(elementPtr));
}

UserInputStruct prevDispatchUserIO;
void eventDispatcherMainLoop()
{
	while (true)
	{
		//Get all user Actions
		UserInputStruct UserInput;
		UserInput.getIO();
		UserActivityStruct UserActivity = getUserActivity(prevDispatchUserIO, UserInput);

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
#ifdef SHOW_MOUSE
		showCursor(consoleSizeRectangle(), toPoint(getMouseConsolePos()));
#endif
		mainContainer->beforeDraw.call(mainContainer);
		drawAllElements();
		mainContainer->afterDraw.call(mainContainer);

		Sleep(eventDispatcherDelay);
	}
}