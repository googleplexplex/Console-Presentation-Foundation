#pragma once
#include <windows.h>
#include <conio.h>
#include "modules\types.hpp"
#include "shell\graphics.hpp"

bool getMouseLeftButtonState()
{
	return (GetAsyncKeyState(VK_LBUTTON) != 0);
}
bool getMouseRightButtonState()
{
	return (GetAsyncKeyState(VK_RBUTTON) != 0);
}

POINT getMouseGlobalPos()
{
	POINT pt;
	GetCursorPos(&pt);
	return pt;
}
POINT getWindowGlobalPos()
{
	WINDOWINFO winInfo;
	GetWindowInfo(consoleHWND, &winInfo);
	return POINT({ winInfo.rcWindow.left, winInfo.rcWindow.top });
}
POINT getConsoleFontSize()
{
	CONSOLE_FONT_INFO GETFONT;
	GetCurrentConsoleFont(stdHWND, FALSE, &GETFONT);
	COORD FontSize = GetConsoleFontSize(stdHWND, GETFONT.nFont);

	return POINT({ FontSize.X, FontSize.Y });
}
point getPresentConsoleSize()
{
	return toPoint(getConsoleSize());
}
rectangle consoleSizeRectangle()
{
	return { { 0, 0 }, toPoint(getConsoleSize()) };
}


const int windowUpFrameSize_px = 30;
const int calibrationValue_px = 8;
POINT getMouseConsolePos()
{
	POINT windowGlobalPos_px = getWindowGlobalPos();
	POINT mouseGlobalPosition_px = getMouseGlobalPos();
	POINT consoleFontSize_px = getConsoleFontSize();
	POINT mousePositionRelativeToTheConsole_px = { mouseGlobalPosition_px.x - windowGlobalPos_px.x - calibrationValue_px,
		mouseGlobalPosition_px.y - windowGlobalPos_px.y - windowUpFrameSize_px };
	POINT mousePositionRelativeToTheConsole_sym = { mousePositionRelativeToTheConsole_px.x / consoleFontSize_px.x,
							mousePositionRelativeToTheConsole_px.y / consoleFontSize_px.y };

	return mousePositionRelativeToTheConsole_sym;
}

void setConsoleSize(int x, int y)
{
	SetConsoleScreenBufferSize(consoleHandle, { short(x), short(y) });
}
void setTittle(char* newTittle)
{
	SetConsoleTitleA(newTittle);
}
void setWinTo(short x, short  y)
{
	SetWindowPos(consoleHWND, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

bool keyboardHit()
{
	return _kbhit();
}
char getInputedChar()
{
	return _getch();
}

struct UserActivityStruct
{
	bool mouseLeftButtonStateChanged;
	bool mouseRightButtonStateChanged;
	bool mousePosChanged;
	bool keyboardStateChanged;
	bool consoleWindowResized;
};

struct UserInputStruct
{
	point mouseConsolePos; //Mouse
	bool mouseLeftPressed;
	bool mouseRightPressed;
	char keyboardPressedKey; //Keyboard
	bool keyboardPress;

	UserInputStruct()
	{
		setNull();
	}

	void setNull()
	{
		//Mouse
		mouseConsolePos = { 0, 0 };
		mouseLeftPressed = 0;
		mouseRightPressed = 0;
		//Keyboard
		keyboardPress = 0;
		keyboardPressedKey = 0;
	}
};
UserInputStruct getInput()
{
	UserInputStruct result;

	//Mouse
	result.mouseConsolePos = toPoint(getMouseConsolePos());
	result.mouseLeftPressed = getMouseLeftButtonState();
	result.mouseRightPressed = getMouseRightButtonState();

	//Keyboard
	result.keyboardPress = keyboardHit();
	if (result.keyboardPress)
		result.keyboardPressedKey = getInputedChar();
	else
		result.keyboardPressedKey = 0;

	return result;
}

UserActivityStruct getUserActivity(UserInputStruct& prevUserIOActions, UserInputStruct& presentUserIOActions, point& prevConsoleSize, point& presentConsoleSize)
{
	UserActivityStruct result;

	if (prevUserIOActions.mouseLeftPressed != presentUserIOActions.mouseLeftPressed)
		result.mouseLeftButtonStateChanged = true;
	else
		result.mouseLeftButtonStateChanged = false;

	if (prevUserIOActions.mouseRightPressed != presentUserIOActions.mouseRightPressed)
		result.mouseRightButtonStateChanged = true;
	else
		result.mouseRightButtonStateChanged = false;

	if (prevUserIOActions.mouseConsolePos != presentUserIOActions.mouseConsolePos)
		result.mousePosChanged = true;
	else
		result.mousePosChanged = false;

	if (prevUserIOActions.keyboardPress != presentUserIOActions.keyboardPress)
		result.keyboardStateChanged = true;
	else
		result.keyboardStateChanged = false;

	if (prevConsoleSize != presentConsoleSize)
		result.consoleWindowResized = true;
	else
		result.consoleWindowResized = false;

	return result;
}