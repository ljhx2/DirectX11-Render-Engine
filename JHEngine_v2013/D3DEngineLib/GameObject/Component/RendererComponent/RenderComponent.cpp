#include "..\..\..\Common.h"
#include "RenderComponent.h"


#include "..\..\..\Core\gDeviceManager.h"
#include "..\CameraComponent\CameraComponent.h"
#include "..\CameraComponent\CameraManager.h"
#include "..\..\..\Core\MathHelper.h"

#include "..\..\..\Core\ShadowManager.h"

ImplRTTI(CRenderComponent, IComponent);


CRenderComponent::CRenderComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: IComponent(id, owner)
	, m_mesh(NULL), m_extern_material(NULL), m_effect(NULL)
	, m_castShadow(true), m_receiveShadow(true)
{
	XMMATRIX i = XMMatrixIdentity();
	m_texTransform = 1.0f;
}


CRenderComponent::~CRenderComponent()
{
	if (m_mesh) m_mesh->Release();
	if (m_extern_material) m_extern_material->Release();
	if (m_effect) m_effect->Release();
}

bool CRenderComponent::Setup()
{
	return true;
}

bool CRenderComponent::Update(float deltaTime)
{
	return true;
}

bool CRenderComponent::HandleMessage(const CMessage& msg)
{
	return IComponent::HandleMessage(msg);
}

void CRenderComponent::BuildShadowMap(CXMMATRIX matWorld)
{
	if (!m_castShadow) return;

	g_pDeviceMgr->GetDeviceContext()->IASetInputLayout(m_mesh->GetVertexLayout());
	g_pDeviceMgr->GetDeviceContext()->IASetPrimitiveTopology(m_mesh->GetPrimitiveTopology());

	ID3D11Buffer* vertexBuffer = m_mesh->GetVertexBuffer();
	UINT stride = m_mesh->GetVertexStride();
	UINT offset = m_mesh->GetVertexOffset();

	//view행렬과 proj행렬을 shadowManager에서 구해옴
	XMMATRIX world = matWorld;
	XMMATRIX viewProj = XMLoadFloat4x4(&g_pShadowMgr->GetLightViewProj());
	XMMATRIX worldViewProj = world * viewProj;
	XMMATRIX texTransform = XMMatrixScaling(m_texTransform, m_texTransform, m_texTransform);

	CShadowBuildEffect* buildEffect = g_pShadowMgr->GetShadowEffect();

	ID3DX11EffectTechnique* tech = buildEffect->GetBiuldShadowMapTech();
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		buildEffect->SetWorldViewProj(worldViewProj);
		buildEffect->SetTexTransform(texTransform);

		g_pDeviceMgr->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		g_pDeviceMgr->GetDeviceContext()->IASetIndexBuffer(m_mesh->GetIndexBuffer(), m_mesh->GetIndexFormat(), 0);

		tech->GetPassByIndex(p)->Apply(0, g_pDeviceMgr->GetDeviceContext());
		g_pDeviceMgr->GetDeviceContext()->DrawIndexed(m_mesh->GetIndexCount(), 0, 0);
	}
}

void CRenderComponent::Render(CXMMATRIX matWorld)
{

	//ID3D11RasterizerState* NoCullRS;
	//D3D11_RASTERIZER_DESC noCullDesc;
	//ZeroMemory(&noCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	//noCullDesc.FillMode = D3D11_FILL_SOLID;
	//noCullDesc.CullMode = D3D11_CULL_NONE;
	//noCullDesc.FrontCounterClockwise = false;
	//noCullDesc.DepthClipEnable = true;
	//
	//g_pDeviceMgr->GetDevice()->CreateRasterizerState(&noCullDesc, &NoCullRS);
	//
	//g_pDeviceMgr->GetDeviceContext()->RSSetState(NoCullRS);




	g_pDeviceMgr->GetDeviceContext()->IASetInputLayout(m_mesh->GetVertexLayout());
	g_pDeviceMgr->GetDeviceContext()->IASetPrimitiveTopology(m_mesh->GetPrimitiveTopology());

	ID3D11Buffer* vertexBuffer = m_mesh->GetVertexBuffer();
	UINT stride = m_mesh->GetVertexStride();
	UINT offset = m_mesh->GetVertexOffset();
	
	//view행렬과 proj행렬을 카메라에서 구해옴
	XMMATRIX world = matWorld;
	XMMATRIX worldInvTraspose = CMathHelper::InverseTranspose(world);
	XMMATRIX viewProj = g_pCameraMgr->GetCurrentCamera()->GetViewProjMatrix();
	XMMATRIX worldViewProj = world * viewProj;
	XMMATRIX texTransform = XMMatrixScaling(m_texTransform, m_texTransform, m_texTransform);
	XMMATRIX shadowTransform = XMLoadFloat4x4(&g_pShadowMgr->GetShadowTransform());

	ID3DX11EffectTechnique* tech = m_effect->GetTech();
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_effect->SetWorld(world);
		m_effect->SetWorldInvTranspose(worldInvTraspose);
		m_effect->SetWorldViewProj(worldViewProj);
		m_effect->SetTexTransform(texTransform);
		m_effect->SetMaterial(m_material);
		m_effect->SetReceiveShadow(m_receiveShadow);
		m_effect->SetShadowTransform(world * shadowTransform);
		m_effect->SetShadowMap(g_pShadowMgr->GetShadowMap()->GetDepthMapSRV());
		

		g_pDeviceMgr->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		g_pDeviceMgr->GetDeviceContext()->IASetIndexBuffer(m_mesh->GetIndexBuffer(), m_mesh->GetIndexFormat(), 0);

		tech->GetPassByIndex(p)->Apply(0, g_pDeviceMgr->GetDeviceContext());
		g_pDeviceMgr->GetDeviceContext()->DrawIndexed(m_mesh->GetIndexCount(), 0, 0);
	}

	//NoCullRS->Release();

}

void CRenderComponent::SetEffect(CEffect* effect)
{
	if (m_effect == effect) return;
	if (m_effect) m_effect->Release();
	m_effect = effect;
	if (m_effect) m_effect->AddRef();
}

void CRenderComponent::SetMesh(CMesh* mesh) 
{ 
	if (m_mesh == mesh) return;
	if (m_mesh) m_mesh->Release();
	m_mesh = mesh;  
	if (m_mesh) m_mesh->AddRef();
}

void CRenderComponent::SetExternMaterial(CMaterial* material)
{
	if (m_extern_material == material) return;
	if (m_extern_material) m_extern_material->Release();
	m_extern_material = material;
	if (m_extern_material) m_extern_material->AddRef();

	CopyExternMaterialToMaterial();

}

void CRenderComponent::CopyExternMaterialToMaterial()
{
	if (!m_extern_material) return;

	m_material.SetAmbient(m_extern_material->GetAmbientXM());
	m_material.SetDiffuse(m_extern_material->GetDiffuseXM());
	m_material.SetSpecular(m_extern_material->GetSpecularXM());
	m_material.SetReflect(m_extern_material->GetReflectXM());
	m_material.SetDiffuseMap(m_extern_material->GetDiffuseMap());
	m_material.SetSpecularMap(m_extern_material->GetSpecularMap());
}