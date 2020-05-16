#pragma once
#include <iostream>
#include "shell\congetter.hpp"
#include "shell\interactionShell.hpp"
#include "helpers\helpFunctions.hpp"
#include "helpers\dynamicArray.hpp"

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

void editConsoleSize(int x, int y)
{
	//...
}
void inline setTo(short x, short y)
{
	SetConsoleCursorPosition(stdHandle, { x, y });
}
void inline setTo(point point)
{
	SetConsoleCursorPosition(stdHandle, toCoord(point));
}
bool getTo(point consoleSize, int x, int y)
{
	if (x < 0 || y < 0 || x >= consoleSize.x || y >= consoleSize.y)
		return false;
	return true;
}
bool getTo(int x, int y)
{
	return getTo(toPoint(getConsoleSize()), x, y);
}
bool getTo(point point)
{
	return getTo(toPoint(getConsoleSize()), point.x, point.y);
}
point getConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(stdHandle, &bi);
	return toPoint(bi.dwCursorPosition);
}


symbolColor presentTextAttribute = white;
void consolePrintCharset(char printedCharset) //TOFIX
{
	point consoleCursorPosition = getConsoleCursorPosition();
	CHAR_INFO symbolPrintedHere = getc_fromConsole(consoleCursorPosition.x, consoleCursorPosition.y);

	if (getTo(consoleCursorPosition.x, consoleCursorPosition.y))
	{
		if (printedCharset != symbolPrintedHere.Char.AsciiChar || presentTextAttribute != symbolPrintedHere.Attributes)
		{
			std::cout << printedCharset;
		}
	}
}
void consolePrintStr(char* printedStr, int size) //TOFIX
{
	point consoleCursorPosition = getConsoleCursorPosition();
	CHAR_INFO* strPrintedHere = gets_fromConsole(consoleCursorPosition.x, consoleCursorPosition.y, size);
	
	for (int i = 0; i < size; i++)
	{
		if (getTo(consoleCursorPosition.x, consoleCursorPosition.y))
		{
			if (printedStr[i] != strPrintedHere[i].Char.AsciiChar || presentTextAttribute != strPrintedHere[i].Attributes)
			{
				std::cout << printedStr[i];
			}
			else {
				setTo(consoleCursorPosition.x + 1, consoleCursorPosition.y);
			}
			consoleCursorPosition.x++;
		}
	}
}
void consolePrintLine(int size, char lineCharset = filledCharacter_5_5)
{
	point consoleCursorPosition = getConsoleCursorPosition();
	CHAR_INFO* strPrintedHere = gets_fromConsole(consoleCursorPosition.x, consoleCursorPosition.y, size);

	for (int i = 0; i < size; i++)
	{
		if (getTo(consoleCursorPosition.x, consoleCursorPosition.y))
		{
			if (lineCharset != strPrintedHere[i].Char.AsciiChar || presentTextAttribute != strPrintedHere[i].Attributes)
			{
				std::cout << lineCharset;
			}
			consoleCursorPosition.x++;
		}
	}
}

void inline setSymbolFullColor(symbolColor color)
{
	presentTextAttribute = symbolColor(color + (color * 16));
	SetConsoleTextAttribute(stdHandle, presentTextAttribute);
}
void inline setSymbolColor(symbolColor text, symbolColor bg)
{
	presentTextAttribute = symbolColor(text + (bg * 16));
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
void consoleClearElements()
{
	consoleCursorInfo save;
	save.getAndReset();
	setSymbolFullColor(black);

	for (int i = 0; i < elementsZones.count; i++)
	{
		point presentElementZoneSize = elementsZones[i].getSize();
		for (int j = 0; j < presentElementZoneSize.y; j++)
		{
			setTo(elementsZones[i].firstPos.x, elementsZones[i].firstPos.y + j);
			consolePrintLine(presentElementZoneSize.x, filledCharacter_1_5);
		}
	}

	save.apply();
}

void showCursor()
{
	point mousePositionRelativeToTheConsole = toPoint(getMouseConsolePos());
	if (getTo(mousePositionRelativeToTheConsole))
	{
		consoleCursorInfo save;
		save.getAndReset();

		setTo(mousePositionRelativeToTheConsole);
		std::cout << filledCharacter_5_5;

		save.apply();
	}
}