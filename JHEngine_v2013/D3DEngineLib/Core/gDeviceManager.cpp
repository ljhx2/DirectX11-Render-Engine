#include "..\Common.h"
#include "gDeviceManager.h"


gDeviceManager::gDeviceManager()
{
	md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	mEnable4xMsaa = false;
	m4xMsaaQulity = 0;

	md3dDevice = 0;
	md3dImmediateContext = 0;
	mSwapChain = 0;

	mDepthStencilBuffer = 0;
	mRenderTargetView = 0;
	mDepthStencilView = 0;

	ZeroMemory(&mScreenViewport, sizeof(D3D10_VIEWPORT));
}


gDeviceManager::~gDeviceManager()
{
	DestroyDirect3D();
}

bool gDeviceManager::InitDirect3D(HWND MainWnd, UINT ClientWidth, UINT ClientHeight)
{
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,						//생성할 장치를 나타내는 디스플레이 어댑터 (0 == 기본 디스플레이 어뎁터)
		md3dDriverType,			//드라이버타입
		0,						//소프트웨어 구동기
		createDeviceFlags,		//추가적인 장치 생성 플래그
		0, 0,					//기능 수준 (0 == 지원되는 최고 기능 수준), 기능수준의 원소개수
		D3D11_SDK_VERSION,
		&md3dDevice,			//함수가 생성한 장치
		&featureLevel,			//pFeatureLevels배열에서 처음으로 지원되는 기능
		&md3dImmediateContext);	//생성된 장치 문맥

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	// 하드웨어 4x msaa를 위한 품질 수준 지원 점검
	HR(md3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQulity));
	assert(m4xMsaaQulity > 0);	//다렉11이 지원되는 장치에는 4x msaa를 항상 지원한다. 따라서 항상 0보다 크다.


								//교환사슬 특성 설정
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = ClientWidth;										//원하는 후면 버퍼 너비
	sd.BufferDesc.Height = ClientHeight;									//원하는 후면 버퍼 높이
	sd.BufferDesc.RefreshRate.Numerator = 60;								//디스플레이 모드 갱신률
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						//후면버퍼 픽셀 형식
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	//디스플레이 스캔라인 모드
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					//디스플레이 비례 모드

																			//4x msaa 사용?
	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQulity - 1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		//버퍼의 용도
	sd.BufferCount = 1;										//교환 사슬에서 사용할 후면 버퍼의 개수
	sd.OutputWindow = MainWnd;							//렌더링 결과를 표시할 창의 핸들
	sd.Windowed = true;										//창모드
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;				//교환 효과 DXGI_SWAP_EFFECT_DISCARD == 가장 효율적인 제시 방법
	sd.Flags = 0;											//추가적인 플래그

															//교환 사슬의 생성
															//IDXGIFactory 인스턴스를 통해 교환 사슬 인터페이스를 생성한다

	IDXGIDevice* dxgiDevice = 0;
	HR(md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	//IDXGIFactory인터페이스를 얻게되었다
	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	//이제 교환 사슬을 생성한다.
	HR(dxgiFactory->CreateSwapChain(md3dDevice, &sd, &mSwapChain));

	//획득한 COM 인터페이스들을 해제한다.
	SAFE_RELEASE(dxgiDevice);
	SAFE_RELEASE(dxgiAdapter);
	SAFE_RELEASE(dxgiFactory);

	return true;

}

void gDeviceManager::OnResize(UINT ClientWidth, UINT ClientHeight)
{
	assert(md3dImmediateContext);
	assert(md3dDevice);
	assert(mSwapChain);

	//이전 뷰들과 깊이버퍼를 지운다
	SAFE_RELEASE(mRenderTargetView);
	SAFE_RELEASE(mDepthStencilView);
	SAFE_RELEASE(mDepthStencilBuffer);

	//스왑체인의 크기를 조절하고 렌더타겟뷰를 재생성한다.
	HR(mSwapChain->ResizeBuffers(1, ClientWidth, ClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView));
	SAFE_RELEASE(backBuffer);

	//depth/stencil 버퍼와 뷰를 생성
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = ClientWidth;
	depthStencilDesc.Height = ClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// 4X MSAA 사용?
	if (mEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQulity - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(md3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
	HR(md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));

	//파이프라인에 뷰들을 묶는다
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	//뷰포트 설정
	mScreenViewport.TopLeftX = 0;
	mScreenViewport.TopLeftY = 0;
	mScreenViewport.Width = static_cast<float>(ClientWidth);
	mScreenViewport.Height = static_cast<float>(ClientHeight);
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;

	md3dImmediateContext->RSSetViewports(1, &mScreenViewport);
}

void gDeviceManager::DestroyDirect3D()
{
	SAFE_RELEASE(mRenderTargetView);
	SAFE_RELEASE(mDepthStencilView);
	SAFE_RELEASE(mDepthStencilBuffer);

	SAFE_RELEASE(mSwapChain);
	if (md3dImmediateContext)
		md3dImmediateContext->ClearState();
	SAFE_RELEASE(md3dImmediateContext);
	SAFE_RELEASE(md3dDevice);
}

bool gDeviceManager::BeginFrame()
{
	assert(md3dImmediateContext);
	assert(mSwapChain);

	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Black));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return true;
}

void gDeviceManager::EndFrame()
{
}

void gDeviceManager::Present()
{
	mSwapChain->Present(0, 0);
}

