#include "ccircle.h"

CCircle::CCircle(POINT p)
{
    center = p;
    radius = 10;
}

CCircle::~CCircle()
{
}

void CCircle::Update(RECT* rectView, POINT p)
{
    // 왼쪽
    if (center.x - radius <= rectView->left)
    {
        center.x = rectView->left + radius;
    }
    // 오른쪽
    if (center.x + radius >= rectView->right)
    {
        center.x = rectView->right - radius;
    }
    // 위
    if (center.y - radius <= rectView->top)
    {
        center.y = rectView->top + radius;
    }
    // 아래
    if (center.y - radius >= rectView->bottom)
    {
        center.y = rectView->bottom - radius;
    }

    center = p;
}

void CCircle::Draw(HDC hdc)
{
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}
