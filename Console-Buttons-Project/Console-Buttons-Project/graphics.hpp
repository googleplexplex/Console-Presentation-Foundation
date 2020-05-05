#pragma once
#include <iostream>
#include "congetter.hpp"

#define setConsoleTitle(x) SetConsoleTitle(x)
#define setCursorBegin() setTo(0, 0)
#define setWinTo(x, y) SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER)

typedef enum symbolColor {
	null = -1,
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

POINT inline toPoint(COORD coord)
{
	return { coord.X, coord.Y };
}

void editConsoleSize(int x, int y)
{
	//...
}
void inline setTo(short x, short y)
{
	SetConsoleCursorPosition(consoleHandle, { x, y });
}
bool getTo(POINT consoleSize, int x, int y)
{
	if (x < 0 || y < 0 || x >= consoleSize.x || y >= consoleSize.y)
		return false;
	return true;
}
bool getTo(int x, int y)
{
	return getTo(toPoint(getConsoleSize()), x, y);
}
POINT getConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(consoleHandle, &bi);
	return toPoint(bi.dwCursorPosition);
}


symbolColor presentTextAttribute = white;
void ConsolePrintCharset(char printedCharset) //TOFIX
{
	POINT consoleCursorPosition = getConsoleCursorPosition();
	CHAR_INFO symbolPrintedHere = getc_fromConsole(consoleCursorPosition.x, consoleCursorPosition.y);
	
	if (getTo(consoleCursorPosition.x, consoleCursorPosition.y))
	{
		if (printedCharset != symbolPrintedHere.Char.AsciiChar || presentTextAttribute != symbolPrintedHere.Attributes)
		{
			std::cout << printedCharset;
		}
	}
}

void inline setSymbolFullColor(symbolColor color)
{
	presentTextAttribute = symbolColor(color + (color * 16));
	SetConsoleTextAttribute(consoleHandle, presentTextAttribute);
}
void inline setSymbolColor(symbolColor text, symbolColor bg)
{
	presentTextAttribute = symbolColor(text + (bg * 16));
	SetConsoleTextAttribute(consoleHandle, presentTextAttribute);
}
void inline setStandartSymbolsMode()
{
	presentTextAttribute = white;
	SetConsoleTextAttribute(consoleHandle, presentTextAttribute);
}