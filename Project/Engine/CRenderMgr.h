#pragma once
#include "CSingleton.h"

class CCamera;
class CLight2D;
class CConstBuffer;


class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);
private:
    vector<CCamera*>            m_vecCam;
    vector<tDebugShapeInfo>     m_vecShapeInfo;

    //구조화 버퍼에 들어갈 광원 정보를 저장하는 컨테이너.
    //구조화 버퍼의 갯수는 별도의 Constant buffer을 통해서 전달할 예정(b2 레지스터, CBUFFER::LIGHT)
    vector<tLightInfo>          m_vecLight2D;



public:
    void init();
    void render();

public:
    int RegisterCamera(CCamera* _Cam, int _idx);
    void RegisterLight2D(const tLightInfo& _Light2D) { m_vecLight2D.push_back(_Light2D); }

    void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_vecShapeInfo.push_back(_info); }
    vector<tDebugShapeInfo>& GetDebugShapeInfo() { return m_vecShapeInfo; }

    CCamera* GetMainCam() 
    { 
        if (m_vecCam.empty())
            return nullptr;

        return m_vecCam[0];
    }

private:
    void UpdateData();
    void Clear();


};

