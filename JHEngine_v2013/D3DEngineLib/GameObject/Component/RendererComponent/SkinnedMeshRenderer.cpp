#include "SkinnedMeshRenderer.h"

#include "..\..\GameObject.h"
#include "..\..\..\Core\gDeviceManager.h"
#include "..\CameraComponent\CameraManager.h"
#include "..\..\..\Core\MathHelper.h"

#include "..\..\..\Core\ShadowManager.h"

ImplRTTI(CSkinnedMeshRenderer, CRenderComponent);

CSkinnedMeshRenderer::CSkinnedMeshRenderer(const COMPONENT_ID_T id, CGameObject* owner)
	: CRenderComponent(id, owner)
{
	//m_receiveShadow = false;
}


CSkinnedMeshRenderer::~CSkinnedMeshRenderer()
{
}

bool CSkinnedMeshRenderer::Setup()
{
	return CRenderComponent::Setup();
}

bool CSkinnedMeshRenderer::Update(float deltaTime)
{
	return true;
}

bool CSkinnedMeshRenderer::HandleMessage(const CMessage& msg)
{
	return CRenderComponent::HandleMessage(msg);
}


void CSkinnedMeshRenderer::BuildShadowMap(CXMMATRIX matWorld)
{
	if (!m_castShadow) return;

	if (m_mesh->GetMeshType() != MESH_TYPE_SKINNED)
	{
		CRenderComponent::BuildShadowMap(matWorld);
		return;
	}

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

	ID3DX11EffectTechnique* tech = buildEffect->GetBuildShadowMapSkinnedTech();
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		CGameObject* parent = m_pOwner->GetParent();
		if (parent)
		{
			CAnimComponent* animComp = parent->GetComponent<CAnimComponent>();
			if (animComp)
			{
				int finalTransformsCount = animComp->GetFinalTransforms().size();
				std::vector<XMFLOAT4X4>& temp = animComp->GetFinalTransforms();

				buildEffect->SetBoneTransforms(&(temp[0]), finalTransformsCount);
				//m_effect->SetBoneTransformsIdentity();

			}
			else
			{
				buildEffect->SetBoneTransformsIdentity();
			}
		}
		else
		{
			buildEffect->SetBoneTransformsIdentity();
		}

		buildEffect->SetWorldViewProj(worldViewProj);
		buildEffect->SetTexTransform(texTransform);

		g_pDeviceMgr->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		g_pDeviceMgr->GetDeviceContext()->IASetIndexBuffer(m_mesh->GetIndexBuffer(), m_mesh->GetIndexFormat(), 0);

		tech->GetPassByIndex(p)->Apply(0, g_pDeviceMgr->GetDeviceContext());
		g_pDeviceMgr->GetDeviceContext()->DrawIndexed(m_mesh->GetIndexCount(), 0, 0);
	}
}


void CSkinnedMeshRenderer::Render(CXMMATRIX matWorld)
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

	if (m_mesh->GetMeshType() != MESH_TYPE_SKINNED)
	{
		CRenderComponent::Render(matWorld);
		return;
	}


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

	ID3DX11EffectTechnique* tech = m_effect->GetSkinnedTech();
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		CGameObject* parent = m_pOwner->GetParent();
		if (parent)
		{
			CAnimComponent* animComp = parent->GetComponent<CAnimComponent>();
			if (animComp)
			{
				int finalTransformsCount = animComp->GetFinalTransforms().size();
				std::vector<XMFLOAT4X4>& temp = animComp->GetFinalTransforms();
				
				m_effect->SetBoneTransforms(&(temp[0]), finalTransformsCount);
				//m_effect->SetBoneTransformsIdentity();

			}
			else
			{
				m_effect->SetBoneTransformsIdentity();
			}
		}
		else
		{
			m_effect->SetBoneTransformsIdentity();
		}

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