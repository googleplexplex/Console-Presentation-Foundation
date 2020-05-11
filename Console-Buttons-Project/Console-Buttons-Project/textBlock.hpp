#pragma once
#include <windows.h>
#include "helpFunctions.hpp"
#include "graphics.hpp"
#include "controlElement.hpp"


class textBlock : controlElement {
	char *text;
	int textLength;
	POINT textPos;
	symbolColor textColor;
	symbolColor foneColor;
	orientationXEnum orientationX;
	orientationYEnum orientationY;
public:
	textBlock(POINT _pos, char* _text = (char*)"TextBlock", POINT _size = { -1, -1 }, orientationXEnum _orientationX = centerX, orientationYEnum _orientationY = centerY, void(*_onClick)(void*, POINT) = &emptyEvent, symbolColor _textColor = white, symbolColor _foneColor = black)
	{
		pos = _pos;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size = _size;
		orientationX = _orientationX;
		orientationY = _orientationY;
		onClick_Delegate = _onClick;
		foneColor = _foneColor;
		textColor = _textColor;

		size.x = (_size.x > 0) ? (_size.x) : (textLength);
		size.y = (_size.y > 0) ? (_size.y) : (1);
	}
	~textBlock()
	{
		delete[] text;
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		setSymbolFullColor(foneColor);
		for (int i = 0; i < size.y; i++)
		{
			setTo(pos.x, pos.y + i);
			for (int j = 0; j < size.x; j++)
			{
				consolePrintCharset(filledCharacter_5_5);
			}
		}

		textPos = getTextPos();
		setTo(textPos);
		setSymbolColor(textColor, foneColor);
		consolePrintStr(text, textLength);

		save.apply();
	}
	bool entersTheArea(int x, int y)
	{
		return getBorder(x, pos.x, pos.x + size.x - 1)
			&& getBorder(y, pos.y, pos.y + size.y - 1);
	}
	bool entersTheArea(POINT point)
	{
		return entersTheArea(point.x, point.y);
	}

	void setText(char* _text)
	{
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
	}
	void setTextColor(symbolColor _textColor)
	{
		textColor = _textColor;
	}
	void setFoneColor(symbolColor _textFone)
	{
		foneColor = _textFone;
	}
	void setPos(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}
	void setSize(int x, int y)
	{
		size.x = x;
		size.y = y;
	}
	void setOrientationX(orientationXEnum newOrientation)
	{
		orientationX = newOrientation;
	}
	void setOrientationY(orientationYEnum newOrientation)
	{
		orientationY = newOrientation;
	}

	POINT getPos()
	{
		return pos;
	}
	POINT getSize()
	{
		return size;
	}
	char* getText()
	{
		return stringCopy(text, textLength);
	}
	symbolColor getTextColor()
	{
		return textColor;
	}
	POINT getTextPos()
	{
		POINT result;

		if (orientationX == right)
		{
			result.x = pos.x;
		}
		else if (orientationX == centerX)
		{
			result.x = pos.x + int(size.x / 2) - textLength / 2;
		}
		else if (orientationX == left)
		{
			result.x = pos.x + size.x - textLength;
		}

		if (orientationY == up)
		{
			result.y = pos.y;
		}
		else if (orientationY == centerY)
		{
			result.y = pos.y + int(size.y / 2);
		}
		else if (orientationY == down)
		{
			result.y = pos.y + size.y - 1;
		}

		return result;
	}
	symbolColor getFoneColor()
	{
		return foneColor;
	}
	orientationXEnum getOrientationX()
	{
		return orientationX;
	}
	orientationYEnum getOrientationY()
	{
		return orientationY;
	}
};