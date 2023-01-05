#pragma once
#include "CScript.h"

class CPlayerScript :
    public CScript
{
private:
    float       m_fSpeed;

public:
    virtual void tick() override;


    virtual void BeginOverlap(CCollider2D* _Other) override;


private:
    void Shoot();
    void ComputeSpotLight();

    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};

