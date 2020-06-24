#pragma once

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