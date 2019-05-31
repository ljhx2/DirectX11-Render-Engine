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
		0,						//������ ��ġ�� ��Ÿ���� ���÷��� ����� (0 == �⺻ ���÷��� ���)
		md3dDriverType,			//����̹�Ÿ��
		0,						//����Ʈ���� ������
		createDeviceFlags,		//�߰����� ��ġ ���� �÷���
		0, 0,					//��� ���� (0 == �����Ǵ� �ְ� ��� ����), ��ɼ����� ���Ұ���
		D3D11_SDK_VERSION,
		&md3dDevice,			//�Լ��� ������ ��ġ
		&featureLevel,			//pFeatureLevels�迭���� ó������ �����Ǵ� ���
		&md3dImmediateContext);	//������ ��ġ ����

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

	// �ϵ���� 4x msaa�� ���� ǰ�� ���� ���� ����
	HR(md3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQulity));
	assert(m4xMsaaQulity > 0);	//�ٷ�11�� �����Ǵ� ��ġ���� 4x msaa�� �׻� �����Ѵ�. ���� �׻� 0���� ũ��.


								//��ȯ�罽 Ư�� ����
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = ClientWidth;										//���ϴ� �ĸ� ���� �ʺ�
	sd.BufferDesc.Height = ClientHeight;									//���ϴ� �ĸ� ���� ����
	sd.BufferDesc.RefreshRate.Numerator = 60;								//���÷��� ��� ���ŷ�
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						//�ĸ���� �ȼ� ����
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	//���÷��� ��ĵ���� ���
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					//���÷��� ��� ���

																			//4x msaa ���?
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

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		//������ �뵵
	sd.BufferCount = 1;										//��ȯ �罽���� ����� �ĸ� ������ ����
	sd.OutputWindow = MainWnd;							//������ ����� ǥ���� â�� �ڵ�
	sd.Windowed = true;										//â���
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;				//��ȯ ȿ�� DXGI_SWAP_EFFECT_DISCARD == ���� ȿ������ ���� ���
	sd.Flags = 0;											//�߰����� �÷���

															//��ȯ �罽�� ����
															//IDXGIFactory �ν��Ͻ��� ���� ��ȯ �罽 �������̽��� �����Ѵ�

	IDXGIDevice* dxgiDevice = 0;
	HR(md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	//IDXGIFactory�������̽��� ��ԵǾ���
	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	//���� ��ȯ �罽�� �����Ѵ�.
	HR(dxgiFactory->CreateSwapChain(md3dDevice, &sd, &mSwapChain));

	//ȹ���� COM �������̽����� �����Ѵ�.
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

	//���� ���� ���̹��۸� �����
	SAFE_RELEASE(mRenderTargetView);
	SAFE_RELEASE(mDepthStencilView);
	SAFE_RELEASE(mDepthStencilBuffer);

	//����ü���� ũ�⸦ �����ϰ� ����Ÿ�ٺ並 ������Ѵ�.
	HR(mSwapChain->ResizeBuffers(1, ClientWidth, ClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView));
	SAFE_RELEASE(backBuffer);

	//depth/stencil ���ۿ� �並 ����
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = ClientWidth;
	depthStencilDesc.Height = ClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// 4X MSAA ���?
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

	//���������ο� ����� ���´�
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	//����Ʈ ����
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

