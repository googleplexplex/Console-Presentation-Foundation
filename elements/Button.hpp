#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"
#include "modules\textModule.hpp"
#include "modules\lowLevelStrMethods.hpp"

class Button : public controlElement, public textModule {
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
	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
		consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, background);

		consolePrintStr(drawFrame, getTextPos(), textLength, text, collectColor(textColor, background));
	}

private:
	point getTextPos()
	{
		point result = { pos.x + int(size.x / 2) - textLength / 2, pos.y + int(size.y / 2) };
		//to validate
		return result;
	}
};