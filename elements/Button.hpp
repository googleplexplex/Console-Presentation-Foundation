#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\textModule.hpp"
#include "helpers\helpFunctions.hpp"


class Button : controlElement, public textModule {
public:
	Button(point _pos, point _size, char* _text = (char*)"Button", onClick_DelegateType _onClick = NULL, symbolColor _textColor = white, symbolColor _foneColor = black, onFocus_DelegateType _onFocus = NULL, onFocusLost_DelegateType _onFocusLost = NULL)
	{
		pos = _pos;
		size = _size;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		background = _foneColor;
		textColor = _textColor;

		onClickSystemDelegate = NULL;
		onFocusSystemDelegate = NULL;
		onFocusLostSystemDelegate = NULL;

		onClickEvent += _onClick;
		onFocusEvent += _onFocus;
		onFocusLostEvent += _onFocusLost;

		registerElement();
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		setSymbolFullColor(background);
		for (int i = 0; i < size.y; i++)
		{
			setTo(pos.x, pos.y + i);
			for (int j = 0; j < size.x; j++)
			{
				consolePrintCharset(filledCharacter_5_5);
			}
		}

		setSymbolColor(textColor, background); //Text in button output
		point textPos = { pos.x + int(size.x / 2) - textLength / 2, pos.y + int(size.y / 2) };
		if (getTo(textPos))
		{
			setTo(textPos);
			consolePrintStr(text, textLength);
		}

		save.apply();
	}
	bool entersTheArea(point point)
	{
		return getBorder(point.x, pos.x, pos.x + size.x - 1)
			&& getBorder(point.y, pos.y, pos.y + size.y - 1);
	}
};