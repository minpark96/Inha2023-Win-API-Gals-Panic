#include "pch.h"
#include "CScene_Start.h"

#include "CCore.h"
#include "CObject.h"
#include "CKineticObject.h"
#include "CPlayer.h"
#include "CMonster.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Object 추가
	CKineticObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(10, 10));
	pObj->SetScale(Vec2(20, 20));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//// 몬스터 배치
	//int iMonCount = 16;
	//float fMoveDist = 25.f;
	//float fObjScale = 50.f;


	//Vec2 vResolution = CCore::GetInst()->GetResolution();
	//float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

	//CMonster* pMosterObj = nullptr;

	//for(int i = 0; i < iMonCount; ++i)
	//{
	//	// Monster Object 추가
	//	pMosterObj = new CMonster;
	//	pMosterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
	//	pMosterObj->SetCenterPos(pMosterObj->GetPos());
	//	pMosterObj->SetMoveDistance(fMoveDist);
	//	pMosterObj->SetScale(Vec2(fObjScale, fObjScale));
	//	AddObject(pMosterObj, GROUP_TYPE::DEFAULT);
	//}
}

void CScene_Start::Exit()
{
}

