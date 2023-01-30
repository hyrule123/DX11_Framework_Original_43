#include "pch.h"
#include "CComputeShader.h"

#include "CPathMgr.h"
#include "CDevice.h"


CComputeShader::CComputeShader()
	: CShader(RES_TYPE::COMPUTE_SHADER)
{
}

CComputeShader::~CComputeShader()
{
}

void CComputeShader::CreateComputeShader(const wstring& _strFileName, const string& _strFuncName)
{
	// Shader ���� ���
	wstring strShaderFile = CPathMgr::GetInst()->GetContentPath();
	strShaderFile += _strFileName;

	// Shader Compile	
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _strFuncName.c_str(), "cs_5_0", 0, 0, m_CSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)m_ErrBlob->GetBufferPointer()
			, "Compute Shader Compile Failed!!", MB_OK);
	}

	// �����ϵ� ��ü�� Shader �� �����.
	DEVICE->CreateComputeShader(m_CSBlob->GetBufferPointer(), m_CSBlob->GetBufferSize()
		, nullptr, m_CS.GetAddressOf());
}

void CComputeShader::Dispatch(UINT _X, UINT _Y, UINT _Z)
{
	CONTEXT->CSSetShader(m_CS.Get(), nullptr, 0);
	CONTEXT->Dispatch(_X, _Y, _Z);
}

void CComputeShader::UpdateData()
{	
	
}

void CComputeShader::Clear()
{
}
