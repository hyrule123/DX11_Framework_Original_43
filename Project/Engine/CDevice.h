#pragma once

class CDevice
	: public CSingleton<CDevice>
{
private:
	HWND							m_hWnd;

	ComPtr<ID3D11Device>			m_Device;		// GPU �޸� �Ҵ� 	
	ComPtr<ID3D11DeviceContext>		m_Context;		// GPU ����, ������, ���� ����

	ComPtr<IDXGISwapChain>			m_SwapChain;

	ComPtr<ID3D11Texture2D>			m_RTTex;
	ComPtr<ID3D11RenderTargetView>	m_RTV;

	ComPtr<ID3D11Texture2D>			m_DSTex;
	ComPtr<ID3D11DepthStencilView>	m_DSV;

	D3D11_VIEWPORT					m_ViewPort;

	// ����Ÿ�� �ػ�
	Vec2							m_vRenderResolution;
						



	// ID3D11RenderTargetView
	// ID3D11DepthStencilView
	// ID3D11ShaderResourceView
	// ID3D11UnorderedAccessView



public:
	int init(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	void ClearTarget(float(&_color)[4]);
	void Present()	{ m_SwapChain->Present(0, 0); }

private:
	int CreateSwapChain();
	int CreateView();

public:
	CDevice();
	~CDevice();
};

