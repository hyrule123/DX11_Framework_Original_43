#include "pch.h"
#include "CCamera.h"


#include "CDevice.h"
#include "CTransform.h"


CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_fAspectRatio(1.f)
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
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
	// View ��� ���
	// ==============
	m_matView = XMMatrixIdentity();

	// ī�޶� ��ǥ�� �������� �̵�
	Vec3 vCamPos = Transform()->GetRelativePos();
	Matrix matViewTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);
		
	// ī�޶� �ٶ󺸴� ������ Z ��� �����ϰ� ����� ȸ�� ����� ����
	Matrix matViewRot = XMMatrixIdentity();

	Vec3 vR = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);
	Vec3 vU = Transform()->GetRelativeDir(DIR_TYPE::UP);
	Vec3 vF = Transform()->GetRelativeDir(DIR_TYPE::FRONT);

	matViewRot._11 = vR.x;	matViewRot._12 = vU.x;	matViewRot._13 = vF.x;
	matViewRot._21 = vR.y;	matViewRot._22 = vU.y;	matViewRot._23 = vF.y;
	matViewRot._31 = vR.z;	matViewRot._32 = vU.z;	matViewRot._33 = vF.z;

	m_matView = matViewTrans * matViewRot;

	// =============
	// ���� ��� ���
	// =============
	m_matProj = XMMatrixIdentity();
	
	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		// ���� ����
		Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
		m_matProj =  XMMatrixOrthographicLH(vResolution.x, vResolution.y, 1.f, 10000.f);
	}
	else
	{	
		// ���� ����
		m_matProj = XMMatrixPerspectiveFovLH(XM_PI / 2.f, m_fAspectRatio, 1.f, 10000.f);
	}


	// ��� ������Ʈ
	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;
}