#pragma once
#include "core\controlElement.hpp"
#include "core\event.hpp"
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"

void TextBox_System_onKeyDown(void* textBoxPtr, char key);
void TextBox_System_onTextChanged(void* textBoxPtr);

class TextBox : public  controlElement { //insert TextModule
	char* text;
	unsigned int textLength;
	symbolColor textColor;

	onTextChanged_DelegateType onTextChangedSystemDelegate = NULL;
public:
	onTextChanged_EventType onTextChangedEvent;
	unsigned int MaxLength;
	bool ReadOnly;
	//todo cursor
	TextBox(point _pos, point _size, char* _text = (char*)"TextBox", symbolColor _textColor = white, symbolColor _foneColor = black, unsigned int _maxLength = 512, bool _readOnly = false)
	{
		pos = _pos;
		size = _size;
		textLength = strlen(_text);
		text = stringCopy(_text, textLength);
		MaxLength = _maxLength;
		ReadOnly = _readOnly;
		background = _foneColor;
		textColor = _textColor;

		onFocusSystemDelegate = Default_System_OnFocus;
		onKeyDownSystemDelegate = TextBox_System_onKeyDown;
		onTextChangedSystemDelegate = TextBox_System_onTextChanged;

		registerElement();
	}
	~TextBox()
	{
		delete[] text;
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
		setTo(pos);
		setSymbolColor(textColor, background);
		for (int i = 0; i < textLength; i++)
		{
			if (textPos.x >= pos.x + size.x || text[i] == enter)
			{
				if (textPos.y >= pos.y + size.y)
					break;
				textPos.x = pos.x;
				textPos.y++;
				setTo(textPos);
			}

			consolePrintCharset(drawFrame, textPos, text[i]);
			textPos.x++;
		}

		save.apply();
	}

	void popText()
	{
		if (textLength == 0)
			return;

		callDelegate(onTextChangedSystemDelegate, (void*)this);

		char* oldText = text;
		text = new char[textLength];
		memcpy(text, oldText, textLength - 1);
		text[textLength] = NULL;
		textLength--;
	}
	void addToText(char addedCharset)
	{
		if (MaxLength < textLength + 1)
			return;

		callDelegate(onTextChangedSystemDelegate, (void*)this);

		char* oldText = text;
		text = new char[textLength + 1 + 1];
		memcpy(text, oldText, textLength);
		text[textLength] = addedCharset;
		text[textLength + 1] = NULL;
		textLength++;
	}
	void addToText(char* addedString, int addedStringSize)
	{
		if (MaxLength < textLength + addedStringSize)
			return;

		callDelegate(onTextChangedSystemDelegate, (void*)this);

		char* oldText = text;
		text = new char[textLength + addedStringSize + 1];
		memcpy(text, oldText, textLength);
		memcpy(text + textLength, addedString, addedStringSize);
		text[textLength + addedStringSize] = NULL;
		textLength += addedStringSize;
	}
	void addToText(char* addedString)
	{
		addToText(addedString, strlen(addedString));
	}

	unsigned int getTextLength()
	{
		return textLength;
	}
};

bool isENLitera(char charset)
{
	return (('a' <= charset && charset >= 'z') || ('A' <= charset && charset >= 'Z'));
}
bool isRULitera(char charset)
{
	return (('à' <= charset && charset >= 'ÿ') || ('À' <= charset && charset >= 'ß'));
}
dynamicArray<char> allPunctuationMarks = "~`!@\"#¹$;%^:&?*()-_+=\\|/{[}].,<>";
bool isPunctuationMark(char charset)
{
	int findResult = allPunctuationMarks.find(charset);
	return (findResult != -1);
}
dynamicArray<char> allNumbers = "0123456789";
bool isNum(char charset)
{
	int findResult = allNumbers.find(charset);
	return (findResult != -1);
}

void TextBox_System_onKeyDown(void* textBoxPtr, char key)
{
	TextBox* textBox = (TextBox*)textBoxPtr;

	if (textBox->ReadOnly)
		return;

	if(isENLitera(key) || isRULitera(key) || isNum(key) || isPunctuationMark(key))
		textBox->addToText(key);
	else if (key == backspace)
		textBox->popText();
	else if (key == tab)
		textBox->addToText((char*)"    ", 4);
}

void TextBox_System_onTextChanged(void* textBoxPtr)
{
	TextBox* textBox = (TextBox*)textBoxPtr;
	textBox->onTextChangedEvent.call(textBoxPtr);
}