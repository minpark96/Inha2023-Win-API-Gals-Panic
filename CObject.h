#pragma once


class CObject
{
private:
	Vec2 m_vPos;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	Vec2 GetPos() { return m_vPos; }

public:
	virtual void update() = 0;
	virtual void render(HDC _dc) = 0;

public:
	CObject();
	virtual ~CObject();
};
