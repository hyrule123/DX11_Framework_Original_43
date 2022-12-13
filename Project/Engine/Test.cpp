#include "pch.h"
#include "Test.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"

#include "CDevice.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CMesh.h"
#include "CGraphicsShader.h"

ComPtr<ID3D11Buffer> g_CB; // 상수버퍼



Vec4		 g_PlayerPos;
CGameObject* g_Obj = nullptr;


CMesh*				g_RectMesh = nullptr;
CGraphicsShader*	g_pShader = nullptr;


void Init()
{
	// RectMesh 생성

	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;
	// 0 --- 1 
	// |  \  |
	// 3 --- 2
	v.vPos = Vec3(-0.5f, 0.5f, 0.5f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.5f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.5f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.5f);
	v.vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	g_RectMesh = new CMesh;
	g_RectMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());


	// Shader 생성
	g_pShader = new CGraphicsShader;
	g_pShader->CreateVertexShader(L"shader\\test.fx", "VS_Test");
	g_pShader->CreatePixelShader(L"shader\\test.fx", "PS_Test");


	// 오브젝트 생성
	g_Obj = new CGameObject;
	g_Obj->AddComponent(new CTransform);
	g_Obj->AddComponent(new CMeshRender);
	g_Obj->AddComponent(new CPlayerScript);

	g_Obj->MeshRender()->SetMesh(g_RectMesh);
	g_Obj->MeshRender()->SetShader(g_pShader);


	// 상수버퍼 생성
	// 16바이트 단위 메모리 정렬
	D3D11_BUFFER_DESC tBufferDesc = {};

	tBufferDesc.ByteWidth = sizeof(Vec4);
	tBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	
	
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, nullptr, g_CB.GetAddressOf())))
	{
		assert(nullptr);
	}




	




}

void Tick()
{
	g_Obj->tick();
	g_Obj->finaltick();
}

void Render()
{
	g_Obj->render();
}

void Release()
{
	delete g_Obj;
	delete g_RectMesh;
	delete g_pShader;
}
