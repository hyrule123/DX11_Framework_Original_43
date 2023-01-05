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
    //����ϵ��� ��ϵ� ���� ����� ����Ѵ�.
    //�е��� �־�� �ϹǷ� �ӽ� ����ü ������ ���� ���� �����Ѵ�.
    struct {
        UINT size;
        Vec3 Padding;
    } tCBuffer{};
    tCBuffer.size = (UINT)m_vecLight2D.size();
    static CConstBuffer* pLightBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::LIGHT);
    pLightBuffer->SetData((void*)&tCBuffer);
    pLightBuffer->UpdateData();

    //����ȭ������ �����͸� ������Ʈ
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
