#pragma once

#define moreThanNull(x) (x > 0)
#define setBorder(x, y, z) if(x < y) { x = y; } if(x > z) { x = z; }
#define getBorder(pos, min, max) ((min) <= (pos) && (pos) <= (max))


#define identifySetterOf(element)\
void set##element(decltype(element) setted##element)\
{\
element = setted##element;\
}
#define identifyGetterOf(element)\
decltype(element) get##element()\
{\
return element;\
}
#define identifySetterAndGetterOf(element)\
identifySetterOf(element)\
identifyGetterOf(element)

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
bool stringCompare(char* firstString, char* secondString)
{
	int firstStringLen = strlen(firstString);
	int secondStringLen = strlen(secondString);

	if (firstStringLen != secondStringLen)
		return false;

	for (int i = 0; i < firstStringLen; i++)
	{
		if (firstString[i] != secondString[i])
			return false;
	}

	return true;
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

struct point
{
	unsigned int x, y;

	point operator+(point& right)
	{
		return { x + right.x, y + right.y };
	}
	point operator-(point& right)
	{
		return { x - right.x, y - right.y };
	}
	point operator/(point& right)
	{
		return { x / right.x, y / right.y };
	}
	point operator*(point& right)
	{
		return { x * right.x, y * right.y };
	}

	bool operator==(point& right)
	{
		return ((x == right.x) && (y == right.y));
	}
	bool operator!=(point& right)
	{
		return !((*this)==right);
	}
};
constexpr point emptyPoint = { 0, 0 };

struct rectangle
{
	point firstPos;
	point secondPos;

	point getSize()
	{
		return (secondPos - firstPos);
	}
};

struct marginType
{
	unsigned int Left;
	unsigned int Top;
	unsigned int Right;
	unsigned int Down;

	bool operator==(marginType right)
	{
		return (Top == right.Top
			&& Down == right.Down
			&& Left == right.Left
			&& Right == right.Right);
	}
};
marginType makeMargin(point _pos, point _size, point _sizeCont)
{
	return { _pos.x, _pos.y, _sizeCont.x - _pos.x - _size.x, _sizeCont.y - _pos.y - _size.y };
}