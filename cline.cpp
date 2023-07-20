#include "pch.h"
#include "CLine.h"

CLine::CLine()
	: vEnd(Vec2(0, 0))
{
}

CLine::~CLine()
{
}

void CLine::update()
{
	


}

void CLine::render(HDC _dc)
{
	Vec2 vStart = GetPos();

	MoveToEx(_dc, vStart.x, vStart.y, NULL);
	LineTo(_dc, vEnd.x, vEnd.y);
}
