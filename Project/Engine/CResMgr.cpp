#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
}

void CResMgr::init()
{
	CreateDefaultMesh();
	CreateDefaultGraphicsShader();
	LoadDefaultTexture();
}

void CResMgr::CreateDefaultMesh()
{	
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;


	Ptr<CMesh> pMesh = nullptr;
	// =============
	// RectMesh 생성
	// =============	
	// 0 --- 1 
	// |  \  |
	// 3 --- 2
	v.vPos = Vec3(-0.5f, 0.5f, 0.5f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.5f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.5f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.5f);
	v.vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes(L"RectMesh", pMesh);
}

void CResMgr::CreateDefaultGraphicsShader()
{
	Ptr<CGraphicsShader> pShader = nullptr;

	// ===========
	// Test Shader
	// ===========
	pShader = new CGraphicsShader;
	pShader->SetKey(L"TestShader");
	pShader->CreateVertexShader(L"shader\\test.fx", "VS_Test");
	pShader->CreatePixelShader(L"shader\\test.fx", "PS_Test");

	AddRes(L"TestShader", pShader);
}

void CResMgr::LoadDefaultTexture()
{
	/*wstring strContent = CPathMgr::GetInst()->GetContentPath();

	wstring strFilePath = strContent + L"texture\\Fighter.bmp";
	Ptr<CRes> pTexture = new CTexture;
	pTexture->SetKey(L"PlayerTex");
	pTexture->SetRelativePath(L"texture\\Fighter.bmp");
	pTexture->Load(strFilePath);

	m_arrRes[(UINT)RES_TYPE::TEXTURE].insert(make_pair(pTexture->GetKey(), pTexture.Get()));*/


	Ptr<CTexture> pTexture = Load<CTexture>(L"PlayerTex", L"texture\\Fighter.bmp");


	// t0 바인딩
	((CTexture*)pTexture.Get())->UpdateData(0);
}