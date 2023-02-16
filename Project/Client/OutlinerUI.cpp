#include "pch.h"
#include "OutlinerUI.h"

#include <Engine\CEventMgr.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "TreeUI.h"

OutlinerUI::OutlinerUI()
    : UI("##Outliner")
	, m_Tree(nullptr)
{
    SetName("Outliner");

	// OutlinerUI �ȿ� �ڽ����� Tree �� �߰��Ѵ�.
	m_Tree = new TreeUI;
	m_Tree->SetName("OutlinerTree");
	m_Tree->SetActive(true);
	m_Tree->ShowRoot(false);
	AddChildUI(m_Tree);
}

OutlinerUI::~OutlinerUI()
{
}

int OutlinerUI::render_update()
{
    return 0;
}

void OutlinerUI::tick()
{
	if (CEventMgr::GetInst()->IsLevelChanged())
	{
		ResetOutliner();
	}
}

void OutlinerUI::ResetOutliner()
{
	// Tree Clear
	m_Tree->Clear();
	m_Tree->AddItem("Root", 0);

	// ���ҽ� �Ŵ������� ���� ��� ���ҽ� ��� �޾ƿ�
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT i = 0; i < (UINT)MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);

		const vector<CGameObject*>& vecParentObj = pLayer->GetParentObject();

		for (size_t i = 0; i < vecParentObj.size(); ++i)
		{
			m_Tree->AddItem(   string(vecParentObj[i]->GetName().begin()
									, vecParentObj[i]->GetName().end())
				            ,  (DWORD_PTR)vecParentObj[i]);
		}
	}
}
