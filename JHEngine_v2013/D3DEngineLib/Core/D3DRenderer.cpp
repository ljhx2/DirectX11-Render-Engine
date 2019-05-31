#include "..\Common.h"
#include "D3DRenderer.h"


D3DRenderer::D3DRenderer()
	: m_d3dDeviceMgr(NULL)
{
}


D3DRenderer::~D3DRenderer()
{
}

bool D3DRenderer::CreateDevice(HWND hWnd, UINT backBufferWidth, UINT backBufferHeight)
{
	m_d3dDeviceMgr = g_pDeviceMgr;

	if (m_d3dDeviceMgr->InitDirect3D(hWnd, backBufferWidth, backBufferHeight))
	{
		m_d3dDeviceMgr->OnResize(backBufferWidth, backBufferHeight);
		return true;
	}
	
	return false;
}

void D3DRenderer::OnReSize(UINT backBufferWidth, UINT backBufferHeight)
{
	m_d3dDeviceMgr->OnResize(backBufferWidth, backBufferHeight);
}

void D3DRenderer::DestroyDevice()
{
	if (!m_d3dDeviceMgr) return;

	m_d3dDeviceMgr->DestroyDirect3D();
}

bool D3DRenderer::BeginFrame()
{
	return m_d3dDeviceMgr->BeginFrame();
}

void D3DRenderer::EndFrame()
{
	m_d3dDeviceMgr->EndFrame();
}

void D3DRenderer::Present()
{
	m_d3dDeviceMgr->Present();
}
