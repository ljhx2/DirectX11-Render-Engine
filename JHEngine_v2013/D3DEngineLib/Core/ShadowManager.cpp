#include "..\Common.h"
#include "ShadowManager.h"

#include "gDeviceManager.h"

#include "..\GameObject\Component\LightComponent\LightManager.h"

CShadowManager::CShadowManager()
	: m_shadowMap(NULL), m_shadowEffect(NULL), m_showShadowTexture(false)
{
	XMMATRIX i = XMMatrixIdentity();
	
	XMStoreFloat4x4(&m_lightView, i);
	XMStoreFloat4x4(&m_lightProj, i);
	XMStoreFloat4x4(&m_lightViewProj, i);
	XMStoreFloat4x4(&m_shadowTransform, i);
}


CShadowManager::~CShadowManager()
{
	SAFE_DELETE(m_shadowMap);
	SAFE_DELETE(m_shadowEffect);
	SAFE_DELETE(m_debugEffect);
}

void CShadowManager::Init()
{
	const UINT ShadowMapSize = 2048U;
	m_shadowMap = new CShadowMap(g_pDeviceMgr->GetDevice(), ShadowMapSize, ShadowMapSize);

	m_shadowEffect = new CShadowBuildEffect(g_pDeviceMgr->GetDevice(), L"FX/BuildShadowMap.fx");

	//shadowMap test
	m_debugEffect = new CDebugTexEffect(g_pDeviceMgr->GetDevice(), L"FX/DebugTexture.fx");
	CerateVertex();

}

void CShadowManager::BeginShadowMap()
{
	CalcLightMatrix();

	m_shadowMap->BindDsvAndSetNullRenderTarget(g_pDeviceMgr->GetDeviceContext());
}

void CShadowManager::EndShadowMap()
{
	g_pDeviceMgr->GetDeviceContext()->RSSetState(0);
	
	ID3D11RenderTargetView* renderTargets[1] = { g_pDeviceMgr->GetRenderTargetView() };
	g_pDeviceMgr->GetDeviceContext()->OMSetRenderTargets(1, renderTargets, g_pDeviceMgr->GetDepthStencilView());
	g_pDeviceMgr->GetDeviceContext()->RSSetViewports(1, &(g_pDeviceMgr->GetScreenViewport()));
}

void CShadowManager::CalcLightMatrix()
{
	XMFLOAT3 center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//float radius = sqrtf(10.0f*10.0f + 15.0f*15.0f);
	float radius = 300.0f;

	int dirLightCount = g_pLightMgr->GetDirectionalLightSize();
	if (dirLightCount <= 0) return;

	XMVECTOR lightDir = g_pLightMgr->GetVecDirectionalLight()[0]->GetDirectionXM();
	lightDir = XMVector3Normalize(lightDir);
	XMVECTOR lightPos = -2.0f*radius*lightDir;
	XMVECTOR targetPos = XMLoadFloat3(&center);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(lightPos, targetPos, up);

	XMFLOAT3 sphereCenterLS;
	XMStoreFloat3(&sphereCenterLS, XMVector3TransformCoord(targetPos, V));

	// Ortho frustum in light space encloses scene.
	float l = sphereCenterLS.x - radius;
	float b = sphereCenterLS.y - radius;
	float n = sphereCenterLS.z - radius;
	float r = sphereCenterLS.x + radius;
	float t = sphereCenterLS.y + radius;
	float f = sphereCenterLS.z + radius;
	XMMATRIX P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	XMMATRIX T(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f);

	XMMATRIX S = V*P*T;

	XMStoreFloat4x4(&m_lightView, V);
	XMStoreFloat4x4(&m_lightProj, P);
	XMStoreFloat4x4(&m_lightViewProj, V*P);
	XMStoreFloat4x4(&m_shadowTransform, S);
}

void CShadowManager::CerateVertex()
{
	m_screenQuad = new CMesh(L"ScreenQuad");

	Vertex_PNT v[4];
	UINT i[6];

	v[0] = Vertex_PNT(-1.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f);

	v[1] = Vertex_PNT(-1.0f, +1.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f);

	v[2] = Vertex_PNT(+1.0f, +1.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f);

	v[3] = Vertex_PNT(+1.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 1.0f);

	i[0] = 0;
	i[1] = 1;
	i[2] = 2;

	i[3] = 0;
	i[4] = 2;
	i[5] = 3;

	m_screenQuad->SetVertexCount(4U);
	m_screenQuad->SetIndexCount(6U);
	m_screenQuad->SetFaceCount(2U);
	m_screenQuad->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_screenQuad->SetVertexStride(sizeof(Vertex_PNT));
	m_screenQuad->SetVertexOffset(0U);
	m_screenQuad->SetIndexFormat(DXGI_FORMAT_R32_UINT);

	if (m_screenQuad->CreateVertexBuffer(v, sizeof(Vertex_PNT) * m_screenQuad->GetVertexCount()) == false
		|| m_screenQuad->CreateIndexBuffer(i, sizeof(UINT) * m_screenQuad->GetIndexCount()) == false)
	{
		assert(!"CreateMesh Failed");
		SAFE_DELETE(m_screenQuad);
		return;
	}

	ID3DX11EffectTechnique* tech = m_debugEffect->ViewRedTech;
	if (m_screenQuad->CreateLayout(vertexPNTLayout, 3, tech, 0) == false)
	{
		assert(!"CreateLayout Failed");
		SAFE_DELETE(m_screenQuad);
		return;
	}
}

void CShadowManager::RenderScreenQuad()
{
	if (!m_showShadowTexture) return;

	g_pDeviceMgr->GetDeviceContext()->IASetInputLayout(m_screenQuad->GetVertexLayout());
	g_pDeviceMgr->GetDeviceContext()->IASetPrimitiveTopology(m_screenQuad->GetPrimitiveTopology());

	ID3D11Buffer* vertexBuffer = m_screenQuad->GetVertexBuffer();
	UINT stride = m_screenQuad->GetVertexStride();
	UINT offset = m_screenQuad->GetVertexOffset();

	g_pDeviceMgr->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	g_pDeviceMgr->GetDeviceContext()->IASetIndexBuffer(m_screenQuad->GetIndexBuffer(), m_screenQuad->GetIndexFormat(), 0);

	// Scale and shift quad to lower-right corner.
	XMMATRIX world(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f);

	ID3DX11EffectTechnique* tech = m_debugEffect->ViewRedTech;
	D3DX11_TECHNIQUE_DESC techDesc;

	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_debugEffect->SetWorldViewProj(world);

		m_debugEffect->SetTexture(g_pShadowMgr->GetShadowMap()->GetDepthMapSRV());

		tech->GetPassByIndex(p)->Apply(0, g_pDeviceMgr->GetDeviceContext());
		g_pDeviceMgr->GetDeviceContext()->DrawIndexed(6, 0, 0);
	}
}