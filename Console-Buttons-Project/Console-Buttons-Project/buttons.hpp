#pragma once
#include <windows.h>
#include "helpFunctions.hpp"
#include "graphics.hpp"
#include "controlElement.hpp"


class button : controlElement {
	char *text;
	int textLength;
	symbolColor textColor;
	symbolColor foneColor;
	symbolColor frameColor;
public:
	//TODO CONSTRUCTORS FOR FRAME/NOT FRAME
	button(POINT _pos, POINT _size, char* _text = (char*)"Button", void(*_onClick)(void*, POINT) = &emptyEvent, symbolColor _textColor = white, symbolColor _foneColor = black, symbolColor _frameColor = null)
	{
		pos = _pos;
		size = _size;
		onClick_Delegate = _onClick;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		foneColor = _foneColor;
		textColor = _textColor;
		frameColor = _frameColor;
	}
	~button()
	{
		delete[] text;
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		if (hasFrame()) //bg output
		{
			setTo(pos.x, pos.y);
			setSymbolFullColor(frameColor);
			for (int i = 0; i < size.x; i++)
			{
				ConsolePrintCharset(filledCharacter_5_5);
			}

			for (int i = 1; i < size.y - 1; i++)
			{
				setTo(pos.x, pos.y + i);

				setSymbolFullColor(frameColor);
				ConsolePrintCharset(filledCharacter_5_5);

				setSymbolFullColor(foneColor);
				for (int i = 1; i < size.x - 1; i++)
				{
					ConsolePrintCharset(filledCharacter_1_5);
				}

				setSymbolFullColor(frameColor);
				ConsolePrintCharset(filledCharacter_5_5);
			}

			setTo(pos.x, pos.y + size.y - 1);
			setSymbolFullColor(frameColor);
			for (int i = 0; i < size.x; i++)
			{
				ConsolePrintCharset(filledCharacter_5_5);
			}
		}
		else {
			setSymbolFullColor(foneColor);
			for (int i = 0; i < size.y; i++)
			{
				setTo(pos.x, pos.y + i);
				for (int j = 0; j < size.x; j++)
				{
					ConsolePrintCharset(filledCharacter_5_5);
				}
			}
		}

		setSymbolColor(textColor, foneColor); //Text in button output
		POINT textPos = { pos.x + int(size.x / 2) - textLength / 2, pos.y + int(size.y / 2) };
		if (getTo(textPos))
		{
			setTo(textPos);
			std::cout << text; //TOUP
		}

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
	void setFrame(symbolColor _frameColor)
	{
		frameColor = _frameColor;
	}
	void setFrameColor(symbolColor _frameColor)
	{
		frameColor = _frameColor;
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
	POINT getPos()
	{
		return pos;
	}
	POINT getSize()
	{
		return size;
	}
	bool hasFrame()
	{
		return (frameColor != null);
	}
	symbolColor getFrameColor()
	{
		return frameColor;
	}
};