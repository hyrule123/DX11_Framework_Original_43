#include "pch.h"
#include "CDevice.h"

#include "CEngine.h"

CDevice::CDevice()
    : m_hWnd(nullptr)  
    , m_ViewPort{}
{
}

CDevice::~CDevice()
{
}

int CDevice::init(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
    m_hWnd = _hWnd;    
    m_vRenderResolution = Vec2((float)_iWidth, (float)_iHeight);

    int iFlag = 0;
#ifdef _DEBUG
    iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL eLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

      

    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
        , nullptr, iFlag
        , nullptr, 0
        , D3D11_SDK_VERSION
        , m_Device.GetAddressOf(), &eLevel
        , m_Context.GetAddressOf())))
    {
        MessageBox(nullptr, L"Device, Context 생성 실패", L"Device 초기화 에러", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateSwapChain()))
    {
        MessageBox(nullptr, L"스왚체인 생성 실패", L"Device 초기화 에러", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateView()))
    {
        MessageBox(nullptr, L"View 생성 실패", L"Device 초기화 에러", MB_OK);
        return E_FAIL;
    }


    // 출력 타겟 설정
    m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());


    // ViewPort 설정
    m_ViewPort.TopLeftX = 0.f;
    m_ViewPort.TopLeftY = 0.f;

    Vec2 vWindowResol = CEngine::GetInst()->GetWindowResolution();
    m_ViewPort.Width = vWindowResol.x;
    m_ViewPort.Height = vWindowResol.y;

    m_ViewPort.MinDepth = 0.f;
    m_ViewPort.MaxDepth = 1.f;

    m_Context->RSSetViewports(1, &m_ViewPort);



    return S_OK; // E_FAIL;
}

int CDevice::CreateSwapChain()
{
    // 스왚체인 설정
    DXGI_SWAP_CHAIN_DESC tDesc = {};

    tDesc.OutputWindow = m_hWnd;    // 출력 윈도우
    tDesc.Windowed = true;          // 창모드, 전체화면 모드

    tDesc.BufferCount = 1;              
    tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    tDesc.BufferDesc.Width = (UINT)m_vRenderResolution.x;
    tDesc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
    tDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    tDesc.BufferDesc.RefreshRate.Denominator = 1;
    tDesc.BufferDesc.RefreshRate.Numerator = 60;
    tDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    tDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    
    tDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

    tDesc.SampleDesc.Count = 1;
    tDesc.SampleDesc.Quality = 0;
    tDesc.Flags = 0;
    

    // 스왚체인 생성
    ComPtr<IDXGIDevice>  pDXGIDevice;
    ComPtr<IDXGIAdapter> pAdapter;
    ComPtr<IDXGIFactory> pFactory;

    HRESULT hr = S_OK;

    hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());
    hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
    hr = pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

    hr = pFactory->CreateSwapChain(m_Device.Get(), &tDesc, m_SwapChain.GetAddressOf());

    return hr;
}

int CDevice::CreateView()
{
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RTTex.GetAddressOf());
    
    if (FAILED(m_Device->CreateRenderTargetView(m_RTTex.Get(), nullptr, m_RTV.GetAddressOf())))
    {
        return E_FAIL;
    }

    // DepthStencil 용도 텍스쳐 생성
    D3D11_TEXTURE2D_DESC tDesc = {};

    tDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    // 반드시 렌더타겟과 같은 해상도로 설정해야 함
    tDesc.Width = (UINT)m_vRenderResolution.x;
    tDesc.Height = (UINT)m_vRenderResolution.y;
    tDesc.ArraySize = 1;

    tDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;    
    tDesc.Usage = D3D11_USAGE_DEFAULT;
    tDesc.CPUAccessFlags = 0;

    tDesc.MipLevels = 1;    // 원본만 생성

    tDesc.SampleDesc.Count = 1;
    tDesc.SampleDesc.Quality = 0;
    

    if (FAILED(m_Device->CreateTexture2D(&tDesc, nullptr, m_DSTex.GetAddressOf())))
    {
        return E_FAIL;
    }

    // DepthStencilView 생성
    if (FAILED(m_Device->CreateDepthStencilView(m_DSTex.Get(), nullptr, m_DSV.GetAddressOf())))
    {
        return E_FAIL;
    }


    return S_OK;
}


void CDevice::ClearTarget(float(&_color)[4])
{
    m_Context->ClearRenderTargetView(m_RTV.Get(), _color);
}