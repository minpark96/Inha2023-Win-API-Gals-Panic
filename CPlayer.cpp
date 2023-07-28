#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"
#include "CLine.h"

CPlayer::CPlayer()
	: m_vecLine()
	, m_iIdx(-1)
	, m_iSpeed(100)
	, m_dAccumX(0.0)
	, m_dAccumY(0.0)
	, m_vDelta()
	, m_iCurKey(0)
{
	for (int i = 0; i < (int)KEY::DOWN + 1; ++i)
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
	



	// 스페이스바을 눌렀는지에 따라 동작이 갈린다!

	// 스페이스바 누른 상태 (라인그리기)
	if (KEY_TAP(KEY::SPACE) || KEY_HOLD(KEY::SPACE))
	{
		// TODO: 이미 먹은 땅 내부 진입할 수 없다
		// 누른채로 선상을 탈수있다. 하지만 선은 외부진입 때만 그려진다.

		// 외부라면?
		// 방향전환 시 -> 선 추가

		if (KEY_TAP(KEY::LEFT))
		{
			m_iCurKey = (int)KEY::LEFT;

			if (m_vecPushed[m_iCurKey] == false)
			{
				// 선 객체 추가
				m_vecLine.push_back({ vPos, vPos });
				m_iIdx++;
			}

			for (int i = 0; i < (int)KEY::DOWN + 1; ++i)
			{
				if (i == m_iCurKey)
					m_vecPushed[i] = true;
				else
					m_vecPushed[i] = false;
			}

			m_dAccumX -= m_iSpeed * fDT;
			m_vDelta.x = (int)m_dAccumX;
			vPos.x += m_vDelta.x;
			m_dAccumX -= m_vDelta.x;
		}
		else if (KEY_TAP(KEY::RIGHT))
		{
			m_iCurKey = (int)KEY::RIGHT;

			if (m_vecPushed[m_iCurKey] == false)
			{
				// 선 객체 추가
				m_vecLine.push_back({ vPos, vPos });
				m_iIdx++;
			}

			for (int i = 0; i < (int)KEY::DOWN + 1; ++i)
			{
				if (i == m_iCurKey)
					m_vecPushed[i] = true;
				else
					m_vecPushed[i] = false;
			}

			m_dAccumX += m_iSpeed * fDT;
			m_vDelta.x = (int)m_dAccumX;
			vPos.x += m_vDelta.x;
			m_dAccumX -= m_vDelta.x;
		}
		else if (KEY_TAP(KEY::UP))
		{
			m_iCurKey = (int)KEY::UP;

			if (m_vecPushed[m_iCurKey] == false)
			{
				// 선 객체 추가
				m_vecLine.push_back({ vPos, vPos });
				m_iIdx++;
			}

			for (int i = 0; i < (int)KEY::DOWN + 1; ++i)
			{
				if (i == m_iCurKey)
					m_vecPushed[i] = true;
				else
					m_vecPushed[i] = false;
			}

			m_dAccumY -= m_iSpeed * fDT;
			m_vDelta.y = (int)m_dAccumY;
			vPos.y += m_vDelta.y;
			m_dAccumY -= m_vDelta.y;
		}
		else if (KEY_TAP(KEY::DOWN))
		{
			m_iCurKey = (int)KEY::DOWN;

			if (m_vecPushed[m_iCurKey] == false)
			{
				// 선 객체 추가
				m_vecLine.push_back({ vPos, vPos });
				m_iIdx++;
			}

			for (int i = 0; i < (int)KEY::DOWN + 1; ++i)
			{
				if (i == m_iCurKey)
					m_vecPushed[i] = true;
				else
					m_vecPushed[i] = false;
			}

			m_dAccumY += m_iSpeed * fDT;
			m_vDelta.y = (int)m_dAccumY;
			vPos.y += m_vDelta.y;
			m_dAccumY -= m_vDelta.y;
		}
		// 뭔가 하나라도 누르고 있는 중이면
		else if (KEY_HOLD(KEY::LEFT) ||
			KEY_HOLD(KEY::RIGHT) ||
			KEY_HOLD(KEY::UP) ||
			KEY_HOLD(KEY::DOWN))
		{
			// 우선권에 따라서 경로 진행
			switch (m_iCurKey)
			{
			case (int)KEY::LEFT:
				m_dAccumX -= m_iSpeed * fDT;
				m_vDelta.x = (int)m_dAccumX;
				vPos.x += m_vDelta.x;
				m_dAccumX -= m_vDelta.x;
				break;
			case (int)KEY::RIGHT:
				m_dAccumX += m_iSpeed * fDT;
				m_vDelta.x = (int)m_dAccumX;
				vPos.x += m_vDelta.x;
				m_dAccumX -= m_vDelta.x;
				break;
			case (int)KEY::UP:
				m_dAccumY -= m_iSpeed * fDT;
				m_vDelta.y = (int)m_dAccumY;
				vPos.y += m_vDelta.y;
				m_dAccumY -= m_vDelta.y;
				break;
			case (int)KEY::DOWN:
				m_dAccumY += m_iSpeed * fDT;
				m_vDelta.y = (int)m_dAccumY;
				vPos.y += m_vDelta.y;
				m_dAccumY -= m_vDelta.y;
				break;
			}
		}
	}
	// 뗀 상태 외부면 돌아가기, 아니면 선상 이동
	else
	{
		if (m_iIdx > -1)
		{
			// 그렸던 경로 되돌아가기 + 선도 같이 사라짐
			if (m_vecLine[m_iIdx][1].x > m_vecLine[m_iIdx][0].x)
			{
				m_dAccumX -= m_iSpeed * fDT;
				m_vDelta.x = (int)m_dAccumX;
				vPos.x += m_vDelta.x;
				m_dAccumX -= m_vDelta.x;
			}
			else if (m_vecLine[m_iIdx][1].x < m_vecLine[m_iIdx][0].x)
			{
				m_dAccumX += m_iSpeed * fDT;
				m_vDelta.x = (int)m_dAccumX;
				vPos.x += m_vDelta.x;
				m_dAccumX -= m_vDelta.x;
			}
			else if (m_vecLine[m_iIdx][1].y > m_vecLine[m_iIdx][0].y)
			{
				m_dAccumY -= m_iSpeed * fDT;
				m_vDelta.y = (int)m_dAccumY;
				vPos.y += m_vDelta.y;
				m_dAccumY -= m_vDelta.y;
			}
			else if (m_vecLine[m_iIdx][1].y < m_vecLine[m_iIdx][0].y)
			{
				m_dAccumY += m_iSpeed * fDT;
				m_vDelta.y = (int)m_dAccumY;
				vPos.y += m_vDelta.y;
				m_dAccumY -= m_vDelta.y;
			}
			else
			{
				m_vecLine.pop_back();
				m_iIdx--;
			}
		}
		else
		{
			// TODO: 스페이스 바를 안눌렀을 때는 선상으로만 이동가능
			// KEY_HOLD에 대한 우선권 설정 다른 방향키 누를 시에 무조건 방향이 바뀜!
			if (KEY_TAP(KEY::LEFT))
			{
				m_iCurKey = (int)KEY::LEFT;
				m_dAccumX -= m_iSpeed * fDT;
				m_vDelta.x = (int)m_dAccumX;
				vPos.x += m_vDelta.x;
				m_dAccumX -= m_vDelta.x;
			}
			else if (KEY_TAP(KEY::RIGHT))
			{
				m_iCurKey = (int)KEY::RIGHT;
				m_dAccumX += m_iSpeed * fDT;
				m_vDelta.x = (int)m_dAccumX;
				vPos.x += m_vDelta.x;
				m_dAccumX -= m_vDelta.x;
			}
			else if (KEY_TAP(KEY::UP))
			{
				m_iCurKey = (int)KEY::UP;
				m_dAccumY -= m_iSpeed * fDT;
				m_vDelta.y = (int)m_dAccumY;
				vPos.y += m_vDelta.y;
				m_dAccumY -= m_vDelta.y;
			}
			else if (KEY_TAP(KEY::DOWN))
			{
				m_iCurKey = (int)KEY::DOWN;
				m_dAccumY += m_iSpeed * fDT;
				m_vDelta.y = (int)m_dAccumY;
				vPos.y += m_vDelta.y;
				m_dAccumY -= m_vDelta.y;
			}
			// 뭔가 하나라도 누르고 있는 중이면
			else if (KEY_HOLD(KEY::LEFT) ||
					KEY_HOLD(KEY::RIGHT) ||
					KEY_HOLD(KEY::UP) ||
					KEY_HOLD(KEY::DOWN))
			{
				// 우선권에 따라서 경로 진행
				switch (m_iCurKey)
				{
				case (int)KEY::LEFT:
					m_dAccumX -= m_iSpeed * fDT;
					m_vDelta.x = (int)m_dAccumX;
					vPos.x += m_vDelta.x;
					m_dAccumX -= m_vDelta.x;
					break;
				case (int)KEY::RIGHT:
					m_dAccumX += m_iSpeed * fDT;
					m_vDelta.x = (int)m_dAccumX;
					vPos.x += m_vDelta.x;
					m_dAccumX -= m_vDelta.x;
					break;
				case (int)KEY::UP:
					m_dAccumY -= m_iSpeed * fDT;
					m_vDelta.y = (int)m_dAccumY;
					vPos.y += m_vDelta.y;
					m_dAccumY -= m_vDelta.y;
					break;
				case (int)KEY::DOWN:
					m_dAccumY += m_iSpeed * fDT;
					m_vDelta.y = (int)m_dAccumY;
					vPos.y += m_vDelta.y;
					m_dAccumY -= m_vDelta.y;
					break;
				}
			}
		}
	}

	// 누르고 있는 상태 -> 선 변경
	if (m_iIdx > -1)
	{
		m_vecLine[m_iIdx][1] = vPos;
	}

	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_dc, hBrush);

	for (int i = 0; i < m_iIdx + 1; i++)
	{
		MoveToEx(_dc, (int)(m_vecLine[i][0].x), (int)(m_vecLine[i][0].y), NULL);
		LineTo(_dc, (int)(m_vecLine[i][1].x), (int)(m_vecLine[i][1].y));
	}

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


//void CPlayer::CreateLine()
//{
//	Vec2 vLinePos = GetPos();
//
//	// Line Object
//	CLine* pLine = new CLine;
//	pLine->SetPos(vLinePos);
//	pLine->SetEnd(vLinePos);
//
//	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
//	pCurScene->AddObject(pLine, GROUP_TYPE::LINE);
//
//	m_currLine = pLine;
//}
