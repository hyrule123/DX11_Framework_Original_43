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
    TreeNode*   m_RootNode; // Ʈ���� �����ϰ� �ִ� ��� �� ��Ʈ ���
    UINT        g_NextId;   // �����Ǵ� ���ڿ� �ٿ��� ���� ����

    bool        m_bShowRoot;

public:
    virtual int render_update() override;
public:
    void Clear();
    TreeNode* AddItem(const string& _strNodeName, DWORD_PTR _Data, TreeNode* _pParent = nullptr);
    void ShowRoot(bool _Show) { m_bShowRoot = _Show; }

public:
    TreeUI();
    ~TreeUI();
};

