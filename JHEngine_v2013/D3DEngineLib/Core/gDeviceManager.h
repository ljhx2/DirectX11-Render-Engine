#pragma once

#ifndef _DEVICE_MGR_H_
#define _DEVICE_MGR_H_

#include "Singleton.h"

#define g_pDeviceMgr gDeviceManager::GetInstance()

class gDeviceManager : public CSingleton<gDeviceManager>
{

public:
	bool InitDirect3D(HWND MainWnd, UINT ClientWidth, UINT ClientHeight);
	void OnResize(UINT ClientWidth, UINT ClientHeight);
	void DestroyDirect3D();

	bool BeginFrame();
	void EndFrame();
	void Present();

	ID3D11Device* GetDevice() { return md3dDevice; }
	ID3D11DeviceContext* GetDeviceContext() { return md3dImmediateContext; }
	IDXGISwapChain* GetSwapChain() { return mSwapChain; }

	ID3D11RenderTargetView* GetRenderTargetView() { return mRenderTargetView; }
	ID3D11DepthStencilView* GetDepthStencilView() { return mDepthStencilView; }
	D3D11_VIEWPORT&			GetScreenViewport()	{ return mScreenViewport; }

	UINT Get4xMsaaQulity() { return m4xMsaaQulity; }

public:
	gDeviceManager();
	virtual ~gDeviceManager();

private:

	ID3D11Device* md3dDevice;					//D3D11 장치
	ID3D11DeviceContext* md3dImmediateContext;	//D3D11 장치
	IDXGISwapChain* mSwapChain;					//페이지 전환을 위한 교환 사슬

	ID3D11Texture2D* mDepthStencilBuffer;		//깊이, 스텐실 버퍼를 위한 2차원 텍스처
	ID3D11RenderTargetView* mRenderTargetView;	//랜더 대상용 2차원 텍스처 
	ID3D11DepthStencilView* mDepthStencilView;	//깊이,스텐실 뷰
	D3D11_VIEWPORT mScreenViewport;				//뷰포트

												//4X MSAA를 사용한다면 true로 설정해야 한다. 기본은 false
	bool mEnable4xMsaa;
	UINT m4xMsaaQulity;	//4X MSAA의 품질 수준

						//구동기 종류(하드웨어 장치 또는 표준장치 등)
						//기본값은 D3D_DRIVER_TYPEHARDWARE이다
	D3D_DRIVER_TYPE md3dDriverType;
};

#endif // _DEVICE_MGR_H_