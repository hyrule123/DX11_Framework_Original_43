#include "pch.h"
#include "Test.h"

#include "CDevice.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

// 정점 버퍼
ComPtr<ID3D11Buffer> g_VB;
ComPtr<ID3D11Buffer> g_IB;
ComPtr<ID3D11Buffer> g_CB; // 상수버퍼


// 쉐이더
ComPtr<ID3DBlob>	g_VSBlob;
ComPtr<ID3DBlob>	g_PSBlob;
ComPtr<ID3DBlob>	g_ErrBlob;

ComPtr<ID3D11VertexShader>	g_VS;
ComPtr<ID3D11PixelShader>	g_PS;

// InputLayout
ComPtr<ID3D11InputLayout>	g_Layout;



// Vertex 
Vtx		g_arrVtx[4] = {};
UINT	g_arrIdx[6] = {};


void Init()
{
	// 0 --- 1 
	// |  \  |
	// 3 --- 2
	g_arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.5f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.5f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	g_arrVtx[3].vColor = Vec4(0.f, 0.f, 0.f, 1.f);


	D3D11_BUFFER_DESC tBufferDesc = {};

	// 정점 저장용도
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;

	// SystemMemroy 에서 수정 가능한 버퍼
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	// 버퍼 크기
	tBufferDesc.ByteWidth = sizeof(Vtx) * 4;

	// 버퍼 생성
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_arrVtx;
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, g_VB.GetAddressOf())))
	{
		assert(nullptr);
	}


	g_arrIdx[0] = 0;
	g_arrIdx[1] = 2;
	g_arrIdx[2] = 3;

	g_arrIdx[3] = 0;
	g_arrIdx[4] = 1;
	g_arrIdx[5] = 2;

	// 인덱스 저장용도
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;

	// 수정 불가능
	tBufferDesc.CPUAccessFlags = 0;
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// 버퍼 크기
	tBufferDesc.ByteWidth = sizeof(UINT) * 6;

	// 버퍼 생성	
	tSub.pSysMem = g_arrIdx;
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, g_IB.GetAddressOf())))
	{
		assert(nullptr);
	}





	// Shader 파일 경로
	wstring strShaderFile = CPathMgr::GetInst()->GetContentPath();
	strShaderFile += L"shader\\test.fx";

	// VertexShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "VS_Test", "vs_5_0", 0, 0, g_VSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)g_ErrBlob->GetBufferPointer()
			, "Vertex Shader Compile Failed!!", MB_OK);
	}

	// PixelShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_Test", "ps_5_0", 0, 0, g_PSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)g_ErrBlob->GetBufferPointer()
			, "Pixel Shader Compile Failed!!", MB_OK);
	}

	// 컴파일된 객체로 VertexShader, PixelShader 를 만든다.
	DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize()
		, nullptr, g_VS.GetAddressOf());

	DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer(), g_PSBlob->GetBufferSize()
		, nullptr, g_PS.GetAddressOf());


	// InputLayout 생성
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};

	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;
	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;


	LayoutDesc[1].SemanticName = "COLOR";
	LayoutDesc[1].SemanticIndex = 0;
	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;

	if (FAILED(DEVICE->CreateInputLayout(LayoutDesc, 2
		, g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize()
		, g_Layout.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void Tick()
{
	if (KEY_PRESSED(KEY::UP))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPos.y += DT * 1.f;
		}
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPos.y -= DT * 1.f;
		}
	}

	if(KEY_PRESSED(KEY::LEFT))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPos.x -= DT * 1.f;
		}
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPos.x += DT * 1.f;
		}
	}	

	// g_arrVtx ==> g_VB
	D3D11_MAPPED_SUBRESOURCE tSubRes = {};

	CONTEXT->Map(g_VB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSubRes);
	memcpy(tSubRes.pData, g_arrVtx, sizeof(Vtx) * 4);	
	CONTEXT->Unmap(g_VB.Get(), 0);
}

void Render()
{
	// IA
	UINT iStride = sizeof(Vtx);
	UINT iOffset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(g_IB.Get(), DXGI_FORMAT_R32_UINT, 0);

	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	CONTEXT->DrawIndexed(6, 0, 0);
}

void Release()
{

}
