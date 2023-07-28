#include "pch.h"
#include "CKineticObject.h"

CKineticObject::CKineticObject()
{
}

CKineticObject::~CKineticObject()
{
}

void CKineticObject::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Rectangle(_dc, vPos.x - m_vScale.x / 2, vPos.y - m_vScale.y / 2
		, vPos.x + m_vScale.x / 2, vPos.y + m_vScale.y / 2);
}
