#include "pch.h"
#include "CConstBuffer.h"

#include "CDevice.h"

CConstBuffer::CConstBuffer(UINT _iRegisterNum)
	: m_Desc{}
	, m_iRegisterNum(_iRegisterNum)
	, m_iElementSize(0)
	, m_iElementCount(0)
{
}

CConstBuffer::~CConstBuffer()
{
}

void CConstBuffer::Create(UINT _iElementSize, UINT _iElementCount)
{
	m_iElementSize = _iElementSize;
	m_iElementCount = _iElementCount;

	UINT iBufferSize = m_iElementSize * _iElementCount;

	// 16����Ʈ ���� �޸� ����
	assert(!(iBufferSize % 16));	

	// ������� ����
	m_Desc.ByteWidth = iBufferSize;
	m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_Desc.Usage = D3D11_USAGE_DYNAMIC;
	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(DEVICE->CreateBuffer(&m_Desc, nullptr, m_CB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

