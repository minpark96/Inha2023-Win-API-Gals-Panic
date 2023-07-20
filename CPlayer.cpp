#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"
#include "CLine.h"

CPlayer::CPlayer()
{
	for (int i = 0; i <= (int)DIR::DOWN; ++i)
	{
		m_vecPushed.push_back(false);
	}
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	Vec2 vPos = GetPos();
	
	// TODO: 스페이스 바를 안눌렀을 때는 선상으로만 이동가능

	if (KEY_HOLD(KEY::LEFT))
	{
		vPos.x -= 100.f * fDT;
	}
	else if (KEY_HOLD(KEY::RIGHT))
	{
		vPos.x += 100.f * fDT;
	}
	else if (KEY_HOLD(KEY::UP))
	{
		vPos.y -= 100.f * fDT;
	}
	else if (KEY_HOLD(KEY::DOWN))
	{
		vPos.y += 100.f * fDT;
	}
	else if (KEY_HOLD(KEY::SPACE))
	{
		// TODO: 이미 먹은 땅 내부로는 진입할 수 없다

		// 외부라면?
		// 방향전환 -> 선 추가
		int idxKey;

		if (KEY_TAP(KEY::LEFT))
		{
			idxKey = (int)DIR::LEFT;

			if (!m_vecPushed[idxKey])
			{
				// 선 객체 추가
			}

			for (int i = 0; i <= (int)DIR::DOWN; ++i)
			{
				if (i == idxKey)
					m_vecPushed[i] = true;
				else
					m_vecPushed[i] = false;
			}

			vPos.x -= 100.f * fDT;
		}
		else if (KEY_TAP(KEY::RIGHT))
		{
			idxKey = (int)DIR::RIGHT;

			if (!m_vecPushed[idxKey])
			{
				// 선 객체 추가
			}

			for (int i = 0; i <= (int)DIR::DOWN; ++i)
			{
				if (i == idxKey)
					m_vecPushed[i] = true;
				else
					m_vecPushed[i] = false;
			}

			vPos.x += 100.f * fDT;
		}
		else if (KEY_TAP(KEY::UP))
		{
			idxKey = (int)DIR::UP;

			if (!m_vecPushed[idxKey])
			{
				// 선 객체 추가
			}

			for (int i = 0; i <= (int)DIR::DOWN; ++i)
			{
				if (i == idxKey)
					m_vecPushed[i] = true;
				else
					m_vecPushed[i] = false;
			}

			vPos.y -= 100.f * fDT;
		}
		else if (KEY_TAP(KEY::DOWN))
		{
			idxKey = (int)DIR::DOWN;

			if (!m_vecPushed[idxKey])
			{
				// 선 객체 추가
			}

			for (int i = 0; i <= (int)DIR::DOWN; ++i)
			{
				if (i == idxKey)
					m_vecPushed[i] = true;
				else
					m_vecPushed[i] = false;
			}

			vPos.y += 100.f * fDT;
		}
		// 누르고 있는 상태 -> 선 연장
		else if (KEY_HOLD(KEY::LEFT))
		{
			vPos.x -= 100.f * fDT;
		}
		else if (KEY_HOLD(KEY::RIGHT))
		{
			vPos.x += 100.f * fDT;
		}
		else if (KEY_HOLD(KEY::UP))
		{
			vPos.y -= 100.f * fDT;
		}
		else if (KEY_HOLD(KEY::DOWN))
		{
			vPos.y += 100.f * fDT;
		}
	}
	else if (KEY_AWAY(KEY::SPACE))
	{
		// TODO: 그렸던 경로 되돌아가기 + 선도 같이 사라짐

	}

	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_dc, hBrush);

	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

    SelectObject(_dc, oldBrush);
    DeleteObject(hBrush);  
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(true);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

void CPlayer::CreateLine()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Line Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(true);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
