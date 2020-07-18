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

		onFocus.add(Default_System_OnFocus);
		onClick.add(_onClick);
	}


	//Drawing methods
	void Draw()
	{
		rectangle thisElementRect = getRect();

		if (size.x > 0 && size.y > 0)
			consolePrintRect(thisElementRect, filledCharacter_5_5, background);

		if (size.y > 0)
		{
			point textPos = getTextPos();
			if (textLength <= size.x)
				consolePrintStr(textPos, textLength, text, collectColor(textColor, background));
			else if (size.x != 0)
				consolePrintStr({ 0, textPos.y }, size.x, text, collectColor(textColor, background));
		}
	}

private:
	point getTextPos()
	{
		point result = { pos.x + int(size.x / 2) - textLength / 2, pos.y + int(size.y / 2) };
		return result;
	}
};