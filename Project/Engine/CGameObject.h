#pragma once
#include "CEntity.h"


class CComponent;
class CTransform;
class CMeshRender;
class CCollider2D;
class CLight2D;
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
    bool                    m_bDead;
    float                   m_LifeTime;
    float                   m_CurLifeTime;
    bool                    m_bLifeSpan;

public:
    void begin();       // ������ ���۵� �� ȣ�� or ���� �� ������ �շ��� ��
    void tick();        
    virtual void finaltick();
    void render();

public:
    void AddComponent(CComponent* _Component);
    void AddChild(CGameObject* _Object);

    CComponent* GetComponent(COMPONENT_TYPE _ComType) { return m_arrCom[(UINT)_ComType]; }
    const vector<CGameObject*> GetChild() { return m_vecChild; }

    CGameObject* GetParent() const { return m_Parent; }

    CTransform* Transform() const { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
    CMeshRender* MeshRender() const { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }
    CCamera* Camera() const { return (CCamera*)m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]; }
    CCollider2D* Collider2D() const { return (CCollider2D*)m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER2D]; }
    CLight2D* Light2D() const { return (CLight2D*)m_arrCom[(UINT)COMPONENT_TYPE::LIGHT2D]; }


    CRenderComponent* GetRenderComponent() const {  return m_RenderCom; }


    int GetLayerIndex() { return m_iLayerIdx; }

    template<typename T>
    T* GetScript();

    const vector<CScript*>& GetScripts() { return m_vecScript; }

    void SetLifeSpan(float _fTime)
    {
        if (m_bLifeSpan)
            return;

        m_LifeTime = _fTime;
        m_bLifeSpan = true;
    }

    bool IsDead() { return m_bDead; }


    CLONE(CGameObject)    
public:
    CGameObject();
    CGameObject(const CGameObject& _Other);
    ~CGameObject();

    friend class CLayer;
    friend class CEventMgr;
};

template<typename T>
inline T* CGameObject::GetScript()
{
    for (size_t i = 0; i < m_vecScript.size(); ++i)
    {
        T* pScript = dynamic_cast<T*> (m_vecScript[i]);
        if (nullptr != pScript)
            return pScript;
    }

    return nullptr;
}
