#pragma once
#include <iostream>
#include <windows.h>
#include "shell\WinConIO.hpp"
#include "helpers\helpFunctions.hpp"
#include "helpers\dynamicArray.hpp"

HWND consoleHWND = GetConsoleWindow();
HANDLE consoleHandle = (HANDLE)consoleHWND;
HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND stdHWND = (HWND)stdHandle;

#define setCursorBegin() setTo(0, 0)

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

//If we use enum, then filledCharacter_5_5 ((char)219) will be perceived as (int)219 and we will not be able to use "cout << filledCharacter_5_5"
#define filledCharacter_5_5 (char)219
#define filledCharacter_4_5 (char)178
#define filledCharacter_3_5 (char)177
#define filledCharacter_2_5 (char)176
#define filledCharacter_1_5 (char)32


POINT inline toWinPoint(COORD coord) //TODEL
{
	return { coord.X, coord.Y };
}
POINT inline toWinPoint(point point) //TODEL
{
	return { point.x, point.y };
}

COORD inline toCoord(POINT point) //TODEL
{
	return { short(point.x), short(point.y) };
}
COORD inline toCoord(point point) //TODEL
{
	return { short(point.x), short(point.y) };
}

point inline toPoint(POINT point) //TODEL
{
	return { point.x, point.y };
}
point inline toPoint(COORD coord) //TODEL
{
	return { coord.X, coord.Y };
}

SMALL_RECT inline toSmallRect(rectangle rect)
{
	return { short(rect.firstPos.x), short(rect.firstPos.y), short(rect.secondPos.x), short(rect.secondPos.y) };
}

rectangle _drawFrame = { {0, 0}, toPoint(getConsoleSize()) };

void inline setTo(short x, short y)
{
	SetConsoleCursorPosition(stdHandle, { x, y });
}
void inline setTo(point point)
{
	SetConsoleCursorPosition(stdHandle, toCoord(point));
}
bool getTo(rectangle drawFrame, int x, int y)
{
	if (x < drawFrame.firstPos.x || y < drawFrame.firstPos.y || x >= drawFrame.secondPos.x || y >= drawFrame.secondPos.y)
		return false;
	return true;
}
bool getTo(rectangle drawFrame, point point)
{
	return getTo(drawFrame, point.x, point.y);
}
point getConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(stdHandle, &bi);
	return toPoint(bi.dwCursorPosition);
}


symbolColor presentTextAttribute = white;
void consolePrintCharset(rectangle& drawFrame, point pos, char printedCharset, symbolColor printedCharColor = presentTextAttribute)
{
	if (getTo(drawFrame, pos))
		setCharInConsoleA(toCoord(pos), printedCharset, (WORD)printedCharColor);
}
void consolePrintStr(rectangle& drawFrame, point pos, int size, char* printedStr, symbolColor printedStrColor = presentTextAttribute)
{
	if (getTo(drawFrame, pos) && getTo(drawFrame, { pos.x, pos.y + size }))
		setStringInConsoleA(toCoord(pos), printedStr, size, (WORD)printedStrColor);
}
void consolePrintLine(rectangle& drawFrame, point pos, int size, char lineCharset = filledCharacter_5_5, symbolColor printedLineColor = presentTextAttribute)
{
	if (getTo(drawFrame, pos) && getTo(drawFrame, { pos.x, pos.y + size }))
		setLineInConsoleA(toCoord(pos), lineCharset, size, (WORD)printedLineColor);
}
void consolePrintRect(rectangle& drawFrame, rectangle& rect, char lineCharset = filledCharacter_5_5, symbolColor lineCharsetColor = presentTextAttribute)
{
	if (getTo(drawFrame, rect.firstPos) && getTo(drawFrame, rect.secondPos))
	{
		SMALL_RECT srrect = toSmallRect(rect);
		setRectInConsoleA(srrect, lineCharset, (WORD)lineCharsetColor);
	}
}
void consolePrintStrInLine(rectangle& drawFrame, point pos, int lineSize, char* printedStr, int strSize, symbolColor strColor = presentTextAttribute, char filledChar = emptyAsciiChar, symbolColor filledCharColor = presentTextAttribute)
{
	if (getTo(drawFrame, pos) && getTo(drawFrame, { pos.x + strSize, pos.y }))
	{
		consolePrintStr(drawFrame, pos, strSize, printedStr, strColor);
		if(lineSize > strSize)
			consolePrintLine(drawFrame, { pos.x, pos.y + strSize }, lineSize - strSize, filledChar, filledCharColor);
	}
}
void consolePrintStrInRect(rectangle& drawFrame, rectangle& rect, char* printedStr, int printedStrSize, symbolColor printedStrColor = presentTextAttribute, char filledChar = emptyAsciiChar, symbolColor filledCharColor = presentTextAttribute)
{
	SMALL_RECT srrect = toSmallRect(rect);
	CHAR_INFO filledCharInfo = { filledChar, (WORD)filledCharColor };
	setRectInConsoleA(srrect, printedStr, printedStrSize, printedStrColor, filledCharInfo);
}

symbolColor inline collectColor(symbolColor textColor, symbolColor backgroundColor)
{
	return symbolColor(textColor + (backgroundColor * 16));
}
void inline setSymbolFullColor(symbolColor color)
{
	presentTextAttribute = collectColor(color, color);
	SetConsoleTextAttribute(stdHandle, presentTextAttribute);
}
void inline setSymbolColor(symbolColor textColor, symbolColor backgroundColor)
{
	presentTextAttribute = collectColor(textColor, backgroundColor);
	SetConsoleTextAttribute(stdHandle, presentTextAttribute);
}
void inline setStandartSymbolsColor()
{
	presentTextAttribute = white;
	SetConsoleTextAttribute(stdHandle, presentTextAttribute);
}

struct consoleCursorInfo
{
	point pos;
	symbolColor color;

	void get()
	{
		pos = getConsoleCursorPosition();
		color = presentTextAttribute;
	}
	void getAndReset()
	{
		get();
		setStandartSymbolsColor();
	}
	void apply()
	{
		setTo(pos);
		SetConsoleTextAttribute(stdHandle, color);
	}
};

dynamicArray<rectangle> elementsZones; //TOHIDE
void addElementZone(rectangle elementZone)
{
	elementsZones.add(elementZone); //TOUP
}
void consoleClearElements(rectangle drawFrame)
{
	for (int i = 0; i < elementsZones.count; i++)
	{
		consolePrintRect(drawFrame, elementsZones[i], emptyAsciiChar, white);
	}
}
void consoleClearAll()
{
	setAllConsoleCI();
}

void showCursor(rectangle drawFrame, point cursorPos)
{
	if (getTo(drawFrame, cursorPos))
		setCharInConsoleA(toCoord(cursorPos), filledCharacter_5_5, white);
}