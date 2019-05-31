#include "..\Common.h"
#include "Grid.h"

#include "..\Core\gDeviceManager.h"
#include "..\Resource\gFXManager.h"

#include "Scene.h"
#include "..\GameObject\Component\CameraComponent\CameraComponent.h"

CGrid::CGrid(CScene* ownerScene)
	: m_isDisable(true), m_mesh(NULL), m_ownerScene(ownerScene)
{
}


CGrid::~CGrid()
{
}

void CGrid::Setup(float fGap, int nNumHalf)
{
	MakeVertices(fGap, nNumHalf);
	MakeEffect();
	MakeMesh();
}

void CGrid::Render()
{
	if (!m_isDisable) return;

	g_pDeviceMgr->GetDeviceContext()->IASetInputLayout(m_mesh->GetVertexLayout());
	g_pDeviceMgr->GetDeviceContext()->IASetPrimitiveTopology(m_mesh->GetPrimitiveTopology());

	ID3D11Buffer* vertexBuffer = m_mesh->GetVertexBuffer();
	UINT stride = m_mesh->GetVertexStride();
	UINT offset = m_mesh->GetVertexOffset();
	g_pDeviceMgr->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	//view행렬과 proj행렬을 카메라에서 구해옴
	CCameraComponent* camera = m_ownerScene->GetMainCamera();

	XMMATRIX world = XMMatrixIdentity();
	XMMATRIX viewProj = camera->GetViewProjMatrix();
	XMMATRIX worldViewProj = world * viewProj;

	m_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	D3DX11_TECHNIQUE_DESC techDesc;
	m_tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_tech->GetPassByIndex(p)->Apply(0, g_pDeviceMgr->GetDeviceContext());

		g_pDeviceMgr->GetDeviceContext()->Draw(m_mesh->GetVertexCount(), 0);
	}
}

void CGrid::MakeVertices(float fGap, int nNumHalf)
{
	fGap /= 2.0f;

	nNumHalf += (nNumHalf % 2);

	m_nNumHalf = nNumHalf;

	int nLine = nNumHalf * 2;

	float fMinusX = -nNumHalf * fGap;
	float fPlusX = nNumHalf * fGap;
	for (int i = 0; i < nLine + 1; i += 2)
	{
		float fPosZ = (-nNumHalf + i) * fGap;

		XMFLOAT4 c;
		if (i == nNumHalf)
			c = (const float*)&Colors::Red;
		else if ((i - nNumHalf) % 5 == 0)
			c = (const float*)&Colors::White;
		else
			c = (const float*)&Colors::Gray;

		Vertex_PC v;
		v.color = c;
		v.pos = XMFLOAT3(fMinusX, 0.0f, fPosZ);
		m_LineVertex.push_back(v);

		v.pos = XMFLOAT3(fPlusX, 0.0f, fPosZ);
		m_LineVertex.push_back(v);
	}

	float fMinusZ = -nNumHalf * fGap;
	float fPlusZ = nNumHalf * fGap;
	for (int i = 0; i < nLine + 1; i += 2)
	{
		float fPosX = (-nNumHalf + i) * fGap;

		XMFLOAT4 c;
		if (i == nNumHalf)
			c = (const float*)&Colors::Blue;
		else if ((i - nNumHalf) % 5 == 0)
			c = (const float*)&Colors::White;
		else
			c = (const float*)&Colors::Gray;

		Vertex_PC v;
		v.color = c;
		v.pos = XMFLOAT3(fPosX, 0.0f, fMinusZ);
		m_LineVertex.push_back(v);

		v.pos = XMFLOAT3(fPosX, 0.0f, fPlusZ);
		m_LineVertex.push_back(v);
	}

	Vertex_PC v;
	v.pos = XMFLOAT3(0.0f, -nNumHalf * fGap, 0.0f);
	v.color = (const float*)&Colors::Green;
	m_LineVertex.push_back(v);

	v.pos = XMFLOAT3(0.0f, nNumHalf * fGap, 0.0f);
	m_LineVertex.push_back(v);
}

void CGrid::MakeEffect()
{
	m_fx = g_pFXMgr->GetFX(L"FX/color.fx");
	m_tech = m_fx->GetTechniqueByName("ColorTech");
	m_fxWorldViewProj = m_fx->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void CGrid::MakeMesh()
{
	m_mesh = new CMesh(L"Grid");

	m_mesh->SetVertexCount(m_LineVertex.size());
	m_mesh->SetIndexCount(0U);
	m_mesh->SetFaceCount(0U);
	m_mesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_mesh->SetVertexStride(sizeof(Vertex_PC));
	m_mesh->SetVertexOffset(0U);
	
	if (m_mesh->CreateVertexBuffer(&m_LineVertex[0], sizeof(Vertex_PC) * m_LineVertex.size()) == false)
	{
		SAFE_DELETE(m_mesh);
		assert(!"CreateGridMesh Failed");
		return;
	}

	if (m_mesh->CreateLayout(vertexPCLayout, 2, m_tech, 0) == false)
	{
		SAFE_DELETE(m_mesh);
		assert(!"CreateGridLayout Failed");
		return;
	}

}