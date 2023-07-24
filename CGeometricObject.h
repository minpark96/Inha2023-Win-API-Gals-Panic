#pragma once
#include "CObject.h"


class CGeometricObject
	: public CObject
{
private:

public:
	virtual void update() = 0;
	virtual void render(HDC _dc) = 0;

public:

public:
	CGeometricObject();
	virtual ~CGeometricObject();
};

