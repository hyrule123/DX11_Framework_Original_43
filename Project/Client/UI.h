#pragma once


#include "ImGuiMgr.h"

class UI
{
private:
	const string	m_strName;		// Ÿ��Ʋ �̸�, ID

	ImVec2			m_vSize;		// UI ũ��

	UI*				m_ParentUI;		// �θ� UI
	vector<UI*>		m_vecChildUI;	// �ڽ� UI ���

	bool			m_Modal;		// ��� or ��޸���
	bool			m_Active;		// UI Ȱ��ȭ üũ

public:
	virtual void tick() {}
	virtual void finaltick();
	virtual int render_update() = 0;


public:	
	void SetActive(bool _Active) { m_Active = _Active; }
	bool IsActive() { return m_Active; }

	void SetModal(bool _Modal) { m_Modal = _Modal; }
	bool IsModal() { return m_Modal; }

	const string& GetName() { return m_strName; }

	void SetSize(float _width, float _height) { m_vSize = ImVec2(_width, _height); }

	void AddChildUI(UI* _UI)
	{
		_UI->m_ParentUI = this;
		m_vecChildUI.push_back(_UI);
	}


public:
	UI(const string& _Name);
	~UI();
};

