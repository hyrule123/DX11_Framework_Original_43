#pragma once
#include "CComponent.h"

class CCamera :
    public CComponent
{
private:
    float       m_fAspectRatio;
    PROJ_TYPE   m_ProjType;


    Matrix      m_matView;
    Matrix      m_matProj;

public:
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
    PROJ_TYPE GetProjType() { return m_ProjType; }


    const Matrix& GetViewMat() { return m_matView; }
    const Matrix& GetProjMat() { return m_matProj; }


public:
    virtual void finaltick() override;

    CLONE(CCamera);
public:    
    CCamera();
    ~CCamera();
};

