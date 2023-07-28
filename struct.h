#pragma once

struct Vec2
{
	int x;
	int y;

public :
	Vec2& operator = (POINT _pt)
	{
		x = _pt.x;
		y = _pt.y;
	}

public:
	Vec2()
		: x(0)
		, y(0)
	{}

	Vec2(int _x, int _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(const POINT& _pt)
		: x(_pt.x)
		, y(_pt.y)
	{}
};