#include "..\Common.h"
#include "Mesh.h"

#include "ResourceMgr.h"
#include "..\Core\gDeviceManager.h"

CMesh::CMesh(const std::wstring& id)
	: cObject(), m_id(id), m_vertexLayout(NULL)
{
	XMMATRIX i = XMMatrixIdentity();
	XMStoreFloat4x4(&m_globalInverseMeshTransform, i);
}


CMesh::~CMesh()
{
	if (m_vertexLayout) m_vertexLayout->Release();
	g_pResouceMgr->EraseMesh(m_id);
}

bool CMesh::CreateVertexBuffer(void* vertices, UINT ByteWidth)
{
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = ByteWidth;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;

	if (FAILED(g_pDeviceMgr->GetDevice()->CreateBuffer(&vbd, &vinitData, &m_vertexBuffer)))
	{
		return false;
	}

	return true;
}

bool CMesh::CreateIndexBuffer(void* indices, UINT ByteWidth)
{
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = ByteWidth;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;

	if (FAILED(g_pDeviceMgr->GetDevice()->CreateBuffer(&ibd, &iinitData, &m_indexBuffer)))
	{
		return false;
	}

	return true;
}

bool CMesh::CreateLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDesc, UINT numElements, ID3DX11EffectTechnique* effectTech, UINT passIndex)
{
	D3DX11_PASS_DESC passDesc;
	effectTech->GetPassByIndex(passIndex)->GetDesc(&passDesc);
	if (FAILED(g_pDeviceMgr->GetDevice()->CreateInputLayout(pInputElementDesc, numElements, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &m_vertexLayout)))
	{
		return false;
	}

	return true;
	
}