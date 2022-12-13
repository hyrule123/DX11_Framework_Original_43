#pragma once
#include "CSingleton.h"

#include "ptr.h"
#include "CMesh.h"
#include "CGraphicsShader.h"


class CResMgr :
    public CSingleton<CResMgr>
{
    SINGLE(CResMgr)
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
};

template<typename T>
RES_TYPE GetResType()
{
    const type_info& mesh = typeid(CMesh);
    //const type_info& meshdata = typeid(CMeshData);
    //const type_info& material = typeid(CMaterial);
    //const type_info& texture = typeid(CTexture);
    //const type_info& sound = typeid(CSound);
    //const type_info& prefab = typeid(CPrefab);
    const type_info& gs = typeid(CGraphicsShader);
    //const type_info& cs = typeid(CComputeShader);

    if (typeid(T).hash_code() == mesh.hash_code())
        return RES_TYPE::MESH;
    if (typeid(T).hash_code() == gs.hash_code())
        return RES_TYPE::GRAPHICS_SHADER;

    return RES_TYPE::END;
}


template<typename T>
inline Ptr<T> CResMgr::FindRes(const wstring& _strKey)
{
    RES_TYPE type = GetResType<T>();
      
    map<wstring, Ptr<CRes>>::iterator iter = m_arrRes[(UINT)type].find(_strKey);
    if (iter == m_arrRes[(UINT)type].end())
        return nullptr;

    return (T*)iter->second.Get();    
}
