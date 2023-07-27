#pragma once
#include "CKineticObject.h"
#include "CLine.h"

enum class DIR
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

class CPlayer :
    public CKineticObject
{
private:
    vector<bool> m_vecPushed;
    CLine* m_currLine;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();
    void CreateLine();

public:
    CPlayer();
    ~CPlayer();
};

