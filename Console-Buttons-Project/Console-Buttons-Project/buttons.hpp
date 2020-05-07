#pragma once
#include <windows.h>
#include "graphics.hpp"
#include "controlElement.hpp"

#define moreThanNull(x) (x > 0)
#define setBorder(x, y, z) if(x < y) { x = y; } if(x > z) { x = z; }
#define getBorder(pos, min, max) ((min) <= (pos) && (pos) <= (max))

char* stringCopy(char* string, int stringSize)
{
	char* result = new char[stringSize + 1];
	memcpy(result, string, stringSize + 1);
	return result;
}
char* stringCopy(const char* string, int stringSize)
{
	return stringCopy((char*)string, stringSize);
}

class button : controlElement {
	char *text;
	int textLength;
	symbolColor textColor;
	symbolColor foneColor;
	symbolColor frameColor;
	//orientationEnum orientation;
public:
	//TODO CONSTRUCTORS FOR FRAME/NOT FRAME
	button(POINT _pos, POINT _size, void(*_onClick)(POINT), char* _text = (char*)"Button", symbolColor _textColor = white, symbolColor _foneColor = black, symbolColor _frameColor = null)
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
		delete[textLength] text;
	}

	void Draw()
	{
		if (hasFrame())
		{
			setTo(pos.x, pos.y);
			setSymbolFullColor(frameColor);
			for (int i = 0; i < size.x; i++)
			{
				ConsolePrintCharset(filledCharacter_1_5);
			}

			for (int i = 1; i < size.y - 1; i++)
			{
				setTo(pos.x, pos.y + i);

				setSymbolFullColor(frameColor);
				ConsolePrintCharset(filledCharacter_1_5);

				setSymbolFullColor(foneColor);
				for (int i = 1; i < size.x - 1; i++)
				{
					ConsolePrintCharset(filledCharacter_5_5);
				}

				setSymbolFullColor(frameColor);
				ConsolePrintCharset(filledCharacter_1_5);
			}

			setTo(pos.x, pos.y + size.y - 1);
			setSymbolFullColor(frameColor);
			for (int i = 0; i < size.x; i++)
			{
				ConsolePrintCharset(filledCharacter_1_5);
			}
		}
		else {
			setSymbolFullColor(foneColor);
			for (int i = 0; i < size.y; i++)
			{
				setTo(pos.x, pos.y + i);
				for (int j = 0; j < size.x; j++)
				{
					ConsolePrintCharset(filledCharacter_1_5);
				}
			}
		}

		setSymbolColor(textColor, foneColor);
		POINT textPos = { pos.x + int(size.x / 2) - textLength / 2, pos.y + int(size.y / 2) };
		if (getTo(textPos))
		{
			setTo(textPos);
			std::cout << text; //TOUP
		}
		setStandartSymbolsColor();
	}
	bool entersTheArea(int x, int y)
	{
		return getBorder(x, pos.x, pos.x + size.x)
			&& getBorder(y, pos.y, pos.y + size.y);
	}
	bool entersTheArea(POINT point)
	{
		return entersTheArea(point.x, point.y);
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
	/*friend bool getButton(button_press *bt);
	friend void addFrame(button_press *bt, int bash);
	friend void eriseFrame(button_press *bt);
	friend void _unsafeCleanText(button_press *bt);
	friend void cleanText(button_press *bt);
	friend void editButtonText(button_press *bt, const char _text[], int _newTextBash);
	friend void editButtonText(button_press *bt, const char _text[]);
	friend void editButtonText(button_press *bt, int _intText, int _newTextBash);
	friend void editButtonText(button_press *bt, int _intText);
	friend void editButtonText(button_press *bt, char _charText, int _newTextBash);
	friend void editButtonText(button_press *bt, char _charText);
	friend void editButtonFone(button_press *bt, int _newFoneBash);
	friend void editButton(button_press *bt, char text[], int _newTextBash, int _newFoneBash);
	friend void editButton(button_press *bt, char text[], int _newTextBash, int _newFoneBash, int _newFrameBash);
	friend void setX(button_press *bt, int _newx);
	friend void setY(button_press *bt, int _newy);
	friend void setXY(button_press *bt, int _newx, int _newy);
	friend void setXSize(button_press *bt, int _newxsize);
	friend void setYSize(button_press *bt, int _newysize);
	friend void setXYSize(button_press *bt, int _newxsize, int _newysize);
	friend void setPropSize(button_press *bt, int _newsize);*/
	//...
};