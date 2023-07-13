#include "cline.h"

CLine::CLine(POINT p)
{
	start = p;
	end = p;
}

CLine::~CLine()
{
}

void CLine::Draw(HDC hdc)
{
	MoveToEx(hdc, start.x, start.y, NULL);
	LineTo(hdc, end.x, end.y);
}

void CLine::SetEnd(POINT p)
{
	end = p;
}
