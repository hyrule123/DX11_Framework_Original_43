#pragma once
#include "CEntity.h"


class CComponent;
class CTransform;
class CMeshRender;
class CCamera;
class CRenderComponent;

class CGameObject :
    public CEntity
{
private:
    CComponent*         m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*   m_RenderCom;


public:
    void tick();
    void finaltick();


    void render();


public:
    void AddComponent(CComponent* _Component);

    CTransform* Transform() { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
    CMeshRender* MeshRender() { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }
    CCamera* Camera() { return (CCamera*)m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]; }

    CRenderComponent* GetRenderComponent() {  return m_RenderCom; }


    CLONE(CGameObject)    
public:
    CGameObject();
    ~CGameObject();

};

