#pragma once
#include "CObject.h"


class CKineticObject :
    public CObject
{
private:
    Vec2 m_vScale;

public:
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    Vec2 GetScale() { return m_vScale; }

public:
    virtual void update() = 0;
    virtual void render(HDC _dc);

public:
    CKineticObject();
    virtual ~CKineticObject();
};

