#pragma once
#include <iostream>
#include <windows.h>
#include <io.h>
#include <atltypes.h>
#include "graphics.hpp"
using namespace std;

#define moreThanNull(x) (x > 0)
#define setBorder(x, y, z) if(x < y) { x = y; } if(x > z) { x = z; }
#define getBorder(x, y, z) ((y) <= (x) && (x) <= (z))

#define mouseLeftButtonState (GetAsyncKeyState(VK_LBUTTON) == 0 ? false : true )
#define mouseRightButtonState (GetAsyncKeyState(VK_RBUTTON) == 0 ? false : true )

POINT getMousePos() //TOREF
{
	POINT pt;
	GetCursorPos(&pt);
	return pt;
}
POINT getWindowPos(HWND gettedWindow) //TOREF
{
	CRect rect;
	GetWindowRect(gettedWindow, rect);
	return POINT({ rect.left, rect.top + 30 + 1 });
}
POINT getFontSize(HANDLE gettedHandle) //TOREF
{
	CONSOLE_FONT_INFO GETFONT;
	GetCurrentConsoleFont(gettedHandle, FALSE, &GETFONT);
	COORD FontSize = GetConsoleFontSize(gettedHandle, GETFONT.nFont);

	return POINT({ FontSize.X, FontSize.Y });
}
POINT getMouseCon() //TOREF
{
	POINT fontSize = getFontSize(consoleHandle);
	POINT mousePos = getMousePos();
	POINT windowPos = getWindowPos(consoleHWND);
	fontSize.y--;
	POINT ret = { (mousePos.x - windowPos.x) / fontSize.x - 1, ((mousePos.y - windowPos.y) / fontSize.y) };
	return ret;
}

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

class buttonPress {
	POINT pos;
	POINT size;
	char *text;
	int textLength;
	symbolColor textColor;
	symbolColor foneColor;
	bool frame;
	symbolColor frameColor;
	void(*onClick_Delegate)(POINT);
public:
	void callOnClick_Delegate(POINT arg)
	{
		onClick_Delegate(arg);
	}
	//TODO CONSTRUCTORS FOR FRAME/NOT FRAME
	buttonPress(POINT _pos, POINT _size, void(*_onClick)(POINT), char* _text = (char*)"Button", symbolColor _textColor = white, symbolColor _foneColor = black, bool _frame = false, symbolColor _frameColor = null)
	{
		pos = _pos;
		size = _size;
		onClick_Delegate = _onClick;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		foneColor = _foneColor;
		textColor = _textColor;
		frame = _frame;
		frameColor = _frameColor;
	}
	~buttonPress()
	{
		delete[textLength] text;
	}

	void Draw()
	{
		if (frame)
		{
			setTo(pos.x, pos.y);
			setSymbolFullColor(frameColor);
			for (int i = 0; i < size.x; i++)
			{
				cout << filledCharacter_1_5;
			}

			for (int i = 1; i < size.y - 1; i++)
			{
				setTo(pos.x, pos.y + i);

				setSymbolFullColor(frameColor);
				cout << filledCharacter_1_5;

				setSymbolColor(textColor, foneColor);
				for (int i = 1; i < size.x - 1; i++)
				{
					cout << 'B'; //TODO OUTPUT TEXT
				}

				setSymbolFullColor(frameColor);
				cout << filledCharacter_1_5;
			}

			setTo(pos.x, pos.y + size.y - 1);
			setSymbolFullColor(frameColor);
			for (int i = 0; i < size.x; i++)
			{
				cout << filledCharacter_1_5;
			}

			setStandartSymbolsMode();
		}
		else {
			setSymbolColor(textColor, foneColor);
			for (int i = 0; i < size.y; i++)
			{
				setTo(pos.x, pos.y + i);
				for (int j = 0; j < size.x; j++)
				{
					cout << filledCharacter_1_5;
				}
			}
			setStandartSymbolsMode();
		}
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
	bool getFrame()
	{
		return frame;
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