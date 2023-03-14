#include "pch.h"
#include "ContentUI.h"

#include <Engine\CResMgr.h>
#include "TreeUI.h"
#include "ImGuiMgr.h"
#include "InspectorUI.h"


ContentUI::ContentUI()
    : UI("##Content")
{
    SetName("Content");

    // ContentUI �ȿ� �ڽ����� Tree �� �߰��Ѵ�.
    m_Tree = new TreeUI;
    m_Tree->SetName("ContentTree");
    m_Tree->SetActive(true);
    m_Tree->ShowRoot(false);

	m_Tree->AddDynamic_Select(this, (UI_DELEGATE_1)&ContentUI::SetTargetToInspector);
	m_Tree->SetDragDropID("Resource");
    AddChildUI(m_Tree);   
}

ContentUI::~ContentUI()
{

}

void ContentUI::init()
{
    ResetContent();
}

void ContentUI::tick()
{
    UI::tick();

    if (CResMgr::GetInst()->IsResourceChanged())
    {
        ResetContent();
    }     
}

int ContentUI::render_update()
{   
    return 0;
}

void ContentUI::ResetContent()
{
	// Tree Clear
	m_Tree->Clear();
	m_Tree->AddItem("Root", 0);

	// ���ҽ� �Ŵ������� ���� ��� ���ҽ� ��� �޾ƿ�
	for (size_t i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		const map<wstring, Ptr<CRes>>& mapRes = CResMgr::GetInst()->GetResources((RES_TYPE)i);

		// m_Tree �� ���� ���ҽ� ����� AddItem
		TreeNode* pCategory = m_Tree->AddItem(ToString((RES_TYPE)i), 0);
        pCategory->SetCategoryNode(true);

		for (const auto& pair : mapRes)
		{
			m_Tree->AddItem(string(pair.first.begin(), pair.first.end()), (DWORD_PTR)pair.second.Get(), pCategory);
		}
	}
}

void ContentUI::SetTargetToInspector(DWORD_PTR _SelectedNode)
{
	TreeNode* pSelectedNode = (TreeNode*)_SelectedNode;
	CRes* pSelectObject = (CRes*)pSelectedNode->GetData();

	if (nullptr == pSelectObject)
		return;

	// Inspector �� ���õ� Resource �� �˷��ش�.	
	InspectorUI* pInspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");
	pInspector->SetTargetResource(pSelectObject);
}


