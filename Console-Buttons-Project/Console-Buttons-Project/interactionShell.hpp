#pragma once

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
POINT getMouseConsolePos() //TOREF
{
	POINT windowGlobalPos_px = getWindowGlobalPos();
	debug_ShowPoint(windowGlobalPos_px);
	POINT mouseGlobalPosition_px = getMouseGlobalPos();
	debug_ShowPoint(mouseGlobalPosition_px);
	POINT consoleFontSize_px = getConsoleFontSize();
	debug_ShowPoint(consoleFontSize_px);
	POINT mousePositionRelativeToTheConsole_px = { mouseGlobalPosition_px.x - windowGlobalPos_px.x,
		mouseGlobalPosition_px.y - windowGlobalPos_px.y};
	debug_ShowPoint(mousePositionRelativeToTheConsole_px);
	POINT mousePositionRelativeToTheConsole_sym = { mousePositionRelativeToTheConsole_px.x / consoleFontSize_px.x,
							mousePositionRelativeToTheConsole_px.y / consoleFontSize_px.y };
	debug_ShowPoint(mousePositionRelativeToTheConsole_sym);

	if (getTo(mousePositionRelativeToTheConsole_sym))
	{
		setTo(mousePositionRelativeToTheConsole_sym);
		std::cout << (char)219;
	}

	return mousePositionRelativeToTheConsole_sym;
}