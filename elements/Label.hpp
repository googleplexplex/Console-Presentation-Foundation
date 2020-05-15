#pragma once
#include "helpers\helpFunctions.hpp"
#include "shell\graphics.hpp"
#include "core\controlElement.hpp"


class Label : controlElement {
	char *text;
	int textLength;
	point textPos;
	symbolColor textColor;
	symbolColor foneColor;
public:
	Label(point _pos, char* _text = (char*)"Label", void(*_onClick)(void*, point) = &OnClick_emptyEvent, symbolColor _textColor = white, symbolColor _foneColor = black, void(*_onFocus)(void*) = &onFocus_emptyEvent, void(*_onFocusLost)(void*) = &onFocusLost_emptyEvent)
	{
		pos = _pos;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size = { textLength, 1 };
		foneColor = _foneColor;
		textColor = _textColor;

		onClickEvent += _onClick;
		onFocusEvent += _onFocus;
		onFocusLostEvent += _onFocusLost;
	}
	~Label()
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
	bool entersTheArea(point point)
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

	point getPos()
	{
		return pos;
	}
	point getSize()
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