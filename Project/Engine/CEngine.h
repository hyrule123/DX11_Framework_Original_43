#pragma once

class CEngine
	: public CSingleton<CEngine>
{
private:
	HWND	m_hWnd;

	// ������ �ػ�
	UINT	m_iWidth;
	UINT	m_iHeight;
	

public:
	int init(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	void progress();

public:
	CEngine();
	~CEngine();
};
