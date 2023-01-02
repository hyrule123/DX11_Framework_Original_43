#pragma once
#include "CEntity.h"

#include "CGameObject.h"

class CTransform;
class CMeshRender;

class CComponent :
    public CEntity
{
private:
    CGameObject*         m_pOwner;
    const COMPONENT_TYPE m_Type;

public:
    COMPONENT_TYPE GetType() { return m_Type; }
    CGameObject* GetOwner() { return m_pOwner ; }

public:
    virtual void begin() {}
    virtual void tick() {}
    virtual void finaltick() = 0;
    virtual CComponent* Clone() = 0;

public:
    CTransform* Transform() { return m_pOwner->Transform(); }
    CMeshRender* MeshRender() { return m_pOwner->MeshRender(); }
    CCamera* Camera() { return m_pOwner->Camera(); }
    CCollider2D* Collider2D() { return m_pOwner->Collider2D(); }
    CLight2D* Light2D() { return m_pOwner->Light2D(); }

public:
    CComponent(COMPONENT_TYPE _Type);
    CComponent(const CComponent& _Other);
    virtual ~CComponent();

    friend class CGameObject;
};

