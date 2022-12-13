#pragma once
#include "CSingleton.h"

#include "ptr.h"
#include "CRes.h"

class CMesh;

class CResMgr :
    public CSingleton<CResMgr>
{
private:
    map<wstring, Ptr<CRes>> m_arrRes[(UINT)RES_TYPE::END];

public:
    void init();

private:
    void CreateDefaultMesh();
    void CreateDefaultGraphicsShader();

public:
    template<typename T>
    Ptr<T> FindRes(const wstring& _strKey);


public:
    CResMgr();
    ~CResMgr();
};

template<typename T>
inline Ptr<T> CResMgr::FindRes(const wstring& _strKey)
{
    if (typeid(T).hash_code() == typeid(CMesh).hash_code())
    {
        map<wstring, Ptr<CRes>>::iterator iter = m_arrRes[(UINT)RES_TYPE::MESH].find(_strKey);
        if (iter == m_arrRes[(UINT)RES_TYPE::MESH].end())
            return nullptr;

        return (T*)iter->second.Get();
    }

    return nullptr;
}
