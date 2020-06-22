#pragma once
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"

constexpr char backspace = 8;
constexpr char tab = 9;
constexpr char enter = 10;

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

class textModule
{
protected:
	char* text;
	unsigned int textLength;
public:
	symbolColor textColor;

	~textModule()
	{
		delete[] text;
	}

	void setText(char* settedText, unsigned int settedTextLength)
	{
		textLength = settedTextLength;
		delete text;
		text = stringCopy(settedText, textLength);
	}
	void setText(char* settedText)
	{
		setText(settedText, strlen(settedText));
	}
	void setText(const char* settedText, unsigned int settedTextLength)
	{
		setText((char*)settedText, settedTextLength);
	}
	void setText(const char* settedText)
	{
		setText((char*)settedText, strlen(settedText));
	}
	void setTextColor(symbolColor settedTextColor)
	{
		textColor = settedTextColor;
	}
	void addToText(char addedCharset)
	{
		char* oldText = text;
		text = new char[textLength + 1 + 1]; //Text Length + New charset + NULL-Charset
		memcpy(text, oldText, textLength);
		text[textLength] = addedCharset;
		text[textLength + 1] = NULL;
		textLength++;
		delete oldText;
	}
	void addToText(char* addedString, unsigned int addedStringLength)
	{
		char* oldText = text;
		text = new char[textLength + addedStringLength + 1]; //Text Length + New Text Length + NULL-Charset
		memcpy(text, oldText, textLength);
		memcpy(text + textLength, addedString, addedStringLength);
		text[textLength + addedStringLength] = NULL;
		textLength += addedStringLength;
		delete oldText;
	}
	void popText()
	{
		if (textLength <= 0)
			return;
		char* oldText = text;
		text = new char[textLength]; //Text Length - 1 + NULL-Charset
		memcpy(text, oldText, textLength - 1);
		text[textLength - 1] = NULL;
		textLength--;
		delete oldText;
	}

	char* getText()
	{
		return stringCopy(text, textLength);
	}
	int getTextLength()
	{
		return textLength;
	}
};