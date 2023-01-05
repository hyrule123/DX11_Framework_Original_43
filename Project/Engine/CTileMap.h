#pragma once

#include "CRenderComponent.h"

class CTileMap :
    public CRenderComponent
{
private:
    UINT    m_iTileCountX;  // Ÿ�� ����
    UINT    m_iTileCountY;  // Ÿ�� ����

public:
    virtual void finaltick() override;
    virtual void render() override;

    void UpdateData();

    CLONE(CTileMap);
public:
    CTileMap();
    ~CTileMap();
};

