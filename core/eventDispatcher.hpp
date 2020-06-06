#pragma once
#include "core\controlElement.hpp"
#include "core\containerElement.hpp"
#include "shell\interactionShell.hpp"
#include "helpers\dynamicArray.hpp"

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
			callDelegate<void*, point>(mainContainer->onFocusSystemDelegate, mainContainer, UserInput.mouseConsolePos);
			for (int i = 0; i < prevElementsInFocus.count; i++)
			{
				if (elementsInFocus[i] != prevElementsInFocus[i] && prevElementsInFocus[i] != NULL)
				{
					callDelegate<void*, point>(prevElementsInFocus[i]->onFocusLostSystemDelegate, prevElementsInFocus[i], UserInput.mouseConsolePos);
					break;
				}
			}

			//Keyboard events
			if (UserActivity.keyboardStateChanged)
			{
				if (UserInput.keyboardPress)
					callDelegate<void*, char>(mainContainer->onKeyDownSystemDelegate, mainContainer, UserInput.keyboardPressedKey);
				else
					callDelegate<void*, char>(mainContainer->onKeyUpSystemDelegate, mainContainer, UserInput.keyboardPressedKey);
			}

			//Mouse events
			if (UserActivity.mouseLeftButtonStateChanged)
			{
				if (UserInput.mouseLeftPressed)
				{
					callDelegate<void*, point>(mainContainer->onClickSystemDelegate, mainContainer, UserInput.mouseConsolePos);
					callDelegate<void*, point>(mainContainer->onLeftButtonDownSystemDelegate, mainContainer, UserInput.mouseConsolePos);
				}
				else {
					callDelegate<void*, point>(mainContainer->onLeftButtonUpSystemDelegate, mainContainer, UserInput.mouseConsolePos);
				}
			}
			if (UserActivity.mouseRightButtonStateChanged)
			{
				if (UserInput.mouseRightPressed)
				{
					callDelegate<void*, point>(mainContainer->onClickSystemDelegate, mainContainer, UserInput.mouseConsolePos);
					callDelegate<void*, point>(mainContainer->onRightButtonDownSystemDelegate, mainContainer, UserInput.mouseConsolePos);
				}
				else {
					callDelegate<void*, point>(mainContainer->onRightButtonUpSystemDelegate, mainContainer, UserInput.mouseConsolePos);
				}
			}
		}

		//Output
		consoleClearAll();
		showCursor(consoleSizeRectangle(), toPoint(getMouseConsolePos()));
		drawAllElements();
		Sleep(eventDispatcherDelay);
	}
}