#include "pch.h"
#include "Test.h"

#include "CDevice.h"

// ���� ����
ComPtr<ID3D11Buffer> g_VB;


// ���̴�




void Init()
{
	Vtx arrVtx[3] = {};

	arrVtx[0].vPos = Vec3(0.f, 1.f, 0.5f);
	arrVtx[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	arrVtx[1].vPos = Vec3(1.f, -1.f, 0.5f);
	arrVtx[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	arrVtx[2].vPos = Vec3(-1.f, -1.f, 0.5f);
	arrVtx[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);


	D3D11_BUFFER_DESC tBufferDesc = {};

	// ���� ����뵵
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;

	// SystemMemroy ���� ���� ������ ����
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	// ���� ũ��
	tBufferDesc.ByteWidth = sizeof(Vtx) * 3;

	// ���� ����
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = arrVtx;
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, g_VB.GetAddressOf())))
	{
		assert(nullptr);
	}
	
	

}

void Tick()
{

}

void Render()
{

}

void Release()
{

}
