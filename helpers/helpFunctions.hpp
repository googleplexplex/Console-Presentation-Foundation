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
	int x, y;

	point operator+(point& right)
	{
		return { x + right.x, y + right.y };
	}
	point operator-(point& right)
	{
		return { x - right.x, y - right.y };
	}
};
struct rectangle
{
	point firstPos;
	point secondPos;

	point getSize()
	{
		return { secondPos.x - firstPos.x, secondPos.y - firstPos.y };
	}
};
struct marginType
{
	int Left;
	int Top;
	int Right;
	int Down;

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
template<typename A, typename B>
struct pair
{
	A first;
	B second;

	bool operator==(pair<A, B>& right)
	{
		return ( first == right.first
			&& second == right.second);
	}
};
template<typename A, typename B>
pair<A, B> makePair(A first, B second)
{
	return pair<A, B>({ first, second });
}