#pragma once


// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����

class CCore
{
	// ���� ����Լ�
	SINGLE(CCore);
public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();
private:
	CCore();
	~CCore();
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hDC			// ���� �����쿡 Draw �� DC
};

