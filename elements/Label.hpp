#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"


//setSize/getSize fix
class Label : controlElement {
	char *text;
	int textLength;
	point textPos;
	symbolColor textColor;
public:
	Label(point _pos, char* _text = (char*)"Label", onClick_DelegateType _onClick = NULL, symbolColor _textColor = white, symbolColor _background = black, onFocus_DelegateType _onFocus = NULL, onFocusLost_DelegateType _onFocusLost = NULL)
	{
		pos = _pos;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size = { textLength, 1 };
		background = _background;
		textColor = _textColor;

		onClickSystemDelegate = NULL;
		onFocusSystemDelegate = NULL;
		onFocusLostSystemDelegate = NULL;

		onClickEvent += _onClick;
		onFocusEvent += _onFocus;
		onFocusLostEvent += _onFocusLost;

		registerElement();
	}
	~Label()
	{
		delete[] text;
	}

	void Draw()
	{
		consoleCursorInfo save;
		save.getAndReset();

		setTo(pos.x, pos.y);
		setSymbolColor(textColor, background);
		consolePrintStr(text, textLength);

		save.apply();
	}
	bool entersTheArea(point point)
	{
		return getBorder(point.x, pos.x, pos.x + size.x - 1)
			&& getBorder(point.y, pos.y, pos.y + size.y - 1);
	}

	void setText(char* _text)
	{
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		size.x = textLength;
	}
	void setTextColor(symbolColor _textColor)
	{
		textColor = _textColor;
	}

	char* getText()
	{
		return stringCopy(text, textLength);
	}
	symbolColor getTextColor()
	{
		return textColor;
	}
};