#pragma once
#include "CEntity.h"


class CComponent;
class CTransform;
class CMeshRender;
class CCamera;
class CRenderComponent;
class CScript;

class CGameObject :
    public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*       m_RenderCom;
    vector<CScript*>        m_vecScript;

    CGameObject*            m_Parent;
    vector<CGameObject*>    m_vecChild;

    int                     m_iLayerIdx;


public:
    void begin();       // ������ ���۵� �� ȣ�� or ���� �� ������ �շ��� ��
    void tick();        
    void finaltick();
    void render();


public:
    void AddComponent(CComponent* _Component);
    void AddChild(CGameObject* _Object);

    CGameObject* GetParent() const { return m_Parent; }

    CTransform* Transform() const { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
    CMeshRender* MeshRender() const { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }
    CCamera* Camera() const { return (CCamera*)m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]; }
    CRenderComponent* GetRenderComponent() const {  return m_RenderCom; }


    CLONE(CGameObject)    
public:
    CGameObject();
    ~CGameObject();

    friend class CLayer;
};

