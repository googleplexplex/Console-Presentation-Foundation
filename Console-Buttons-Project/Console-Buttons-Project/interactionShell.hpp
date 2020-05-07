#pragma once
#include <windows.h>

#define setConsoleTitle(x) SetConsoleTitle(x)
#define setWinTo(x, y) SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)
#define mouseLeftButtonState (GetAsyncKeyState(VK_LBUTTON) == 0 ? false : true )
#define mouseRightButtonState (GetAsyncKeyState(VK_RBUTTON) == 0 ? false : true )

POINT getMouseGlobalPos() //TOREF
{
	POINT pt;
	GetCursorPos(&pt);
	return pt;
}
POINT getWindowGlobalPos() //TOREF
{
	WINDOWINFO winInfo;
	GetWindowInfo(consoleHWND, &winInfo);
	return POINT({ winInfo.rcWindow.left, winInfo.rcWindow.top });
}
POINT getConsoleFontSize() //TOREF
{
	CONSOLE_FONT_INFO GETFONT;
	GetCurrentConsoleFont(stdHWND, FALSE, &GETFONT);
	COORD FontSize = GetConsoleFontSize(stdHWND, GETFONT.nFont);

	return POINT({ FontSize.X, FontSize.Y });
}
#define debug_ShowPoint(point) std::cout << #point << " - " << point.x << ", " << point.y << std::endl
const int windowUpFrameSize = 30;
const int calibrationValue = 8;
POINT getMouseConsolePos() //TOREF
{
	POINT windowGlobalPos_px = getWindowGlobalPos();
	POINT mouseGlobalPosition_px = getMouseGlobalPos();
	POINT consoleFontSize_px = getConsoleFontSize();
	POINT mousePositionRelativeToTheConsole_px = { mouseGlobalPosition_px.x - windowGlobalPos_px.x - calibrationValue,
		mouseGlobalPosition_px.y - windowGlobalPos_px.y - windowUpFrameSize };
	POINT mousePositionRelativeToTheConsole_sym = { mousePositionRelativeToTheConsole_px.x / consoleFontSize_px.x,
							mousePositionRelativeToTheConsole_px.y / consoleFontSize_px.y };

	return mousePositionRelativeToTheConsole_sym;
}