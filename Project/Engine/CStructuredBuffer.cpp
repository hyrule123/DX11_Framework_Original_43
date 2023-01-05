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
	m_iElementSize = _iElementSize;
	m_iElementCount = _iElementCount;

	UINT iBufferSize = m_iElementSize * _iElementCount;

	// 16바이트 단위 메모리 정렬
	assert(!(iBufferSize % 16));

	// 상수버퍼 생성
	m_tDesc.ByteWidth = iBufferSize;
	m_tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	m_tDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	m_tDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_tDesc.StructureByteStride = m_iElementSize;
	
	if (FAILED(DEVICE->CreateBuffer(&m_tDesc, nullptr, m_SB.GetAddressOf())))
	{
		assert(nullptr);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};

	SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	SRVDesc.BufferEx.FirstElement = 0;
	SRVDesc.BufferEx.Flags = 0;
	SRVDesc.BufferEx.NumElements = _iElementCount;

	if(FAILED(DEVICE->CreateShaderResourceView(m_SB.Get(), &SRVDesc, &m_SRV)))
		assert(nullptr);
}

void CStructuredBuffer::SetData(void* _pSrc, UINT _iSize)
{
	if (nullptr == _pSrc || nullptr == m_SB || 0 == _iSize)
		return;
	
	D3D11_MAPPED_SUBRESOURCE Res = {};
	if(FAILED(CONTEXT->Map(m_SB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Res)))
		assert(nullptr);

	memcpy(Res.pData, _pSrc, _iSize);

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
	if (PIPELINE_STAGE::PS_VERTEX & _iPipeLineStage)
	{
		CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}
}