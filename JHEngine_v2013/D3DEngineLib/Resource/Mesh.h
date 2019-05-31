#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include <Windows.h>
#include <D3DX11.h>
#include <d3dx11effect.h>
#include <string>
#include <xnamath.h>

#include "Object.h"

enum eMeshType
{
	MESH_TYPE_STATIC,
	MESH_TYPE_SKINNED,
};

class CMesh : public cObject
{
public:
	bool							CreateVertexBuffer(void* vertices, UINT ByteWidth);
	bool							CreateIndexBuffer(void* indices, UINT ByteWidth);
	bool							CreateLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDesc, UINT numElements, ID3DX11EffectTechnique* effectTech, UINT passIndex);

	inline ID3D11Buffer*			GetVertexBuffer() const									{ return m_vertexBuffer; }
	//inline void						SetVertexBuffer(ID3D11Buffer *vertexBuffer)				{ m_vertexBuffer = vertexBuffer; }
	inline ID3D11InputLayout*		GetVertexLayout() const									{ return m_vertexLayout; }
	//inline void						SetVertexLayout(ID3D11InputLayout *vertexLayout)		{ m_vertexLayout = vertexLayout; }
	inline ID3D11Buffer*			GetIndexBuffer() const									{ return m_indexBuffer; }
	//inline void						SetIndexBuffer(ID3D11Buffer *indexBuffer)				{ m_indexBuffer = indexBuffer; }


public:
	const std::wstring&				GetID()	const	{ return m_id; }

	eMeshType						GetMeshType() const { return m_type; }
	void							SetMeshType(eMeshType type) { m_type = type; }
	
	inline UINT						GetVertexCount() const									{ return m_vertexCount; }
	inline void						SetVertexCount(UINT count)								{ m_vertexCount = count; }

	inline UINT						GetIndexCount() const									{ return m_indexCount; }
	inline void						SetIndexCount(UINT count)								{ m_indexCount = count; }

	inline UINT						GetFaceCount() const									{ return m_faceCount; }
	inline void						SetFaceCount(UINT count)								{ m_faceCount = count; }

	inline D3D_PRIMITIVE_TOPOLOGY	GetPrimitiveTopology() const							{ return m_primitiveTopology; }
	inline void						SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology)	{ m_primitiveTopology = topology; }

	inline UINT						GetVertexStride() const									{ return m_vertexStride; }
	inline void						SetVertexStride(UINT stride)							{ m_vertexStride = stride; }

	inline UINT						GetVertexOffset() const									{ return m_vertexOffset; }
	inline void						SetVertexOffset(UINT offset)							{ m_vertexOffset = offset; }

	inline DXGI_FORMAT				GetIndexFormat() const									{ return m_indexFormat; }
	inline void						SetIndexFormat(DXGI_FORMAT format)						{ m_indexFormat = format; }

	XMFLOAT4X4						GetGlobalInverseTransform() { return m_globalInverseMeshTransform; }
	void							SetGlobalInverseTransform(XMFLOAT4X4& matrix) { m_globalInverseMeshTransform = matrix; }

public:
	CMesh(const std::wstring& id);
	~CMesh();

private:
	std::wstring				m_id;

	eMeshType					m_type;

	D3D_PRIMITIVE_TOPOLOGY		m_primitiveTopology;

	UINT						m_vertexStride;
	UINT						m_vertexOffset;
	DXGI_FORMAT					m_indexFormat;

	UINT						m_vertexCount;
	UINT						m_indexCount;
	UINT						m_faceCount;

	ID3D11Buffer*				m_vertexBuffer;
	ID3D11Buffer*				m_indexBuffer;
	ID3D11InputLayout*			m_vertexLayout;

	//스킨드메시 랜더할때만 사용
	XMFLOAT4X4					m_globalInverseMeshTransform;

};

#endif // !_MESH_H_
