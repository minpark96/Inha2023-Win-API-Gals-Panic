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
	



	// �����̽����� ���������� ���� ������ ������!

	// �����̽��� ���� ���� (���α׸���)
	if (KEY_TAP(KEY::SPACE) || KEY_HOLD(KEY::SPACE))
	{
		// TODO: �̹� ���� �� ���� ������ �� ����
		// ����ä�� ������ Ż���ִ�. ������ ���� �ܺ����� ���� �׷�����.

		// �ܺζ��?
		// ������ȯ �� -> �� �߰�

		if (KEY_TAP(KEY::LEFT))
		{
			m_iCurKey = (int)KEY::LEFT;

			if (m_vecPushed[m_iCurKey] == false)
			{
				// �� ��ü �߰�
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
				// �� ��ü �߰�
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
				// �� ��ü �߰�
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
				// �� ��ü �߰�
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
		// ���� �ϳ��� ������ �ִ� ���̸�
		else if (KEY_HOLD(KEY::LEFT) ||
			KEY_HOLD(KEY::RIGHT) ||
			KEY_HOLD(KEY::UP) ||
			KEY_HOLD(KEY::DOWN))
		{
			// �켱�ǿ� ���� ��� ����
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
	// �� ���� �ܺθ� ���ư���, �ƴϸ� ���� �̵�
	else
	{
		if (m_iIdx > -1)
		{
			// �׷ȴ� ��� �ǵ��ư��� + ���� ���� �����
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
			// TODO: �����̽� �ٸ� �ȴ����� ���� �������θ� �̵�����
			// KEY_HOLD�� ���� �켱�� ���� �ٸ� ����Ű ���� �ÿ� ������ ������ �ٲ�!
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
			// ���� �ϳ��� ������ �ִ� ���̸�
			else if (KEY_HOLD(KEY::LEFT) ||
					KEY_HOLD(KEY::RIGHT) ||
					KEY_HOLD(KEY::UP) ||
					KEY_HOLD(KEY::DOWN))
			{
				// �켱�ǿ� ���� ��� ����
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

	// ������ �ִ� ���� -> �� ����
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
