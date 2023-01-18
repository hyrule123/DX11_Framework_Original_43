#include "pch.h"
#include "ListUI.h"

ListUI::ListUI()
    : UI("##List")
    , m_iSelectedIdx(0)
{
  /*  AddItem("AAA");
    AddItem("BBB");
    AddItem("CCC");    */
}

ListUI::~ListUI()
{
}

int ListUI::render_update()
{    
    // �ֱ� UI �� �۾����� ����� �˾Ƴ���.
    ImVec2 ListUIContentSize = ImGui::GetContentRegionAvail();
        
    if (ImGui::BeginListBox("##list", ListUIContentSize))
    {
        for (int i = 0; i < m_vecStrData.size(); i++)
        {
            const bool is_selected = (m_iSelectedIdx == i);

            // ����Ʈ ������ ���, ��ȯ���� Ŭ�� True/ False
            if (ImGui::Selectable(m_vecStrData[i].c_str(), is_selected))
            {
                m_iSelectedIdx = i;
            }             

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
       

    return TRUE;
}
