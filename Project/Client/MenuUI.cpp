#include "pch.h"
#include "MenuUI.h"

#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include "ImGuiMgr.h"
#include "OutlinerUI.h"
#include "InspectorUI.h"

MenuUI::MenuUI()
	: UI("##Menu")
{
	SetName("Menu");
}

MenuUI::~MenuUI()
{
}

void MenuUI::finaltick()
{
    if (!IsActive())
        return;

    render_update();
}

int MenuUI::render_update()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save Level"))
            {

            }

            if (ImGui::MenuItem("Load Level"))
            {

            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObject"))
        {
            // ���� ������ ���ӿ�����Ʈ ����
            if (ImGui::MenuItem("Create Empty Object"))
            {
                CreateEmptyObject();
            }
            ImGui::Separator();

            
            if (ImGui::BeginMenu("Add Component"))
            {
                for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
                {
                    if (ImGui::MenuItem(ToString((COMPONENT_TYPE)i)))
                    {
                        AddComponent(COMPONENT_TYPE(i));
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::BeginMenu("Add Script"))
            {
                if (ImGui::MenuItem("PlayerScript"))
                {

                }

                if (ImGui::MenuItem("MonsterScript"))
                {

                }
                
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

	return 0;
}

void MenuUI::CreateEmptyObject()
{
    CGameObject* pNewObject = new CGameObject;
    pNewObject->AddComponent(new CTransform);
    pNewObject->SetName(L"New Object");
    SpawnGameObject(pNewObject, Vec3(0.f, 0.f, 0.f), L"Default");

    // Outliner �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");

    // �����߰��� ������Ʈ�� �����ͷ� �ϴ� ��尡 �߰��Ǹ�, ���û��·� �ΰ� �Ѵ�.
    outliner->SetSelectedNodeData(DWORD_PTR(pNewObject));    
}

void MenuUI::AddComponent(COMPONENT_TYPE _type)
{
    // Outliner �� Inspector �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");

    // ���õ� ������Ʈ�� �����ͼ� ComponentType �� �´� ������Ʈ�� �����ؼ� �߰��Ѵ�.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject)
        return;

    switch (_type)
    {
    case COMPONENT_TYPE::TRANSFORM:
        pSelectedObject->AddComponent(new CTransform);
        break;
    case COMPONENT_TYPE::COLLIDER2D:
        pSelectedObject->AddComponent(new CCollider2D);
        break;
    case COMPONENT_TYPE::COLLIDER3D:
        //pSelectedObject->AddComponent(new CCollider3D);
        break;
    case COMPONENT_TYPE::ANIMATOR2D:
        pSelectedObject->AddComponent(new CAnimator2D);
        break;
    case COMPONENT_TYPE::ANIMATOR3D:
        //pSelectedObject->AddComponent(new CAnimator3D);
        break;
    case COMPONENT_TYPE::LIGHT2D:
        pSelectedObject->AddComponent(new CLight2D);
        break;
    case COMPONENT_TYPE::LIGHT3D:
        //pSelectedObject->AddComponent(new CLight3D);
        break;
    case COMPONENT_TYPE::CAMERA:
        pSelectedObject->AddComponent(new CCamera);
        break;
    case COMPONENT_TYPE::MESHRENDER:
        pSelectedObject->AddComponent(new CMeshRender);
        break;
    case COMPONENT_TYPE::PARTICLESYSTEM:
        pSelectedObject->AddComponent(new CParticleSystem);
        break;
    case COMPONENT_TYPE::TILEMAP:
        pSelectedObject->AddComponent(new CTileMap);
        break;
    case COMPONENT_TYPE::LANDSCAPE:
        //pSelectedObject->AddComponent(new CLandScape);
        break;
    case COMPONENT_TYPE::DECAL:
        //pSelectedObject->AddComponent(new CDecal);
        break;            
    }

    // Inspector �� ���Ӱ� �߰��� ������Ʈ�� �˸��� ���ؼ� Ÿ���� �ٽ� �˷��ش�.
    inspector->SetTargetObject(pSelectedObject);

}
