#pragma once
#include "shell\graphics.hpp"
#include "helpers\helpFunctions.hpp"

class textModule
{
protected:
	char* text;
	int textLength;
	symbolColor textColor;
public:
	~textModule()
	{
		delete[] text;
	}

	void setText(char* settedText)
	{
		textLength = strlen(settedText);
		text = stringCopy(settedText, textLength);
	}
	void setText(char* settedText, int settedTextLength)
	{
		textLength = settedTextLength;
		text = stringCopy(settedText, textLength);
	}
	void setText(const char* settedText)
	{
		textLength = strlen(settedText);
		text = stringCopy(settedText, textLength);
	}
	void setText(const char* settedText, int settedTextLength)
	{
		textLength = settedTextLength;
		text = stringCopy(settedText, textLength);
	}
	void setTextColor(symbolColor settedTextColor)
	{
		textColor = settedTextColor;
	}

	char* getText()
	{
		return stringCopy(text, textLength);
	}
	int getTextLength()
	{
		return textLength;
	}
	symbolColor getSymbolColor()
	{
		return textColor;
	}
};