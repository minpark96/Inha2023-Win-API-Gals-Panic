#pragma once
#include "CGeometricObject.h"

class CLine
	: public CGeometricObject
{
private:
	Vec2 vEnd;

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	void SetEnd(Vec2 _p) { vEnd = _p; }

public:
	CLine();
	~CLine();
};

