#include "pch.h"
#include "CMeshRender.h"

#include "CGraphicsShader.h"
#include "CMesh.h"

CMeshRender::CMeshRender()
	: CComponent(COMPONENT_TYPE::MESHRENDER)	
	, m_pMesh(nullptr)
	, m_pShader(nullptr)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::finaltick()
{
}

void CMeshRender::render()
{
	if (nullptr == m_pMesh || nullptr == m_pShader)
		return;

	// Transform ¿¡ UpdateData ¿äÃ»

	m_pShader->UpdateData();
	m_pMesh->render();
}