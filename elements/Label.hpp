#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\textModule.hpp"
#include "helpers\helpFunctions.hpp"

class Label : public controlElement, public textModule
{
public:
	Label(char* _text = (char*)"Label", symbolColor _textColor = white, symbolColor _background = black)
	{
		pos = emptyPoint;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size = { textLength, 1 };
		background = _background;
		textColor = _textColor;

		onFocusSystemDelegate = Default_System_OnFocus;

		registerElement();
	}

	//Drawing methods
	void Draw(rectangle drawFrame)
	{
		consolePrintStr(drawFrame, pos, textLength, text, collectColor(textColor, background));
	}
};