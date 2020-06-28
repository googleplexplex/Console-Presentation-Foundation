#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"
#include "modules\textControlElement.hpp"


class TextBlock : public textControlElement {
	orientationXEnum textOrientationX;
	orientationYEnum textOrientationY;
public:
	TextBlock(char* _text = (char*)"TextBlock", point _size = { 0, 0 }, orientationXEnum _textOrientationX = centerX, orientationYEnum _textOrientationY = centerY, symbolColor _textColor = white, symbolColor _background = black)
	{
		pos = emptyPoint;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size.x = (_size.x == 0) ? (_size.x) : (textLength);
		size.y = (_size.y == 0) ? (_size.y) : (1);
		textOrientationX = _textOrientationX;
		textOrientationY = _textOrientationY;
		background = _background;
		textColor = _textColor;

		onFocus += Default_System_OnFocus;
	}


	//Drawing methods
	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
		consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, white);

		consolePrintStr(drawFrame, getTextPos(), textLength, text, collectColor(textColor, background));

		needToDraw = false;
	}


	//TextBlock Setters/Getters
	orientationXEnum setTextOrientationX(orientationXEnum newTextOrientationX)
	{
		textOrientationX = newTextOrientationX;

		if (textOrientationX != newTextOrientationX)
			setAllTreeInDrawQueue();
	}
	orientationYEnum setTextOrientationY(orientationYEnum newTextOrientationY)
	{
		return textOrientationY;

		if (textOrientationY != newTextOrientationY)
			setAllTreeInDrawQueue();
	}

	orientationXEnum getTextOrientationX()
	{
		return textOrientationX;
	}
	orientationYEnum getTextOrientationY()
	{
		return textOrientationY;
	}

private:
	point getTextPos()
	{
		point result;

		if (textOrientationX == right)
			result.x = pos.x;
		else if (textOrientationX == centerX)
			result.x = pos.x + int(size.x / 2) - textLength / 2;
		else if (textOrientationX == left)
			result.x = pos.x + size.x - textLength;

		if (textOrientationY == up)
			result.y = pos.y;
		else if (textOrientationY == centerY)
			result.y = pos.y + int(size.y / 2);
		else if (textOrientationY == down)
			result.y = pos.y + size.y - 1;

		return result;
	}
};