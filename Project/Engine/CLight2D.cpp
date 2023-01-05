#include "pch.h"
#include "CLight2D.h"

#include "CRenderMgr.h"
#include "CTransform.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CLight2D::CLight2D()
	: CComponent(COMPONENT_TYPE::LIGHT2D)
{
}

CLight2D::~CLight2D()
{
}

void CLight2D::tick()
{
	CTransform* Transform = GetOwner()->Transform();
	if (Transform)
	{
		m_LightInfo.vWorldPos = Transform->GetWorldPos();
	}
}

void CLight2D::finaltick()
{
	CRenderMgr::GetInst()->RegisterLight2D(m_LightInfo);
}