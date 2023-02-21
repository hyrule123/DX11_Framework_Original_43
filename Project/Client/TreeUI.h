#pragma once
#include "UI.h"

// =========
// TreeNode
// =========
class TreeUI;
class TreeNode
{
private:
    TreeUI*             m_Owner;        // ��带 �����ϰ� �ִ� Ʈ��
    TreeNode*           m_ParentNode;   // �θ���
    vector<TreeNode*>   m_vecChildNode; // ����� �ڽ� ���
        
    string              m_strName;      // ����� ��� �̸�
    UINT                m_ID;           // ����� ���� ID

    DWORD_PTR           m_Data;         // ��忡 ����� ������


    bool                m_CategoryNode; // �׸� ��ǥ ���
    bool                m_Hilight;      // ��� ���̶���Ʈ ó��


public:
    void SetCategoryNode(bool _category)
    {
        m_CategoryNode = _category;
    }

public:
    const string& GetName() { return m_strName; }
    DWORD_PTR GetData() { return m_Data; }


private:
    void render_update();

public:
    TreeNode();
    ~TreeNode();

    friend class TreeUI;
};



// ======
// TreeUI
// ======
class TreeUI :
    public UI
{
private:
    TreeNode*       m_RootNode; // Ʈ���� �����ϰ� �ִ� ��� �� ��Ʈ ���
    UINT            g_NextId;   // �����Ǵ� ���ڿ� �ٿ��� ���� ����
    bool            m_bShowRoot;

    TreeNode*       m_SelectedNode;

    UI*             m_SelectInst;
    UI_DELEGATE_1   m_SelectFunc;


public:
    virtual int render_update() override;

public:
    void Clear();
    TreeNode* AddItem(const string& _strNodeName, DWORD_PTR _Data, TreeNode* _pParent = nullptr);
    void ShowRoot(bool _Show) { m_bShowRoot = _Show; }
    void AddDynamic_Select(UI* _UI, UI_DELEGATE_1 _MemFunc)
    {
        m_SelectInst = _UI;
        m_SelectFunc = _MemFunc;
    }


private:
    void SetSelectedNode(TreeNode* _Node);

public:
    TreeUI();
    ~TreeUI();

    friend class TreeNode;
};

