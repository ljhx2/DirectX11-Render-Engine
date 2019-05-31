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

	ID3D11Device* md3dDevice;					//D3D11 ��ġ
	ID3D11DeviceContext* md3dImmediateContext;	//D3D11 ��ġ
	IDXGISwapChain* mSwapChain;					//������ ��ȯ�� ���� ��ȯ �罽

	ID3D11Texture2D* mDepthStencilBuffer;		//����, ���ٽ� ���۸� ���� 2���� �ؽ�ó
	ID3D11RenderTargetView* mRenderTargetView;	//���� ���� 2���� �ؽ�ó 
	ID3D11DepthStencilView* mDepthStencilView;	//����,���ٽ� ��
	D3D11_VIEWPORT mScreenViewport;				//����Ʈ

												//4X MSAA�� ����Ѵٸ� true�� �����ؾ� �Ѵ�. �⺻�� false
	bool mEnable4xMsaa;
	UINT m4xMsaaQulity;	//4X MSAA�� ǰ�� ����

						//������ ����(�ϵ���� ��ġ �Ǵ� ǥ����ġ ��)
						//�⺻���� D3D_DRIVER_TYPEHARDWARE�̴�
	D3D_DRIVER_TYPE md3dDriverType;
};

#endif // _DEVICE_MGR_H_