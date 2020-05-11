#pragma once
#include <windows.h>
#include "helpFunctions.hpp"
#include "graphics.hpp"
#include "controlElement.hpp"


class label : controlElement {
	char *text;
	int textLength;
	POINT textPos;
	symbolColor textColor;
	symbolColor foneColor;
public:
	label(POINT _pos, char* _text = (char*)"label", void(*_onClick)(void*, POINT) = &emptyEvent, symbolColor _textColor = white, symbolColor _foneColor = black)
	{
		pos = _pos;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size = { textLength, 1 };
		onClick_Delegate = _onClick;
		foneColor = _foneColor;
		textColor = _textColor;
	}
	~label()
	{
		delete[] text;
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		setTo(pos.x, pos.y);
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
		size.x = textLength;
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
};