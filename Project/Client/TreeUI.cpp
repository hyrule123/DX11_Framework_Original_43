#include "pch.h"
#include "TreeUI.h"

// ========
// TreeNode
// ========
TreeNode::TreeNode()
    : m_Owner(nullptr)
    , m_ParentNode(nullptr)
{

}

TreeNode::~TreeNode()
{
    Safe_Del_Vec(m_vecChildNode);
}

void TreeNode::render_update()
{
    // FinalName �����
    string strFinalName = m_strName;
    strFinalName += "##";

    char szBuff[100] = {};
    itoa(m_ID, szBuff, 10);
    strFinalName += szBuff;

    ImGuiTreeNodeFlags_ flag = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_None;

    if (ImGui::TreeNodeEx(strFinalName.c_str(), flag))
    {
        for (size_t i = 0; i < m_vecChildNode.size(); ++i)
        {
            m_vecChildNode[i]->render_update();
        }

        ImGui::TreePop();
    }

}


// ================
//      TreeUI
// ================
TreeUI::TreeUI()
    : UI("##Tree")
    , m_RootNode(nullptr)
    , g_NextId(0)
    , m_bShowRoot(true)
{   

}

TreeUI::~TreeUI()
{
    if (nullptr != m_RootNode)
        delete m_RootNode;
}

int TreeUI::render_update()
{
    if (nullptr != m_RootNode)
    {
        if (m_bShowRoot)
        {
            m_RootNode->render_update();
        }
        else
        {
            for (size_t i = 0; i < m_RootNode->m_vecChildNode.size(); ++i)
            {
                m_RootNode->m_vecChildNode[i]->render_update();
            }
        }
    }

    return 0;
}

void TreeUI::Clear()
{
    if (nullptr != m_RootNode)
    {
        delete m_RootNode;
        m_RootNode = nullptr;
    }     
}

TreeNode* TreeUI::AddItem(const string& _strNodeName, DWORD_PTR _Data, TreeNode* _pParent)
{    
    TreeNode* pNewNode = new TreeNode;

    pNewNode->m_Owner = this;
    pNewNode->m_strName = _strNodeName;
    pNewNode->m_Data = _Data;
    pNewNode->m_ID = g_NextId++;

    // ��Ʈ�� NULL �̴� ==> Ʈ���� ���� ������ ������
    if (nullptr == m_RootNode)
    {
        // ���� ������ �Է��ε�, �θ� ������ ���
        assert(!_pParent);

        m_RootNode = pNewNode;
    }

    // Ʈ���� ���� �����Ͱ� ���ʰ� �ƴϴ�.
    else
    {
        if (_pParent)
        {
            // ����� �θ�� ������ ��尡 �ش� Ʈ�� �Ҽ��� �ƴϴ�.
            if (_pParent->m_Owner != this)
                assert(nullptr);

            // ������ �θ��� �ڽ����� ����
            _pParent->m_vecChildNode.push_back(pNewNode);
            pNewNode->m_ParentNode = _pParent;
        }

        // �θ�� ������ ��尡 ���°��, ��Ʈ ������ �ִ´�
        else
        {
            // ���� ������ ��带 ��Ʈ����� �ڽ����� ����
            m_RootNode->m_vecChildNode.push_back(pNewNode);
            pNewNode->m_ParentNode = m_RootNode;            
        }
    }

    return pNewNode;
}

