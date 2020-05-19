#pragma once
#include <windows.h>
#include "helpers\helpFunctions.hpp"
#include "shell\graphics.hpp"

#define setConsoleTitle(x) SetConsoleTitle(x)
#define setWinTo(x, y) SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)
#define mouseLeftButtonState (GetAsyncKeyState(VK_LBUTTON) == 0 ? false : true )
#define mouseRightButtonState (GetAsyncKeyState(VK_RBUTTON) == 0 ? false : true )

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
//POINT getConsoleSize()
//{
//	CONSOLE_SCREEN_BUFFER_INFO result;
//	GetConsoleScreenBufferInfo(consoleHandle, &result);
//	return toWinPoint(result.dwSize);
//}

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