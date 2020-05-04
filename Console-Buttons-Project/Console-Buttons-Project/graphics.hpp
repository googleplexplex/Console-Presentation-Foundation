#pragma once

#define setConsoleTitle(x) SetConsoleTitle(x)
#define setCursorBegin() setTo(0, 0)
#define setWinTo(x, y) SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)

typedef enum symbolColor {
	null = 0,
	black = 0,
	blue,
	green,
	aqua,
	red,
	violet,
	yellow,
	white,
	gray,
	brightBlue,
	brightGreen,
	brightAqua,
	brightRed,
	brightViolet,
	brightYellow,
	brightWhite,
};

//If we use enum, then filledCharacter_1_5 ((char)219) will be perceived as (int)219 and we will not be able to use "cout << filledCharacter_1_5"
#define filledCharacter_1_5 (char)219
#define filledCharacter_2_5 (char)178
#define filledCharacter_3_5 (char)177
#define filledCharacter_4_5 (char)176
#define filledCharacter_5_5 (char)32

HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND  consoleHWND = (HWND)consoleHandle;
HINSTANCE consoleInstance = (HINSTANCE)GetWindowLong(consoleHWND, -6);

void editConsoleSize(int intCols, int intLines)
{
	//...
}
POINT getConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
}
void inline setTo(short x, short y)
{
	SetConsoleCursorPosition(consoleHandle, { x, y });
}
bool getTo(POINT consoleSize, int x, int y)
{
	if (x < 0 || y < 0 || x > consoleSize.x - 1 || y > consoleSize.y - 1)
		return false;
	return true;
}
bool getTo(int x, int y)
{
	return getTo(getConsoleSize(), x, y);
}

void inline setSymbolFullColor(symbolColor color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (color * 16));
}
void inline setSymbolColor(symbolColor text, symbolColor bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text + (bg * 16));
}
void inline setStandartSymbolsMode()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);
}