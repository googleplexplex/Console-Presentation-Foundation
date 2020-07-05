#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"
#include "modules\textControlElement.hpp"
#include "modules\lowLevelStrMethods.hpp"

class Label : public textControlElement {
public:
	Label(char* _text = (char*)"Label", symbolColor _textColor = white, symbolColor _background = black)
	{
		pos = emptyPoint;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size = { textLength, 1 };
		background = _background;
		textColor = _textColor;

		onFocus.add(Default_System_OnFocus);
	}

	//Drawing methods
	void Draw()
	{
		consolePrintStr(pos, textLength, text, collectColor(textColor, background));

		needToDraw = false;
	}
};