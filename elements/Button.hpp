#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"
#include "modules\textControlElement.hpp"
#include "modules\lowLevelStrMethods.hpp"

class Button : public textControlElement {
public:
	Button(char* _text = (char*)"Button", onClick_DelegateType _onClick = NULL, symbolColor _textColor = white, symbolColor _foneColor = black)
	{
		pos = emptyPoint;
		size = emptyPoint;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		background = _foneColor;
		textColor = _textColor;

		onFocus += Default_System_OnFocus;
		onClick += _onClick;
	}


	//Drawing methods
	void Draw()
	{
		rectangle thisElementRect = getRect();
		consolePrintRect(thisElementRect, filledCharacter_5_5, background);

		consolePrintStr(getTextPos(), textLength, text, collectColor(textColor, background));

		needToDraw = false;
	}

private:
	point getTextPos()
	{
		point result = { pos.x + int(size.x / 2) - textLength / 2, pos.y + int(size.y / 2) };
		//to validate
		return result;
	}
};