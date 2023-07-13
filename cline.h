#pragma once
#include "framework.h"

class CLine
{
private:
	POINT start, end;
public:
	CLine(POINT p);
	~CLine();

	void Draw(HDC hdc);

	void SetEnd(POINT p);
};

