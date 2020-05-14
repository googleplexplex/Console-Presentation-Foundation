#pragma once
#include <windows.h>

HWND consoleHWND = GetConsoleWindow();
HANDLE consoleHandle = (HANDLE)consoleHandle;
HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND stdHWND = (HWND)stdHandle;

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

#ifdef DEBUG
	#define debug_ShowPoint(point) std::cout << #point << " - " << point.x << ", " << point.y << std::endl
#else
	#define debug_ShowPoint(point)
#endif
const int windowUpFrameSize = 30;
const int calibrationValue = 8;
POINT getMouseConsolePos()
{
	POINT windowGlobalPos_px = getWindowGlobalPos(); debug_ShowPoint(windowGlobalPos_px);
	POINT mouseGlobalPosition_px = getMouseGlobalPos(); debug_ShowPoint(mouseGlobalPosition_px);
	POINT consoleFontSize_px = getConsoleFontSize(); debug_ShowPoint(consoleFontSize_px);
	POINT mousePositionRelativeToTheConsole_px = { mouseGlobalPosition_px.x - windowGlobalPos_px.x - calibrationValue,
		mouseGlobalPosition_px.y - windowGlobalPos_px.y - windowUpFrameSize }; debug_ShowPoint(mousePositionRelativeToTheConsole_px);
	POINT mousePositionRelativeToTheConsole_sym = { mousePositionRelativeToTheConsole_px.x / consoleFontSize_px.x,
							mousePositionRelativeToTheConsole_px.y / consoleFontSize_px.y }; debug_ShowPoint(mousePositionRelativeToTheConsole_sym);

	return mousePositionRelativeToTheConsole_sym;
}