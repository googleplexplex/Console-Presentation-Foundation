#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "modules\dynamicArray.hpp"
#include "modules\types.hpp"
#include "modules\textModule.hpp"

void TextBox_System_onKeyDown(void* textBoxPtr, char key);

class TextBox : public controlElement, public textModule {
public:
	onTextChanged_EventType onTextChanged;
	unsigned int MaxLength;
	bool ReadOnly;
	//todo cursor
	TextBox(char* _text = (char*)"TextBox", unsigned int _maxLength = 512, bool _readOnly = false, symbolColor _textColor = white, symbolColor _foneColor = black)
	{
		pos = emptyPoint;
		size = emptyPoint;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		MaxLength = _maxLength;
		ReadOnly = _readOnly;
		background = _foneColor;
		textColor = _textColor;

		/*onFocus += Default_System_OnFocus;
		onKeyDown += TextBox_System_onKeyDown;*/
	}

	//Drawing methods
	void Draw(rectangle& drawFrame)
	{
		rectangle thisElementRect = getRect();
		if (Visible)
			consolePrintRect(drawFrame, thisElementRect, filledCharacter_5_5, collectColor(black, background));
		
		unsigned long int sizeS = size.x * size.y;
		if(sizeS < textLength)
			consolePrintStrInRect(drawFrame, thisElementRect, text + textLength - sizeS, sizeS, collectColor(textColor, background), filledCharacter_5_5, background);
		else
			consolePrintStrInRect(drawFrame, thisElementRect, text, textLength, collectColor(textColor, background), filledCharacter_5_5, background);
	}
};

//System delegates
void TextBox_System_onKeyDown(void* textBoxPtr, char key)
{
	TextBox* textBox = static_cast<TextBox*>(textBoxPtr);

	if (textBox->ReadOnly)
		return;

	if(isENLitera(key) || isRULitera(key) || isNum(key) || isPunctuationMark(key))
		textBox->addToText(key);
	else if (key == backspace)
		textBox->popText();
	else if (key == tab)
		textBox->addToText((char*)"    ", 4);
}