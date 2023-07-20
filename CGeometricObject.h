#pragma once
#include "CObject.h"


class CGeometricObject
	: public CObject
{
private:
	Vec2 m_vPos;

public:
	virtual void update() = 0;
	virtual void render(HDC _dc) = 0;

public:
	Vec2 GetPos() { return m_vPos; }

public:
	CGeometricObject();
	virtual ~CGeometricObject();
};

