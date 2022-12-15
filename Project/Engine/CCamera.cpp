#include "pch.h"
#include "CCamera.h"


#include "CDevice.h"
#include "CTransform.h"


CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_fAspectRatio(1.f)
{
	Vec2 vRenderResol = CDevice::GetInst()->GetRenderResolution();
	m_fAspectRatio = vRenderResol.x / vRenderResol.y;
}

CCamera::~CCamera()
{
}

void CCamera::finaltick()
{
	// ==============
	// View 행렬 계산
	// ==============
	m_matView = XMMatrixIdentity();

	// 카메라 좌표를 원점으로 이동
	Vec3 vCamPos = Transform()->GetRelativePos();
	Matrix matViewTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);
		
	Matrix matViewRot = XMMatrixIdentity();

	m_matView = matViewTrans * matViewRot;


	// =============
	// 투영 행렬 계산
	// =============
	m_matProj = XMMatrixIdentity();


	m_fAspectRatio;

	// 직교 투영
	Vec2 vResolution  = CDevice::GetInst()->GetRenderResolution();
	m_matProj =  XMMatrixOrthographicLH(vResolution.x, vResolution.y, 1.f, 10000.f);


	// 원근 투영
	//m_matProj = XMMatrixPerspectiveFovLH(XM_PI / 2.f, m_fAspectRatio, 1.f, 10000.f);




	// 행렬 업데이트
	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;
}