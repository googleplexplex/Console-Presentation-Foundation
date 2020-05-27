#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\textModule.hpp"
#include "helpers\helpFunctions.hpp"

class Button : public controlElement, public textModule {
public:
	Button(point _pos, point _size, char* _text = (char*)"Button", onClick_DelegateType _onClick = NULL, symbolColor _textColor = white, symbolColor _foneColor = black)
	{
		pos = _pos;
		size = _size;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		background = _foneColor;
		textColor = _textColor;

		onFocusSystemDelegate = Default_System_OnFocus;

		onClickEvent += _onClick;

		registerElement();
	}

	void Draw(rectangle drawFrame)
	{
		consoleCursorInfo save;
		save.getAndReset();

		setSymbolFullColor(background);
		for (int i = 0; i < size.y; i++)
		{
			setTo(pos.x, pos.y + i);
			consolePrintLine(drawFrame, size.x, filledCharacter_5_5);
		}

		setSymbolColor(textColor, background); //Text in button output
		point textPos = { pos.x + int(size.x / 2) - textLength / 2, pos.y + int(size.y / 2) };
		if (getTo(drawFrame, textPos))
		{
			setTo(textPos);
			consolePrintStr(drawFrame, text, textLength);
		}

		save.apply();
	}
};