#include "pch.h"
#include "CTransform.h"



CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
{
}

CTransform::~CTransform()
{
}

void CTransform::finaltick()
{

}

void CTransform::UpdateData()
{
	// 위치값을 상수버퍼에 전달 및 바인딩		
	D3D11_MAPPED_SUBRESOURCE tSubRes = {};
	if (!FAILED(CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSubRes)))
	{
		memcpy(tSubRes.pData, &g_PlayerPos, sizeof(Vec4));
		CONTEXT->Unmap(g_CB.Get(), 0);
	}

	CONTEXT->VSSetConstant();
}
