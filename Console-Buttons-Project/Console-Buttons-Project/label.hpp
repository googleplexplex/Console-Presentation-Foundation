#pragma once
#include <windows.h>
#include "helpFunctions.hpp"
#include "graphics.hpp"
#include "controlElement.hpp"


class label : controlElement {
	char *text;
	int textLength;
	symbolColor textColor;
	symbolColor foneColor;
	orientationXEnum orientationX;
	orientationYEnum orientationY;
public:
	label(POINT _pos, char* _text = (char*)"Label", POINT _size = { -1, -1 }, orientationXEnum _orientationX = centerX, orientationYEnum _orientationY = centerY, void(*_onClick)(void*, POINT) = &emptyEvent, symbolColor _textColor = white, symbolColor _foneColor = black)
	{
		pos = _pos;
		text = stringCopy(_text, textLength);
		textLength = strlen(_text);
		size = _size;
		orientationX = _orientationX;
		orientationY = _orientationY;
		onClick_Delegate = _onClick;
		foneColor = _foneColor;
		textColor = _textColor;

		size.x = (_size.x > 0) ? (_size.x) : (textLength);
		size.y = (_size.y > 0) ? (_size.y) : (1);
	}
	~label()
	{
		delete[] text;
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		//...

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