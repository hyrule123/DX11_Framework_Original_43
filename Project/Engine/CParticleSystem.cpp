#include "pch.h"
#include "CParticleSystem.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CResMgr.h"
#include "CTransform.h"

#include "CTimeMgr.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_RWBuffer(nullptr)
	, m_ModuleData{}
	, m_AccTime(0.f)
{
	m_ModuleData.iMaxParticleCount = 100;
	m_ModuleData.SpawnRate = 1;
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;

	// ���� �޽�
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"PointMesh"));

	// ��ƼŬ ���� ����
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ParticleRenderMtrl"));

	// ��ƼŬ ������Ʈ ��ǻƮ ���̴�	
	m_UpdateCS = (CParticleUpdateShader*)CResMgr::GetInst()->FindRes<CComputeShader>(L"ParticleUpdateCS").Get();

	// ��ƼŬ ���� �ʱ� ������
	tParticle arrParticle[100] = { };
	float fAngle = XM_2PI / 100.f;
	float fRadius = 20.f;
	float fSpeed = 100.f;

	for (UINT i = 0; i < 100; ++i)
	{
		arrParticle[i].vWorldPos = Vec3(fRadius * cosf(fAngle * (float)i), fRadius * sinf(fAngle * (float)i), 100.f);
		arrParticle[i].vVelocity = arrParticle[i].vWorldPos;
		arrParticle[i].vVelocity.z = 0.f;
		arrParticle[i].vVelocity.Normalize();
		arrParticle[i].vVelocity *= fSpeed;
		arrParticle[i].vWorldScale = Vec3(10.f, 10.f, 1.f);
		arrParticle[i].Age = -1.f;		
	}
	
	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_ModuleData.iMaxParticleCount, SB_TYPE::READ_WRITE, false, arrParticle);

	m_RWBuffer = new CStructuredBuffer;
	m_RWBuffer->Create(sizeof(tRWParticleBuffer), 1, SB_TYPE::READ_WRITE, true);

	m_ModuleDataBuffer = new CStructuredBuffer;
	m_ModuleDataBuffer->Create(sizeof(tParticleModule), 1, SB_TYPE::READ_ONLY, true);
}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;

	if (nullptr != m_RWBuffer)
		delete m_RWBuffer;

	if (nullptr != m_ModuleDataBuffer)
		delete m_ModuleDataBuffer;
}


void CParticleSystem::finaltick()
{
	// ���� ����Ʈ ���
	// 1�� ���� �ð�
	float fTimePerCount = 1.f / (float)m_ModuleData.SpawnRate;
	m_AccTime += DT;

	// �����ð��� ���� �����ð��� �Ѿ��
	if (fTimePerCount < m_AccTime)
	{
		// �ʰ� ���� ==> ���� ����
		float fData = m_AccTime / fTimePerCount;

		// �������� ���� �ð�
		m_AccTime = fTimePerCount * (fData - floor(fData));

		// ���ۿ� ���� ī��Ʈ ����
		tRWParticleBuffer rwbuffer = { (int)fData, };		
		m_RWBuffer->SetData(&rwbuffer);
	}


	// ��ƼŬ ������Ʈ ��ǻƮ ���̴�
	m_ModuleDataBuffer->SetData(&m_ModuleData);

	m_UpdateCS->SetParticleBuffer(m_ParticleBuffer);
	m_UpdateCS->SetRWParticleBuffer(m_RWBuffer);
	m_UpdateCS->SetModuleData(m_ModuleDataBuffer);
	m_UpdateCS->SetNoiseTexture(CResMgr::GetInst()->FindRes<CTexture>(L"Noise_03"));

	m_UpdateCS->Execute();
}

void CParticleSystem::render()
{
	Transform()->UpdateData();

	// ��ƼŬ���� t20 �� ���ε�
	m_ParticleBuffer->UpdateData(20, PIPELINE_STAGE::PS_ALL);

	// Particle Render	
	GetMaterial()->UpdateData();
	GetMesh()->render_particle(m_ModuleData.iMaxParticleCount);

	// ��ƼŬ ���� ���ε� ����
	m_ParticleBuffer->Clear();
}