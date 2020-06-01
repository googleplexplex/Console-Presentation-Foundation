#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"


void TextBox_System_onKeyDown(void* textBoxPtr, char key);

class TextBox : public  controlElement, public textModule {
public:
	TextBox(point _pos, point _size, char* _text = (char*)"TextBox", symbolColor _textColor = white, symbolColor _foneColor = black)
	{
		pos = _pos;
		size = _size;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		background = _foneColor;
		textColor = _textColor;

		onFocusSystemDelegate = Default_System_OnFocus;
		onKeyDownSystemDelegate = TextBox_System_onKeyDown;

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

		point textPos = pos;
		for (int i = 0; i < textLength; i++)
		{
			if (textPos.x > drawFrame.secondPos.x || text[i] == enter)
			{
				textPos.x = pos.x;
				textPos.y++;
			}
			else {
				consolePrintCharset(drawFrame, textPos, text[i]);
				textPos.x++;
			}
		}

		save.apply();
	}
};

void TextBox_System_onKeyDown(void* textBoxPtr, char key)
{
	TextBox* textBox = (TextBox*)textBoxPtr;

	if (key == backspace)
		textBox->popText();
	else if (key == tab)
		textBox->addToText((char*)"    ", 4);
	else
		textBox->addToText(key);
}