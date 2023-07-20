#pragma once
#include "CKineticObject.h"

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

