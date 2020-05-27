#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\textModule.hpp"
#include "helpers\helpFunctions.hpp"


//setSize/getSize fix
class Label : public controlElement, public textModule
{
public:
	Label(point _pos, char* _text = (char*)"Label", symbolColor _textColor = white, symbolColor _background = black)
	{
		pos = _pos;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size = { textLength, 1 };
		background = _background;
		textColor = _textColor;

		onFocusSystemDelegate = Default_System_OnFocus;

		registerElement();
	}

	void Draw(rectangle drawFrame)
	{
		consoleCursorInfo save;
		save.getAndReset();

		setTo(pos.x, pos.y);
		setSymbolColor(textColor, background);
		consolePrintStr(drawFrame, text, textLength);

		save.apply();
	}
};