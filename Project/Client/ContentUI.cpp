#include "pch.h"
#include "ContentUI.h"

#include <Engine\CResMgr.h>
#include "TreeUI.h"

ContentUI::ContentUI()
    : UI("##Content")
{
    SetName("ContentUI");

    // ContentUI �ȿ� �ڽ����� Tree �� �߰��Ѵ�.
    m_Tree = new TreeUI;
    m_Tree->SetName("ContentTree");
    m_Tree->SetActive(true);
    m_Tree->ShowRoot(false);
    AddChildUI(m_Tree);

    // ��Ʈ ����
    m_Tree->AddItem("RootNode", 0);

    // ��Ʈ �ؿ� �ڽ� 2�� �߰�
    TreeNode* pChild1Node = m_Tree->AddItem("Child1", 0);
    m_Tree->AddItem("Child2", 0);

    // Child1 �ؿ� �ڽ� 2�� �߰�
    m_Tree->AddItem("ChildChild1", 0, pChild1Node);
    m_Tree->AddItem("ChildChild2", 0, pChild1Node);
}

ContentUI::~ContentUI()
{

}


int ContentUI::render_update()
{
  
    return 0;
}

void ContentUI::ResetContent()
{
    // Tree Clear
    m_Tree->Clear();

    // ���ҽ� �Ŵ������� ���� ��� ���ҽ� ��� �޾ƿ�

    // m_Tree �� ���� ���ҽ� ����� AddItem

}

