#pragma once
#include "CRes.h"


class CShader :
    public CRes
{
protected:
    ComPtr<ID3DBlob>    m_ErrBlob;


public:
    CShader(RES_TYPE _eType);
    ~CShader();
};

