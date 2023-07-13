#pragma once
#include "framework.h"

class CCircle
{
private:
	POINT center;
	int radius;
public:
	CCircle(POINT p);
	~CCircle();

	void Update(RECT* rectView, POINT p);
	void Draw(HDC hdc);
};

