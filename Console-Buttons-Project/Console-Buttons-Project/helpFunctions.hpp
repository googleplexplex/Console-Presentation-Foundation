#pragma once
#include <windows.h>

#define moreThanNull(x) (x > 0)
#define setBorder(x, y, z) if(x < y) { x = y; } if(x > z) { x = z; }
#define getBorder(pos, min, max) ((min) <= (pos) && (pos) <= (max))

char* stringCopy(char* string, int stringSize)
{
	char* result = new char[stringSize + 1];
	memcpy(result, string, stringSize + 1);
	return result;
}
char* stringCopy(const char* string, int stringSize)
{
	return stringCopy((char*)string, stringSize);
}


typedef enum orientationXEnum
{
	left = 0,
	centerX,
	right
};
typedef enum orientationYEnum
{
	up = 0,
	centerY,
	down
};

void emptyEvent(void*, POINT)
{
	return;
}