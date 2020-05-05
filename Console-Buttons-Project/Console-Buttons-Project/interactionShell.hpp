#pragma once

#define setConsoleTitle(x) SetConsoleTitle(x)
#define setWinTo(x, y) SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)
#define mouseLeftButtonState (GetAsyncKeyState(VK_LBUTTON) == 0 ? false : true )
#define mouseRightButtonState (GetAsyncKeyState(VK_RBUTTON) == 0 ? false : true )

POINT getMousePos() //TOREF
{
	POINT pt;
	GetCursorPos(&pt);
	return pt;
}
POINT getWindowPos(HWND gettedWindow) //TOREF
{
	CRect rect;
	GetWindowRect(gettedWindow, rect);
	return POINT({ rect.left, rect.top + 30 + 1 });
}
POINT getFontSize(HANDLE gettedHandle) //TOREF
{
	CONSOLE_FONT_INFO GETFONT;
	GetCurrentConsoleFont(gettedHandle, FALSE, &GETFONT);
	COORD FontSize = GetConsoleFontSize(gettedHandle, GETFONT.nFont);

	return POINT({ FontSize.X, FontSize.Y });
}
POINT getMouseCon() //TOREF
{
	POINT fontSize = getFontSize(consoleHandle);
	POINT mousePos = getMousePos();
	POINT windowPos = getWindowPos(consoleHWND);
	fontSize.y--;
	POINT ret = { (mousePos.x - windowPos.x) / fontSize.x - 1, ((mousePos.y - windowPos.y) / fontSize.y) };
	return ret;
}