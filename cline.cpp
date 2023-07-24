#include "pch.h"
#include "CLine.h"
#include "CPlayer.h"
#include "CSceneMgr.h"
#include "CScene.h"

CLine::CLine()
	: vEnd(Vec2(0, 0))
{
}

CLine::~CLine()
{
}

void CLine::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CObject* pPlayer = pCurScene->GetPlayer();
	Vec2 vPos = pPlayer->GetPos();
	vEnd = vPos;
}

void CLine::render(HDC _dc)
{
	Vec2 vStart = GetPos();

	MoveToEx(_dc, vStart.x, vStart.y, NULL);
	LineTo(_dc, vEnd.x, vEnd.y);
}
