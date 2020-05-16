#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"


class TextBlock : controlElement {
	char *text;
	int textLength;
	point textPos;
	symbolColor textColor;
	orientationXEnum orientationX;
	orientationYEnum orientationY;
public:
	TextBlock(point _pos, char* _text = (char*)"TextBlock", point _size = { -1, -1 }, orientationXEnum _orientationX = centerX, orientationYEnum _orientationY = centerY, onClick_DelegateType _onClick = NULL, symbolColor _textColor = white, symbolColor _background = black, onFocus_DelegateType _onFocus = NULL, onFocusLost_DelegateType _onFocusLost = NULL)
	{
		pos = _pos;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size.x = (_size.x > 0) ? (_size.x) : (textLength);
		size.y = (_size.y > 0) ? (_size.y) : (1);
		orientationX = _orientationX;
		orientationY = _orientationY;
		background = _background;
		textColor = _textColor;

		onClickSystemDelegate = NULL;
		onFocusSystemDelegate = NULL;
		onFocusLostSystemDelegate = NULL;

		onClickEvent += _onClick;
		onFocusEvent += _onFocus;
		onFocusLostEvent += _onFocusLost;

		registerElement();
	}
	~TextBlock()
	{
		delete[] text;
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		setSymbolFullColor(background);
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
		setSymbolColor(textColor, background);
		consolePrintStr(text, textLength);

		save.apply();
	}
	bool entersTheArea(point point)
	{
		return getBorder(point.x, pos.x, pos.x + size.x - 1)
			&& getBorder(point.y, pos.y, pos.y + size.y - 1);
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
	void setOrientationX(orientationXEnum newOrientation)
	{
		orientationX = newOrientation;
	}
	void setOrientationY(orientationYEnum newOrientation)
	{
		orientationY = newOrientation;
	}

	char* getText()
	{
		return stringCopy(text, textLength);
	}
	symbolColor getTextColor()
	{
		return textColor;
	}
	point getTextPos()
	{
		point result;

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
	orientationXEnum getOrientationX()
	{
		return orientationX;
	}
	orientationYEnum getOrientationY()
	{
		return orientationY;
	}
};