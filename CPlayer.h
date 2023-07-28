#pragma once
#include "CKineticObject.h"
#include "CLine.h"

class CPlayer :
    public CKineticObject
{
private:
    vector<bool> m_vecPushed;
    vector<vector<Vec2>> m_vecLine;
    int m_iIdx;
    int m_iSpeed;
    double m_dAccumX;
    double m_dAccumY;
    Vec2 m_vDelta;
    int m_iCurKey;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();
    void DrawLine();

public:
    CPlayer();
    ~CPlayer();
};

