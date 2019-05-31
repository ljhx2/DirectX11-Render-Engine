#pragma once

#ifndef _D3D_RENDERER_H_
#define _D3D_RENDERER_H_

class gDeviceManager;

class D3DRenderer
{
public:
	bool CreateDevice(HWND hWnd, UINT backBufferWidth, UINT backBufferHeight);
	void DestroyDevice();
	void OnReSize(UINT backBufferWidth, UINT backBufferHeight);

	bool BeginFrame();
	void EndFrame();
	void Present();

	

public:
	D3DRenderer();
	virtual ~D3DRenderer();

private:
	gDeviceManager* m_d3dDeviceMgr;
};

#endif // _D3D_RENDERER_H_