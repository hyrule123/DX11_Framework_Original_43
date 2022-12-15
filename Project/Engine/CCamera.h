#pragma once
#include "CComponent.h"

class CCamera :
    public CComponent
{
private:

    float       m_fAspectRatio;


    Matrix      m_matView;
    Matrix      m_matProj;

public:
    const Matrix& GetViewMat() { return m_matView; }
    const Matrix& GetProjMat() { return m_matProj; }


public:
    virtual void finaltick() override;

    CLONE(CCamera);
public:    
    CCamera();
    ~CCamera();
};

