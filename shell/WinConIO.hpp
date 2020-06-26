#pragma once
#include <windows.h>

#define CONREADER

#ifdef UNICODE
#define getAllFromConsole getAllFromConsoleW
#define getRectFromConsole getRectFromConsoleW
#define getStringFromConsole getStringFromConsoleW
#define getCharFromConsole  getCharFromConsoleW
#else
#define getAllFromConsole getAllFromConsoleA
#define getRectFromConsole getRectFromConsoleA
#define getStringFromConsole getStringFromConsoleA
#define getCharFromConsole  getCharFromConsoleA
#endif

#ifndef CONWRITER
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

COORD getConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hStdout, &consoleInfo);
	short widht = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	short height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
	return { widht, height };
}
#endif

DWORD* lastFunctionOut = new DWORD();

CHAR_INFO* getAllFromConsoleCI()
{
	COORD consoleSize = getConsoleSize();
	SMALL_RECT srctReadRect = { 0, 0, consoleSize.X - 1, consoleSize.Y - 1 };
	CHAR_INFO* charBuffer = new CHAR_INFO[consoleSize.Y * consoleSize.X];
	COORD coordBufSize = { consoleSize.X, consoleSize.Y };

	ReadConsoleOutput(
		hStdout,        	//Screen buffer from which we read
		charBuffer,      	//Buffer to copy to
		coordBufSize,   	//Column / row size
		{ 0, 0 },  			//up left
		&srctReadRect); 	//Screen buffer source rectangle

	return charBuffer;
}
char* getAllFromConsoleA()
{
	COORD consoleSize = getConsoleSize();
	SMALL_RECT srctReadRect = { 0, 0, consoleSize.X - 1, consoleSize.Y - 1 };
	int charsInConsoleCount = consoleSize.Y * consoleSize.X;
	CHAR_INFO* charBuffer = new CHAR_INFO[charsInConsoleCount];
	COORD coordBufSize = { consoleSize.X, consoleSize.Y };
	char* result = new char[charsInConsoleCount];

	ReadConsoleOutputA(hStdout, charBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	for (int i = 0; i < charsInConsoleCount; i++)
	{
		result[i] = charBuffer[i].Char.AsciiChar;
	}

	delete[] charBuffer;
	return result;
}
char* getAllFromConsoleAN()
{
	COORD consoleSize = getConsoleSize();
	SMALL_RECT srctReadRect = { 0, 0, consoleSize.X - 1, consoleSize.Y - 1 };
	int charsInConsoleCount = consoleSize.Y * consoleSize.X;
	CHAR_INFO* charBuffer = new CHAR_INFO[charsInConsoleCount];
	COORD coordBufSize = { consoleSize.X, consoleSize.Y };
	char* result = new char[charsInConsoleCount];

	ReadConsoleOutputA(hStdout, charBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	for (int i = 0; i < consoleSize.Y; i++)
	{
		bool lastIteration = (i == consoleSize.Y - 1);
		for (int j = 0; j < consoleSize.X; j++)
		{
			result[i * consoleSize.X + j + i] = charBuffer[i * consoleSize.X + j].Char.AsciiChar;
		}
		if (!lastIteration)
			result[i * consoleSize.X + consoleSize.X + i] = '\n';
	}
	result[charsInConsoleCount + consoleSize.Y - 1] = NULL;

	delete[] charBuffer;
	return result;
}
wchar_t* getAllFromConsoleW()
{
	COORD consoleSize = getConsoleSize();
	SMALL_RECT srctReadRect = { 0, 0, consoleSize.X - 1, consoleSize.Y - 1 };
	int charsInConsoleCount = consoleSize.Y * consoleSize.X;
	CHAR_INFO* charBuffer = new CHAR_INFO[charsInConsoleCount];
	COORD coordBufSize = { consoleSize.X, consoleSize.Y };
	wchar_t* result = new wchar_t[charsInConsoleCount];

	ReadConsoleOutputW(hStdout, charBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	for (int i = 0; i < charsInConsoleCount; i++)
	{
		result[i] = charBuffer[i].Char.UnicodeChar;
	}

	delete[] charBuffer;
	return result;
}
wchar_t* getAllFromConsoleWN()
{
	COORD consoleSize = getConsoleSize();
	SMALL_RECT srctReadRect = { 0, 0, consoleSize.X - 1, consoleSize.Y - 1 };
	int charsInConsoleCount = consoleSize.Y * consoleSize.X;
	CHAR_INFO* charBuffer = new CHAR_INFO[charsInConsoleCount];
	COORD coordBufSize = { consoleSize.X, consoleSize.Y };
	wchar_t* result = new wchar_t[charsInConsoleCount];

	ReadConsoleOutputW(hStdout, charBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	for (int i = 0; i < consoleSize.Y; i++)
	{
		bool lastIteration = (i == consoleSize.Y - 1);
		for (int j = 0; j < consoleSize.X; j++)
		{
			result[i * consoleSize.X + j + i] = charBuffer[i * consoleSize.X + j].Char.UnicodeChar;
		}
		if (!lastIteration)
			result[i * consoleSize.X + consoleSize.X + i] = '\n';
	}
	result[charsInConsoleCount + consoleSize.Y - 1] = NULL;

	delete[] charBuffer;
	return result;
}

CHAR_INFO* getRectFromConsoleCI(SMALL_RECT& srctReadRect)
{
	COORD coordBufSize = { srctReadRect.Right - srctReadRect.Left, srctReadRect.Bottom - srctReadRect.Top };
	CHAR_INFO* charBuffer = new CHAR_INFO[coordBufSize.X * coordBufSize.Y];

	ReadConsoleOutput(hStdout, charBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	return charBuffer;
}
char* getRectFromConsoleA(SMALL_RECT& srctReadRect)
{
	COORD coordBufSize = { srctReadRect.Right - srctReadRect.Left, srctReadRect.Bottom - srctReadRect.Top };
	int allRectCharsCount = coordBufSize.X * coordBufSize.Y;
	CHAR_INFO* charInfoBuffer = new CHAR_INFO[allRectCharsCount];
	char* result = new char[allRectCharsCount + 1];

	ReadConsoleOutputA(hStdout, charInfoBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	for (int i = 0; i < allRectCharsCount + 1; i++)
	{
		result[i] = charInfoBuffer[i].Char.AsciiChar;
	}
	result[allRectCharsCount] = NULL;

	delete[] charInfoBuffer;
	return result;
}
char* getRectFromConsoleAN(SMALL_RECT& srctReadRect)
{
	COORD coordBufSize = { srctReadRect.Right - srctReadRect.Left, srctReadRect.Bottom - srctReadRect.Top };
	int allRectCharsCount = coordBufSize.X * coordBufSize.Y;
	CHAR_INFO* charInfoBuffer = new CHAR_INFO[allRectCharsCount];
	char* result = new char[allRectCharsCount + 1];

	ReadConsoleOutputA(hStdout, charInfoBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	for (int i = 0; i < coordBufSize.Y; i++)
	{
		bool lastIteration = (i == coordBufSize.Y - 1);
		for (int j = 0; j < coordBufSize.X; j++)
		{
			result[i * coordBufSize.X + j + i] = charInfoBuffer[i * coordBufSize.X + j].Char.AsciiChar;
		}
		if (!lastIteration)
			result[i * coordBufSize.X + coordBufSize.X + i] = '\n';
	}
	result[allRectCharsCount + coordBufSize.Y - 1] = NULL;

	delete[] charInfoBuffer;
	return result;
}
wchar_t* getRectFromConsoleW(SMALL_RECT& srctReadRect)
{
	COORD coordBufSize = { srctReadRect.Right - srctReadRect.Left, srctReadRect.Bottom - srctReadRect.Top };
	int allRectCharsCount = coordBufSize.X * coordBufSize.Y;
	CHAR_INFO* charInfoBuffer = new CHAR_INFO[allRectCharsCount];
	wchar_t* result = new wchar_t[allRectCharsCount + 1];

	ReadConsoleOutputW(hStdout, charInfoBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	for (int i = 0; i < allRectCharsCount + 1; i++)
	{
		result[i] = charInfoBuffer[i].Char.UnicodeChar;
	}
	result[allRectCharsCount] = NULL;

	delete[] charInfoBuffer;
	return result;
}
wchar_t* getRectFromConsoleWN(SMALL_RECT& srctReadRect)
{
	COORD coordBufSize = { srctReadRect.Right - srctReadRect.Left, srctReadRect.Bottom - srctReadRect.Top };
	int allRectCharsCount = coordBufSize.X * coordBufSize.Y;
	CHAR_INFO* charInfoBuffer = new CHAR_INFO[allRectCharsCount];
	wchar_t* result = new wchar_t[allRectCharsCount + 1];

	ReadConsoleOutputW(hStdout, charInfoBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	for (int i = 0; i < coordBufSize.Y; i++)
	{
		bool lastIteration = (i == coordBufSize.Y - 1);
		for (int j = 0; j < coordBufSize.X; j++)
		{
			result[i * coordBufSize.X + j + i] = charInfoBuffer[i * coordBufSize.X + j].Char.UnicodeChar;
		}
		if (!lastIteration)
			result[i * coordBufSize.X + coordBufSize.X + i] = '\n';
	}
	result[allRectCharsCount + coordBufSize.Y - 1] = NULL;

	delete[] charInfoBuffer;
	return result;
}

CHAR_INFO* getStringFromConsoleCI(COORD stringPos, short size)
{
	SMALL_RECT srctReadRect = { stringPos.X, stringPos.Y, stringPos.X + size + 1, stringPos.Y + 1 };
	CHAR_INFO* charBuffer = new CHAR_INFO[size];
	COORD coordBufSize = { size, 1 };

	ReadConsoleOutput(hStdout, charBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	return charBuffer;
}
char* getStringFromConsoleA(COORD stringPos, short size, DWORD* out = lastFunctionOut)
{
	LPSTR result = new char[size];
	ReadConsoleOutputCharacterA(hStdout, result, size, stringPos, out);

	return result;
}
wchar_t* getStringFromConsoleW(COORD stringPos, short size, DWORD* out = lastFunctionOut)
{
	LPWSTR result = new wchar_t[size];
	ReadConsoleOutputCharacterW(hStdout, result, size, stringPos, out);

	return result;
}
WORD* getAttributesFromConsole(COORD gettedPos, short size, DWORD* out = lastFunctionOut)
{
	WORD* result = new WORD[size];
	ReadConsoleOutputAttribute(hStdout, result, size, gettedPos, out);

	return result;
}

CHAR_INFO getCharFromConsoleCI(COORD charsetPos)
{
	SMALL_RECT srctReadRect = { charsetPos.X, charsetPos.Y, charsetPos.X + 1, charsetPos.Y + 1 };
	CHAR_INFO result;
	COORD coordBufSize = { 1, 1 };

	ReadConsoleOutput(hStdout, &result, coordBufSize, { 0, 0 }, &srctReadRect);

	return result;
}
char getCharFromConsoleA(COORD charsetPos, DWORD* out = lastFunctionOut)
{
	char result;
	ReadConsoleOutputCharacterA(hStdout, &result, 1, charsetPos, out);

	return result;
}
wchar_t getCharFromConsoleW(COORD charsetPos, DWORD* out = lastFunctionOut)
{
	wchar_t result;
	ReadConsoleOutputCharacterW(hStdout, &result, 1, charsetPos, out);

	return result;
}
WORD getAttributesFromConsole(COORD gettedPos, DWORD* out = lastFunctionOut)
{
	WORD result;
	ReadConsoleOutputAttribute(hStdout, &result, 1, gettedPos, out);

	return result;
}


#define CONWRITER

#ifdef UNICODE
#define setAllConsole setAllConsoleW
#define setRectInConsole setRectInConsoleW
#define setLineInConsole setLineInConsoleW
#define setStringInConsole setStringInConsoleW
#define setCharInConsole setCharInConsoleW
#else
#define setAllConsole setAllConsoleA
#define setRectInConsole setRectInConsoleA
#define setLineInConsole setLineInConsoleA
#define setStringInConsole setStringInConsoleA
#define setCharInConsole setCharInConsoleA
#endif

#ifndef CONREADER
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

COORD getConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hStdout, &consoleInfo);
	short widht = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	short height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
	return { widht, height };
}
#endif

constexpr char brushedAsciiChar = (char)219;
constexpr char emptyAsciiChar = ' ';
constexpr wchar_t brushedUnicodeChar = (wchar_t)219;
constexpr wchar_t emptyUnicodeChar = (wchar_t)' ';
constexpr WORD standartAttribute = 7;
constexpr CHAR_INFO brushedChaInfo = { brushedAsciiChar, standartAttribute };
constexpr CHAR_INFO emptyCharInfo = { emptyAsciiChar, standartAttribute };

template <typename T>
T* getFilledBuffer(T fillElement, int bufferSize)
{
	T* result = new T[bufferSize];

	//If sizeof(T) > sizeof(int), memset will not work
	for (int i = 0; i < bufferSize; i++)
	{
		result[i] = fillElement;
	}

	return result;
}


void setAllConsoleCI(CHAR_INFO filledChar = emptyCharInfo)
{
	COORD consoleSize = getConsoleSize();
	SMALL_RECT srctReadRect = { 0, 0, consoleSize.X - 1, consoleSize.Y - 1 };
	COORD coordBufSize = { consoleSize.X, consoleSize.Y };
	CHAR_INFO* charInfoBuffer = getFilledBuffer(filledChar, consoleSize.X * consoleSize.Y);

	WriteConsoleOutput(hStdout, charInfoBuffer, coordBufSize, { 0, 0 }, &srctReadRect);
	delete[] charInfoBuffer;
}

void setAllConsoleA(char filledChar = emptyAsciiChar, WORD filledCharAttribute = standartAttribute)
{
	CHAR_INFO charset = { filledChar, filledCharAttribute };
	setAllConsoleCI(charset);
}

void setAllConsoleW(wchar_t filledChar = emptyUnicodeChar, WORD filledCharAttribute = standartAttribute)
{
	CHAR_INFO charset = { filledChar, filledCharAttribute };
	setAllConsoleCI(charset);
}


void setRectInConsoleCI(SMALL_RECT& filledRect, CHAR_INFO filledChar = emptyCharInfo)
{
	COORD filledRectSize = { filledRect.Right - filledRect.Left, filledRect.Bottom - filledRect.Top };
	int charsCountInConsole = filledRectSize.X * filledRectSize.Y;

	CHAR_INFO* charInfoBuffer = new CHAR_INFO[charsCountInConsole];
	for (int i = 0; i < charsCountInConsole; i++)
	{
		charInfoBuffer[i] = filledChar;
	}

	WriteConsoleOutput(hStdout, charInfoBuffer, filledRectSize, { 0, 0 }, &filledRect);
	delete[] charInfoBuffer;
}

void setRectInConsoleA(SMALL_RECT& filledRect, char filledChar = emptyAsciiChar, WORD filledCharAttribute = standartAttribute)
{
	CHAR_INFO charset = { filledChar, filledCharAttribute };
	setRectInConsoleCI(filledRect, charset);
}

void setRectInConsoleW(SMALL_RECT& filledRect, wchar_t filledChar = emptyUnicodeChar, WORD filledCharAttribute = standartAttribute)
{
	CHAR_INFO charset = { filledChar, filledCharAttribute };
	setRectInConsoleCI(filledRect, charset);
}

void setRectInConsoleCI(SMALL_RECT& printedRect, CHAR_INFO* printedString, int printedStringSize, CHAR_INFO emptyChar = emptyCharInfo)
{
	COORD filledRectSize = { printedRect.Right - printedRect.Left, printedRect.Bottom - printedRect.Top };
	int charsCountInConsole = filledRectSize.X * filledRectSize.Y;

	CHAR_INFO* charInfoBuffer = new CHAR_INFO[charsCountInConsole];
	for (int i = 0; i < printedStringSize; i++)
	{
		charInfoBuffer[i] = printedString[i];
	}
	for (int i = printedStringSize; i < charsCountInConsole; i++)
	{
		charInfoBuffer[i] = emptyChar;
	}

	WriteConsoleOutput(hStdout, charInfoBuffer, filledRectSize, { 0, 0 }, &printedRect);
	delete[] charInfoBuffer;
}

void setRectInConsoleA(SMALL_RECT& printedRect, char* printedString, int printedStringSize, WORD printedStringAttributes = standartAttribute, CHAR_INFO emptyChar = emptyCharInfo)
{
	COORD filledRectSize = { printedRect.Right - printedRect.Left, printedRect.Bottom - printedRect.Top };
	int charsCountInConsole = filledRectSize.X * filledRectSize.Y;

	CHAR_INFO* charInfoBuffer = new CHAR_INFO[charsCountInConsole];
	for (int i = 0; i < printedStringSize; i++)
	{
		charInfoBuffer[i].Char.AsciiChar = printedString[i];
		charInfoBuffer[i].Attributes = printedStringAttributes;
	}
	for (int i = printedStringSize; i < charsCountInConsole; i++)
	{
		charInfoBuffer[i] = emptyChar;
	}

	WriteConsoleOutputA(hStdout, charInfoBuffer, filledRectSize, { 0, 0 }, &printedRect);
	delete[] charInfoBuffer;
}

void setRectInConsoleW(SMALL_RECT& printedRect, wchar_t* printedString, int printedStringSize, WORD printedStringAttributes = standartAttribute, CHAR_INFO emptyChar = emptyCharInfo)
{
	COORD filledRectSize = { printedRect.Right - printedRect.Left, printedRect.Bottom - printedRect.Top };
	int charsCountInConsole = filledRectSize.X * filledRectSize.Y;

	CHAR_INFO* charInfoBuffer = new CHAR_INFO[charsCountInConsole];
	for (int i = 0; i < printedStringSize; i++)
	{
		charInfoBuffer[i].Char.UnicodeChar = printedString[i];
		charInfoBuffer[i].Attributes = printedStringAttributes;
	}
	for (int i = printedStringSize; i < charsCountInConsole; i++)
	{
		charInfoBuffer[i] = emptyChar;
	}

	WriteConsoleOutputW(hStdout, charInfoBuffer, filledRectSize, { 0, 0 }, &printedRect);
	delete[] charInfoBuffer;
}


void setLineInConsoleCI(COORD linePos, CHAR_INFO lineChar, short lineSize)
{
	SMALL_RECT srctReadRect = { linePos.X, linePos.Y, linePos.X + lineSize, linePos.Y + 1 };
	COORD coordBufSize = { lineSize, 1 };
	CHAR_INFO* charInfoBuffer = getFilledBuffer(lineChar, lineSize);

	WriteConsoleOutput(hStdout, charInfoBuffer, coordBufSize, { 0, 0 }, &srctReadRect);
	delete[] charInfoBuffer;
}

void setLineInConsoleA(COORD linePos, char lineChar, short lineSize, WORD lineCharAttribute = standartAttribute)
{
	CHAR_INFO charset = { lineChar, lineCharAttribute };
	setLineInConsoleCI(linePos, charset, lineSize);
}

void setLineInConsoleW(COORD linePos, wchar_t lineChar, short lineSize, WORD lineCharAttribute = standartAttribute)
{
	CHAR_INFO charset = { lineChar, lineCharAttribute };
	setLineInConsoleCI(linePos, charset, lineSize);
}


void setStringInConsoleCI(COORD stringPos, CHAR_INFO* filledChar, short stringSize)
{
	SMALL_RECT srctReadRect = { stringPos.X, stringPos.Y, stringPos.X + stringSize, stringPos.Y + 1 };
	COORD coordBufSize = { stringSize, 1 };

	WriteConsoleOutput(hStdout, filledChar, coordBufSize, { 0, 0 }, &srctReadRect);
}

void setStringInConsoleA(COORD stringPos, char* filledChar, short stringSize, WORD filledCharAttribute = standartAttribute)
{
	CHAR_INFO* charBuffer = new CHAR_INFO[stringSize];
	for (int i = 0; i < stringSize; i++)
	{
		charBuffer[i].Char.AsciiChar = filledChar[i];
		charBuffer[i].Attributes = filledCharAttribute;
	}

	setStringInConsoleCI(stringPos, charBuffer, stringSize);
	delete[] charBuffer;
}
void setStringInConsoleA(COORD stringPos, char* filledChar, WORD filledCharAttribute = standartAttribute)
{
	setStringInConsoleA(stringPos, filledChar, strlen(filledChar), filledCharAttribute);
}

void setStringInConsoleW(COORD stringPos, wchar_t* filledChar, short stringSize, WORD filledCharAttribute = standartAttribute)
{
	CHAR_INFO* charBuffer = new CHAR_INFO[stringSize];
	for (int i = 0; i < stringSize; i++)
	{
		charBuffer[i].Char.UnicodeChar = filledChar[i];
		charBuffer[i].Attributes = filledCharAttribute;
	}

	setStringInConsoleCI(stringPos, charBuffer, stringSize);
	delete[] charBuffer;
}
void setStringInConsoleW(COORD stringPos, wchar_t* filledChar, WORD filledCharAttribute = standartAttribute)
{
	setStringInConsoleW(stringPos, filledChar, wcslen(filledChar), filledCharAttribute);
}


void setCharInConsoleCI(COORD settedCharPos, CHAR_INFO settedChar = emptyCharInfo)
{
	SMALL_RECT srctReadRect = { settedCharPos.X, settedCharPos.Y, settedCharPos.X + 1, settedCharPos.Y + 1 };
	COORD coordBufSize = { 1, 1 };

	WriteConsoleOutput(hStdout, &settedChar, coordBufSize, { 0, 0 }, &srctReadRect);
}

void setCharInConsoleA(COORD settedCharPos, char settedChar = emptyAsciiChar, WORD settedCharAttribute = standartAttribute)
{
	CHAR_INFO charset = { settedChar, settedCharAttribute };
	setCharInConsoleCI(settedCharPos, charset);
}

void setCharInConsoleW(COORD settedCharPos, wchar_t settedChar = emptyUnicodeChar, WORD settedCharAttribute = standartAttribute)
{
	CHAR_INFO charset = { settedChar, settedCharAttribute };
	setCharInConsoleCI(settedCharPos, charset);
}