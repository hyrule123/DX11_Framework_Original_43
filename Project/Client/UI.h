#pragma once


#include "ImGuiMgr.h"

class UI
{
private:
	const string	m_strName;		// Ÿ��Ʋ �̸�, ID

	UI*				m_ParentUI;		// �θ� UI
	vector<UI*>		m_vecChildUI;	// �ڽ� UI ���

public:
	virtual void tick() {}
	virtual void finaltick();
	virtual void render_update() = 0;


public:
	const string& GetName() { return m_strName; }
	void AddChildUI(UI* _UI)
	{
		_UI->m_ParentUI = this;
		m_vecChildUI.push_back(_UI);
	}


public:
	UI(const string& _Name);
	~UI();
};

