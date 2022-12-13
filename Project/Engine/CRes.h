#pragma once
#include "CEntity.h"

class CRes :
    public CEntity
{
private:
    const RES_TYPE  m_Type;
    int             m_iRefCount;

    wstring         m_strKey;
    wstring         m_strRelativePath;

private:
    void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
    void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

    void AddRef() { ++m_iRefCount; }
    void Release();


public:
    // 리소스 바인딩
    virtual void UpdateData() = 0;

    // 리소스는 Clone 을 구현하지 않는다.
    virtual CRes* Clone() { return nullptr; assert(nullptr); }

public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }


public:
    CRes(RES_TYPE _type);
    virtual ~CRes();

    friend class CResMgr;
};

