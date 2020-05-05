#pragma once
#include <windows.h>

HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

COORD getConsoleSize() //Getting console window size
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hStdout, &consoleInfo);
	short widht = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	short height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
	return { widht, height };
}

CHAR_INFO* getAll_fromConsole()
{
	COORD consoleSize = getConsoleSize();
	SMALL_RECT srctReadRect;
	CHAR_INFO* charBuffer = new CHAR_INFO[consoleSize.Y * consoleSize.X];
	COORD coordBufSize;

	//Set the source rectangle.
	srctReadRect.Top = 0;    //top left
	srctReadRect.Left = 0;
	srctReadRect.Bottom = consoleSize.Y - 1; // down right
	srctReadRect.Right = consoleSize.X - 1;

	//The size of the temporary buffer is the size of the console.
	coordBufSize.Y = consoleSize.Y;
	coordBufSize.X = consoleSize.X;

	//Copy the block from the screen buffer to a temporary buffer.
	ReadConsoleOutput(
		hStdout,        	//Screen buffer from which we read
		charBuffer,      	//Buffer to copy to
		coordBufSize,   	//Column / row size
		{ 0, 0 },  	//up left
		&srctReadRect); 	//Screen buffer source rectangle

	return charBuffer;
}
char* getAll_fromConsoleA()
{
	//Everything you need to process
	CHAR_INFO* ret_ci = getAll_fromConsole();
	COORD consoleSize = getConsoleSize();
	size_t allConsleCharsCount = consoleSize.Y * consoleSize.X;
	char* ret_a = new char[allConsleCharsCount];

	//Treatment
	for (int i = 0; i < allConsleCharsCount; i++)
	{
		ret_a[i] = ret_ci[i].Char.AsciiChar;
	}

	return ret_a;
}
char* getAll_fromConsoleAN()
{
	//Everything you need to process
	CHAR_INFO* ret_ci = getAll_fromConsole();
	COORD consoleSize = getConsoleSize();
	size_t allConsleCharsCount = consoleSize.Y * consoleSize.X;
	char* ret_a = new char[allConsleCharsCount + consoleSize.Y];

	//Treatment
	for (int i = 0; i < consoleSize.Y; i++)
	{
		bool lastIteration = (i == consoleSize.Y - 1);
		for (int j = 0; j < consoleSize.X; j++)
		{
			ret_a[i * consoleSize.X + j + i] = ret_ci[i * consoleSize.X + j].Char.AsciiChar;
		}
		if (!lastIteration)
			ret_a[i * consoleSize.X + consoleSize.X + i] = '\n';
	}
	ret_a[allConsleCharsCount + consoleSize.Y - 1] = NULL;

	return ret_a;
}
wchar_t* getAll_fromConsoleU()
{
	//Everything you need to process
	CHAR_INFO* ret_ci = getAll_fromConsole();
	COORD consoleSize = getConsoleSize();
	size_t allConsleCharsCount = consoleSize.Y * consoleSize.X;
	wchar_t* ret_u = new wchar_t[allConsleCharsCount];

	//Treatment
	for (int i = 0; i < allConsleCharsCount; i++)
	{
		ret_u[i] = ret_ci[i].Char.UnicodeChar;
	}

	return ret_u;
}
wchar_t* getAll_fromConsoleUN()
{
	//Everything you need to process
	CHAR_INFO* ret_ci = getAll_fromConsole();
	COORD consoleSize = getConsoleSize();
	size_t allConsleCharsCount = consoleSize.Y * consoleSize.X;
	wchar_t* ret_u = new wchar_t[allConsleCharsCount];

	//Treatment
	for (int i = 0; i < consoleSize.Y; i++)
	{
		bool lastIteration = (i == consoleSize.Y - 1);
		for (int j = 0; j < consoleSize.X; j++)
		{
			ret_u[i * consoleSize.X + j + i] = ret_ci[i * consoleSize.X + j].Char.UnicodeChar;
		}
		if (!lastIteration)
			ret_u[i * consoleSize.X + consoleSize.X + i] = '\n';
	}
	ret_u[allConsleCharsCount + consoleSize.Y - 1] = NULL;

	return ret_u;
}

