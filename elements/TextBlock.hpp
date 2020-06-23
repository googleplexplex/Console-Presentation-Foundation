#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\textModule.hpp"
#include "helpers\helpFunctions.hpp"


class TextBlock : public controlElement, public textModule {
public:
	orientationXEnum orientationX;
	orientationYEnum orientationY;
	TextBlock(char* _text = (char*)"TextBlock", point _size = { 0, 0 }, orientationXEnum _orientationX = centerX, orientationYEnum _orientationY = centerY, symbolColor _textColor = white, symbolColor _background = black)
	{
		pos = emptyPoint;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size.x = (_size.x == 0) ? (_size.x) : (textLength);
		size.y = (_size.y == 0) ? (_size.y) : (1);
		orientationX = _orientationX;
		orientationY = _orientationY;
		background = _background;
		textColor = _textColor;

		onFocus += Default_System_OnFocus;

		registerElement();
	}


	//Drawing methods
	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
		consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, white);

		consolePrintStr(drawFrame, getTextPos(), textLength, text, collectColor(textColor, background));
	}


	//Text block methods
	void setText(char* settedText, unsigned int settedTextLength)
	{
		textLength = settedTextLength;
		text = stringCopy(settedText, textLength);

		if (size.x < settedTextLength)
			size.x = settedTextLength;
	}
	void setText(char* settedText)
	{
		setText(settedText, strlen(settedText));
	}
	void setText(const char* settedText)
	{
		setText((char*)settedText, strlen(settedText));
	}
	void setText(const char* settedText, unsigned int settedTextLength)
	{
		setText((char*)settedText, settedTextLength);
	}

	point getTextPos()
	{
		point result;

		if (orientationX == right)
			result.x = pos.x;
		else if (orientationX == centerX)
			result.x = pos.x + int(size.x / 2) - textLength / 2;
		else if (orientationX == left)
			result.x = pos.x + size.x - textLength;

		if (orientationY == up)
			result.y = pos.y;
		else if (orientationY == centerY)
			result.y = pos.y + int(size.y / 2);
		else if (orientationY == down)
			result.y = pos.y + size.y - 1;

		return result;
	}
};