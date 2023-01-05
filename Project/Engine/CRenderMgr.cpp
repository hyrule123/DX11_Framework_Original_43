#include "pch.h"
#include "CRenderMgr.h"

#include "CDevice.h"
#include "CConstBuffer.h"

#include "CCamera.h"
#include "CLight2D.h"

#include "CConstBuffer.h"
#include "CStructuredBuffer.h"

CRenderMgr::CRenderMgr()
{

}

CRenderMgr::~CRenderMgr()
{

}


void CRenderMgr::init()
{
}

void CRenderMgr::render()
{
    UpdateData();


    for (size_t i = 0; i < m_vecCam.size(); ++i)
    {
        if (nullptr == m_vecCam[i])
            continue;

        m_vecCam[i]->SortObject();
        m_vecCam[i]->render();
    }   

    Clear();
}

int CRenderMgr::RegisterCamera(CCamera* _Cam, int _idx)
{
    if (m_vecCam.size() <= _idx)
    {
        m_vecCam.resize(_idx + 1);
    }

    m_vecCam[_idx] = _Cam;    
    return _idx;
}

void CRenderMgr::UpdateData()
{
    //출력하도록 등록된 빛의 사이즈를 등록한다.
    //패딩을 넣어야 하므로 임시 구조체 변수를 만든 다음 전달한다.
    struct {
        UINT size;
        Vec3 Padding;
    } tCBuffer{};
    tCBuffer.size = (UINT)m_vecLight2D.size();
    static CConstBuffer* pLightBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::LIGHT);
    pLightBuffer->SetData((void*)&tCBuffer);
    pLightBuffer->UpdateData();

    //구조화버퍼의 데이터를 업데이트
    CStructuredBuffer* pBuffer = CDevice::GetInst()->GetStructBuffer(SB_TYPE::LIGHT);

    UINT bytesize = (UINT)(sizeof(tLightInfo) * m_vecLight2D.size());
    pBuffer->SetData(m_vecLight2D.data(), bytesize);
    UINT PStage = PIPELINE_STAGE::PS_VERTEX | PIPELINE_STAGE::PS_PIXEL;
    pBuffer->UpdateData((UINT)SB_TYPE::LIGHT, PStage); 
}

void CRenderMgr::Clear()
{
    m_vecLight2D.clear();
}
