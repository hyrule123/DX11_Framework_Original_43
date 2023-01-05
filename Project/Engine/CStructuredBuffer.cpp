#include "pch.h"
#include "CStructuredBuffer.h"

#include "CDevice.h"

CStructuredBuffer::CStructuredBuffer()
	: m_iElementSize(0)
	, m_iElementCount(0)
{
}

CStructuredBuffer::~CStructuredBuffer()
{
}

void CStructuredBuffer::Create(UINT _iElementSize, UINT _iElementCount)
{
	m_SB = nullptr;
	m_SRV = nullptr;


	m_iElementSize = _iElementSize;
	m_iElementCount = _iElementCount;

	UINT iBufferSize = m_iElementSize * _iElementCount;

	// 16����Ʈ ���� �޸� ����
	assert(!(iBufferSize % 16));

	// ������� ����
	m_tDesc.ByteWidth = iBufferSize;				// ���� ũ��
	m_tDesc.StructureByteStride = m_iElementSize;	// ������ ����

	m_tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// Texture �������Ϳ� ���̵��ϱ� ���� �÷���
	m_tDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;	// ����ȭ ���� üũ

	m_tDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	if (FAILED(DEVICE->CreateBuffer(&m_tDesc, nullptr, m_SB.GetAddressOf())))
	{
		assert(nullptr);
	}


	// ShaderResourceView ����
	D3D11_SHADER_RESOURCE_VIEW_DESC	m_SRVDesc = {};

	m_SRVDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;
	m_SRVDesc.BufferEx.NumElements = m_iElementCount;

	if (FAILED(DEVICE->CreateShaderResourceView(m_SB.Get(), &m_SRVDesc, m_SRV.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void CStructuredBuffer::SetData(void* _pSrc, UINT _iSize)
{
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_SB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSub);

	memcpy(tSub.pData, _pSrc, _iSize);	

	CONTEXT->Unmap(m_SB.Get(), 0);
}

void CStructuredBuffer::UpdateData(UINT _iRegisterNum, UINT _iPipeLineStage)
{
	if (PIPELINE_STAGE::PS_VERTEX & _iPipeLineStage)
	{
		CONTEXT->VSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_HULL & _iPipeLineStage)
	{
		CONTEXT->HSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_DOMAIN & _iPipeLineStage)
	{
		CONTEXT->DSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_GEOMETRY & _iPipeLineStage)
	{
		CONTEXT->GSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_PIXEL & _iPipeLineStage)
	{
		CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}
}