CHAR_INFO* getRect_fromConsole(short x, short y, short xsize, short ysize)
{
	SMALL_RECT srctReadRect;
	CHAR_INFO* charBuffer = new CHAR_INFO[ysize * xsize];
	COORD coordBufSize;

	srctReadRect.Top = y;
	srctReadRect.Left = x;
	srctReadRect.Bottom = y + ysize - 1;
	srctReadRect.Right = x + xsize - 1;

	coordBufSize.Y = ysize;
	coordBufSize.X = xsize;

	ReadConsoleOutput(hStdout, charBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	return charBuffer;
}
char* getRect_fromConsoleA(short x, short y, short xsize, short ysize)
{
	CHAR_INFO* ret_ci = getRect_fromConsole(x, y, xsize, ysize);
	int allRectCharsCount = ysize * xsize;
	char* ret_a = new char[allRectCharsCount + 1];

	for (int i = 0; i < allRectCharsCount + 1; i++)
	{
		ret_a[i] = ret_ci[i].Char.AsciiChar;
	}
	ret_a[allRectCharsCount] = NULL;

	return ret_a;
}
char* getRect_fromConsoleAN(short x, short y, short xsize, short ysize)
{
	CHAR_INFO* ret_ci = getRect_fromConsole(x, y, xsize, ysize);
	int allRectCharsCount = ysize * xsize;
	char* ret_a = new char[allRectCharsCount + ysize];

	for (int i = 0; i < ysize; i++)
	{
		bool lastIteration = (i == ysize - 1);
		for (int j = 0; j < xsize; j++)
		{
			ret_a[i * xsize + j + i] = ret_ci[i * xsize + j].Char.AsciiChar;
		}
		if (!lastIteration)
			ret_a[i * xsize + xsize + i] = '\n';
	}
	ret_a[allRectCharsCount + ysize - 1] = NULL;

	return ret_a;
}
wchar_t* getRect_fromConsoleU(short x, short y, short xsize, short ysize)
{
	CHAR_INFO* ret_ci = getRect_fromConsole(x, y, xsize, ysize);
	int allRectCharsCount = ysize * xsize;
	wchar_t* ret_u = new wchar_t[allRectCharsCount + 1];

	for (int i = 0; i < allRectCharsCount + 1; i++)
	{
		ret_u[i] = ret_ci[i].Char.UnicodeChar;
	}
	ret_u[allRectCharsCount] = NULL;

	return ret_u;
}
wchar_t* getRect_fromConsoleUN(short x, short y, short xsize, short ysize)
{
	CHAR_INFO* ret_ci = getRect_fromConsole(x, y, xsize, ysize);
	int allRectCharsCount = ysize * xsize;
	wchar_t* ret_u = new wchar_t[allRectCharsCount + ysize];

	for (int i = 0; i < ysize; i++)
	{
		bool lastIteration = (i == ysize - 1);
		for (int j = 0; j < xsize; j++)
		{
			ret_u[i * xsize + j + i] = ret_ci[i * xsize + j].Char.UnicodeChar;
		}
		if (!lastIteration)
			ret_u[i * xsize + xsize + i] = '\n';
	}
	ret_u[allRectCharsCount + ysize - 1] = NULL;

	return ret_u;
}

CHAR_INFO* gets_fromConsole(short x, short y, short xsize)
{
	SMALL_RECT srctReadRect;
	CHAR_INFO* charBuffer = new CHAR_INFO[xsize];
	COORD coordBufSize;

	srctReadRect.Top = y;
	srctReadRect.Left = x;
	srctReadRect.Bottom = y + 1;
	srctReadRect.Right = x + xsize - 1;

	coordBufSize.Y = 1;
	coordBufSize.X = xsize;

	ReadConsoleOutput(hStdout, charBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	return charBuffer;
}
char* gets_fromConsoleA(short x, short y, short xsize)
{
	CHAR_INFO* ret_ci = gets_fromConsole(x, y, xsize);
	int allRectCharsCount = xsize;
	char* ret_a = new char[allRectCharsCount + 1];

	for (int i = 0; i < allRectCharsCount; i++)
	{
		ret_a[i] = ret_ci[i].Char.AsciiChar;
	}
	ret_a[allRectCharsCount] = NULL;

	return ret_a;
}
wchar_t* gets_fromConsoleU(short x, short y, short xsize)
{
	CHAR_INFO* ret_ci = gets_fromConsole(x, y, xsize);
	int allRectCharsCount = xsize;
	wchar_t* ret_u = new wchar_t[allRectCharsCount + 1];

	for (int i = 0; i < allRectCharsCount; i++)
	{
		ret_u[i] = ret_ci[i].Char.UnicodeChar;
	}
	ret_u[allRectCharsCount] = NULL;

	return ret_u;
}

CHAR_INFO getc_fromConsole(short x, short y)
{
	SMALL_RECT srctReadRect;
	CHAR_INFO* charBuffer = new CHAR_INFO[1];
	COORD coordBufSize;

	srctReadRect.Top = y;
	srctReadRect.Left = x;
	srctReadRect.Bottom = y + 1;
	srctReadRect.Right = x + 1;

	coordBufSize.Y = x + 1;
	coordBufSize.X = y + 1;

	ReadConsoleOutput(hStdout, charBuffer, coordBufSize, { 0, 0 }, &srctReadRect);

	return charBuffer[0];
}
char getc_fromConsoleA(short x, short y)
{
	//Just return the item received, but of the return type
	return getc_fromConsole(x, y).Char.AsciiChar;
}
wchar_t getc_fromConsoleU(short x, short y)
{
	//Just return the item received, but of the return type
	return getc_fromConsole(x, y).Char.UnicodeChar;
}