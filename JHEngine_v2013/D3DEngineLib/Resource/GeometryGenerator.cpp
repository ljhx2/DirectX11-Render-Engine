#include "..\Common.h"
#include "GeometryGenerator.h"


#include "..\Core\gDeviceManager.h"
#include "gFXManager.h"
#include "ResourceMgr.h"

CGeometryGenerator::CGeometryGenerator()
{
}


CGeometryGenerator::~CGeometryGenerator()
{
}
/*
CMesh* CGeometryGenerator::CreateBox()
{
	CMesh* mesh = new CMesh(L"Box");

	// Create vertex buffer
	Vertex_PC vertices[] = 
	{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), (const float*)&Colors::White },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), (const float*)&Colors::Black },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), (const float*)&Colors::Red },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), (const float*)&Colors::Green },
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), (const float*)&Colors::Blue },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), (const float*)&Colors::Yellow },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), (const float*)&Colors::Cyan },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), (const float*)&Colors::Magenta }
	};
	// Create the index buffer
	UINT indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	mesh->SetVertexCount(8U);
	mesh->SetIndexCount(36U);
	mesh->SetFaceCount(12U);
	mesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mesh->SetVertexStride(sizeof(Vertex_PC));
	mesh->SetVertexOffset(0U);
	mesh->SetIndexFormat(DXGI_FORMAT_R32_UINT);

	if (mesh->CreateVertexBuffer(vertices, sizeof(Vertex_PC) * 8) == false
		|| mesh->CreateIndexBuffer(indices, sizeof(UINT) * 36) == false)
	{
		assert(!"CreateMesh Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	ID3DX11Effect* fx = g_pFXMgr->GetFX(L"FX/color.fx");
	ID3DX11EffectTechnique* tech = fx->GetTechniqueByName("ColorTech");
	if (mesh->CreateLayout(vertexPCLayout, 2, tech, 0) == false)
	{
		assert(!"CreateLayout Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	return mesh;

}
*/

CMesh* CGeometryGenerator::CreateBoxPNT()
{
	CMesh* mesh = new CMesh(L"BoxPNT");

	float width = 5.0f;
	float height = 5.0f;
	float depth = 5.0f;

	float w2 = 0.5f * width;
	float h2 = 0.5f * height;
	float d2 = 0.5f * depth;

	// Create vertex buffer
	Vertex_PNT v[24];

	//Fill in the front face vertex data
	v[0] = Vertex_PNT(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex_PNT(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex_PNT(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[3] = Vertex_PNT(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[4] = Vertex_PNT(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	v[5] = Vertex_PNT(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[6] = Vertex_PNT(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[7] = Vertex_PNT(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8]  = Vertex_PNT(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	v[9]  = Vertex_PNT(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[10] = Vertex_PNT(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	v[11] = Vertex_PNT(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[12] = Vertex_PNT(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	v[13] = Vertex_PNT(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	v[14] = Vertex_PNT(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	v[15] = Vertex_PNT(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
			
	// Fill in the left face vertex data.
	v[16] = Vertex_PNT(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[17] = Vertex_PNT(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[18] = Vertex_PNT(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[19] = Vertex_PNT(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			
	// Fill in the right face vertex data.
	v[20] = Vertex_PNT(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[21] = Vertex_PNT(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[22] = Vertex_PNT(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[23] = Vertex_PNT(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	
	
	// Create the index buffer
	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;


	mesh->SetVertexCount(24U);
	mesh->SetIndexCount(36U);
	mesh->SetFaceCount(12U);
	mesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mesh->SetVertexStride(sizeof(Vertex_PNT));
	mesh->SetVertexOffset(0U);
	mesh->SetIndexFormat(DXGI_FORMAT_R32_UINT);

	if (mesh->CreateVertexBuffer(v, sizeof(Vertex_PNT) * mesh->GetVertexCount()) == false
		|| mesh->CreateIndexBuffer(i, sizeof(UINT) * mesh->GetIndexCount()) == false)
	{
		assert(!"CreateMesh Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	ID3DX11EffectTechnique* tech = g_pResouceMgr->GetEffect(L"FX/Basic.fx")->GetTech();
	if (mesh->CreateLayout(vertexPNTLayout, 3, tech, 0) == false)
	{
		assert(!"CreateLayout Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	return mesh;

}

CMesh* CGeometryGenerator::CreateBox()
{
	CMesh* mesh = new CMesh(L"Box");

	float width = 5.0f;
	float height = 5.0f;
	float depth = 5.0f;

	float w2 = 0.5f * width;
	float h2 = 0.5f * height;
	float d2 = 0.5f * depth;

	// Create vertex buffer
	Vertex_PTNTan v[24];

	// Fill in the front face vertex data.
	v[0] = Vertex_PTNTan(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[1] = Vertex_PTNTan(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[2] = Vertex_PTNTan(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[3] = Vertex_PTNTan(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[4] = Vertex_PTNTan(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[5] = Vertex_PTNTan(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[6] = Vertex_PTNTan(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[7] = Vertex_PTNTan(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8] = Vertex_PTNTan(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[9] = Vertex_PTNTan(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[10] = Vertex_PTNTan(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[11] = Vertex_PTNTan(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[12] = Vertex_PTNTan(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[13] = Vertex_PTNTan(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[14] = Vertex_PTNTan(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[15] = Vertex_PTNTan(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = Vertex_PTNTan(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[17] = Vertex_PTNTan(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[18] = Vertex_PTNTan(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[19] = Vertex_PTNTan(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	v[20] = Vertex_PTNTan(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[21] = Vertex_PTNTan(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[22] = Vertex_PTNTan(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	v[23] = Vertex_PTNTan(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);



	// Create the index buffer
	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;


	mesh->SetVertexCount(24U);
	mesh->SetIndexCount(36U);
	mesh->SetFaceCount(12U);
	mesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mesh->SetVertexStride(sizeof(Vertex_PTNTan));
	mesh->SetVertexOffset(0U);
	mesh->SetIndexFormat(DXGI_FORMAT_R32_UINT);

	if (mesh->CreateVertexBuffer(v, sizeof(Vertex_PTNTan) * mesh->GetVertexCount()) == false
		|| mesh->CreateIndexBuffer(i, sizeof(UINT) * mesh->GetIndexCount()) == false)
	{
		assert(!"CreateMesh Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	ID3DX11EffectTechnique* tech = g_pResouceMgr->GetEffect(L"FX/Basic.fx")->GetTech();
	if (mesh->CreateLayout(vertexPTNTanLayout, 4, tech, 0) == false)
	{
		assert(!"CreateLayout Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	return mesh;

}

CMesh* CGeometryGenerator::CreateSphere()
{
	CMesh* mesh = new CMesh(L"Sphere");

	float radius = 10.0f;
	UINT sliceCount = 20U;
	UINT stackCount = 20U;


	std::vector<Vertex_PTNTan> vertices;
	std::vector<UINT> indices;


	Vertex_PTNTan topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	Vertex_PTNTan bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	vertices.push_back(topVertex);

	float phiStep = XM_PI / stackCount;
	float thetaStep = 2.0f*XM_PI / sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (UINT i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i*phiStep;

		// Vertices of ring.
		for (UINT j = 0; j <= sliceCount; ++j)
		{
			float theta = j*thetaStep;

			Vertex_PTNTan v;

			// spherical to cartesian
			v.Pos.x = radius*sinf(phi)*cosf(theta);
			v.Pos.y = radius*cosf(phi);
			v.Pos.z = radius*sinf(phi)*sinf(theta);

			// Partial derivative of P with respect to theta
			v.Tangent.x = -radius*sinf(phi)*sinf(theta);
			v.Tangent.y = 0.0f;
			v.Tangent.z = +radius*sinf(phi)*cosf(theta);

			XMVECTOR T = XMLoadFloat3(&v.Tangent);
			XMStoreFloat3(&v.Tangent, XMVector3Normalize(T));

			XMVECTOR p = XMLoadFloat3(&v.Pos);
			XMStoreFloat3(&v.Normal, XMVector3Normalize(p));

			v.Tex.x = theta / XM_2PI;
			v.Tex.y = phi / XM_PI;

			vertices.push_back(v);
		}
	}

	vertices.push_back(bottomVertex);

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for (UINT i = 1; i <= sliceCount; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	UINT baseIndex = 1;
	UINT ringVertexCount = sliceCount + 1;
	for (UINT i = 0; i < stackCount - 2; ++i)
	{
		for (UINT j = 0; j < sliceCount; ++j)
		{
			indices.push_back(baseIndex + i*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);

			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	UINT southPoleIndex = (UINT)vertices.size() - 1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < sliceCount; ++i)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}



	mesh->SetVertexCount(vertices.size());
	mesh->SetIndexCount(indices.size());
	mesh->SetFaceCount(indices.size() / 3);
	mesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mesh->SetVertexStride(sizeof(Vertex_PTNTan));
	mesh->SetVertexOffset(0U);
	mesh->SetIndexFormat(DXGI_FORMAT_R32_UINT);

	if (mesh->CreateVertexBuffer(&vertices[0], sizeof(Vertex_PTNTan) * mesh->GetVertexCount()) == false
		|| mesh->CreateIndexBuffer(&indices[0], sizeof(UINT) * mesh->GetIndexCount()) == false)
	{
		assert(!"CreateMesh Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	ID3DX11EffectTechnique* tech = g_pResouceMgr->GetEffect(L"FX/Basic.fx")->GetTech();
	if (mesh->CreateLayout(vertexPTNTanLayout, 4, tech, 0) == false)
	{
		assert(!"CreateLayout Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	return mesh;
}

CMesh* CGeometryGenerator::CreateCylinder()
{
	float bottomRadius = 10.0f;
	float topRadius = 10.0f;
	float height = 20.0f;
	UINT sliceCount = 20U;
	UINT stackCount = 20U;

	std::vector<Vertex_PTNTan> vertices;
	std::vector<UINT> indices;

	//
	// Build Stacks.
	// 

	float stackHeight = height / stackCount;

	// Amount to increment radius as we move up each stack level from bottom to top.
	float radiusStep = (topRadius - bottomRadius) / stackCount;

	UINT ringCount = stackCount + 1;

	// Compute vertices for each stack ring starting at the bottom and moving up.
	for (UINT i = 0; i < ringCount; ++i)
	{
		float y = -0.5f*height + i*stackHeight;
		float r = bottomRadius + i*radiusStep;

		// vertices of ring
		float dTheta = 2.0f*XM_PI / sliceCount;
		for (UINT j = 0; j <= sliceCount; ++j)
		{
			Vertex_PTNTan vertex;

			float c = cosf(j*dTheta);
			float s = sinf(j*dTheta);

			vertex.Pos = XMFLOAT3(r*c, y, r*s);

			vertex.Tex.x = (float)j / sliceCount;
			vertex.Tex.y = 1.0f - (float)i / stackCount;

			// Cylinder can be parameterized as follows, where we introduce v
			// parameter that goes in the same direction as the v tex-coord
			// so that the bitangent goes in the same direction as the v tex-coord.
			//   Let r0 be the bottom radius and let r1 be the top radius.
			//   y(v) = h - hv for v in [0,1].
			//   r(v) = r1 + (r0-r1)v
			//
			//   x(t, v) = r(v)*cos(t)
			//   y(t, v) = h - hv
			//   z(t, v) = r(v)*sin(t)
			// 
			//  dx/dt = -r(v)*sin(t)
			//  dy/dt = 0
			//  dz/dt = +r(v)*cos(t)
			//
			//  dx/dv = (r0-r1)*cos(t)
			//  dy/dv = -h
			//  dz/dv = (r0-r1)*sin(t)

			// This is unit length.
			vertex.Tangent = XMFLOAT3(-s, 0.0f, c);

			float dr = bottomRadius - topRadius;
			XMFLOAT3 bitangent(dr*c, -height, dr*s);

			XMVECTOR T = XMLoadFloat3(&vertex.Tangent);
			XMVECTOR B = XMLoadFloat3(&bitangent);
			XMVECTOR N = XMVector3Normalize(XMVector3Cross(T, B));
			XMStoreFloat3(&vertex.Normal, N);

			vertices.push_back(vertex);
		}
	}

	// Add one because we duplicate the first and last vertex per ring
	// since the texture coordinates are different.
	UINT ringVertexCount = sliceCount + 1;

	// Compute indices for each stack.
	for (UINT i = 0; i < stackCount; ++i)
	{
		for (UINT j = 0; j < sliceCount; ++j)
		{
			indices.push_back(i*ringVertexCount + j);
			indices.push_back((i + 1)*ringVertexCount + j);
			indices.push_back((i + 1)*ringVertexCount + j + 1);

			indices.push_back(i*ringVertexCount + j);
			indices.push_back((i + 1)*ringVertexCount + j + 1);
			indices.push_back(i*ringVertexCount + j + 1);
		}
	}

	BuildCylinderTopCap(bottomRadius, topRadius, height, sliceCount, stackCount, vertices, indices);
	BuildCylinderBottomCap(bottomRadius, topRadius, height, sliceCount, stackCount, vertices, indices);


	CMesh* mesh = new CMesh(L"Cylinder");

	mesh->SetVertexCount(vertices.size());
	mesh->SetIndexCount(indices.size());
	mesh->SetFaceCount(indices.size() / 3);
	mesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mesh->SetVertexStride(sizeof(Vertex_PTNTan));
	mesh->SetVertexOffset(0U);
	mesh->SetIndexFormat(DXGI_FORMAT_R32_UINT);

	if (mesh->CreateVertexBuffer(&vertices[0], sizeof(Vertex_PTNTan) * mesh->GetVertexCount()) == false
		|| mesh->CreateIndexBuffer(&indices[0], sizeof(UINT) * mesh->GetIndexCount()) == false)
	{
		assert(!"CreateMesh Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	ID3DX11EffectTechnique* tech = g_pResouceMgr->GetEffect(L"FX/Basic.fx")->GetTech();
	if (mesh->CreateLayout(vertexPTNTanLayout, 4, tech, 0) == false)
	{
		assert(!"CreateLayout Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	return mesh;

}


void CGeometryGenerator::BuildCylinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, std::vector<Vertex_PTNTan>& vertices, std::vector<UINT>& indices)
{
	UINT baseIndex = (UINT)vertices.size();

	float y = 0.5f*height;
	float dTheta = 2.0f*XM_PI / sliceCount;

	// Duplicate cap ring vertices because the texture coordinates and normals differ.
	for (UINT i = 0; i <= sliceCount; ++i)
	{
		float x = topRadius*cosf(i*dTheta);
		float z = topRadius*sinf(i*dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertices.push_back(Vertex_PTNTan(x, y, z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v));
	}

	// Cap center vertex.
	vertices.push_back(Vertex_PTNTan(0.0f, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f));

	// Index of center vertex.
	UINT centerIndex = (UINT)vertices.size() - 1;

	for (UINT i = 0; i < sliceCount; ++i)
	{
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i + 1);
		indices.push_back(baseIndex + i);
	}
}

void CGeometryGenerator::BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, std::vector<Vertex_PTNTan>& vertices, std::vector<UINT>& indices)
{
	// 
	// Build bottom cap.
	//

	UINT baseIndex = (UINT)vertices.size();
	float y = -0.5f*height;

	// vertices of ring
	float dTheta = 2.0f*XM_PI / sliceCount;
	for (UINT i = 0; i <= sliceCount; ++i)
	{
		float x = bottomRadius*cosf(i*dTheta);
		float z = bottomRadius*sinf(i*dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertices.push_back(Vertex_PTNTan(x, y, z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v));
	}

	// Cap center vertex.
	vertices.push_back(Vertex_PTNTan(0.0f, y, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f));

	// Cache the index of center vertex.
	UINT centerIndex = (UINT)vertices.size() - 1;

	for (UINT i = 0; i < sliceCount; ++i)
	{
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}
}

CMesh* CGeometryGenerator::CreatePlane()
{
	std::vector<Vertex_PTNTan> vertices;
	std::vector<UINT> indices;


	float width = 100.0f;
	float depth = 100.0f;
	UINT m = 10U;
	UINT n = 10U;


	UINT vertexCount = m*n;
	UINT faceCount = (m - 1)*(n - 1) * 2;

	//
	// Create the vertices.
	//

	float halfWidth = 0.5f*width;
	float halfDepth = 0.5f*depth;

	float dx = width / (n - 1);
	float dz = depth / (m - 1);

	float du = 1.0f / (n - 1);
	float dv = 1.0f / (m - 1);

	vertices.resize(vertexCount);
	for (UINT i = 0; i < m; ++i)
	{
		float z = halfDepth - i*dz;
		for (UINT j = 0; j < n; ++j)
		{
			float x = -halfWidth + j*dx;

			vertices[i*n + j].Pos = XMFLOAT3(x, 0.0f, z);
			vertices[i*n + j].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertices[i*n + j].Tangent = XMFLOAT3(1.0f, 0.0f, 0.0f);

			// Stretch texture over grid.
			vertices[i*n + j].Tex.x = j*du;
			vertices[i*n + j].Tex.y = i*dv;
		}
	}


	//
	// Create the indices.
	//

	indices.resize(faceCount * 3); // 3 indices per face

	// Iterate over each quad and compute indices.
	UINT k = 0;
	for (UINT i = 0; i < m - 1; ++i)
	{
		for (UINT j = 0; j < n - 1; ++j)
		{
			indices[k] = i*n + j;
			indices[k + 1] = i*n + j + 1;
			indices[k + 2] = (i + 1)*n + j;

			indices[k + 3] = (i + 1)*n + j;
			indices[k + 4] = i*n + j + 1;
			indices[k + 5] = (i + 1)*n + j + 1;

			k += 6; // next quad
		}
	}

	CMesh* mesh = new CMesh(L"Plane");

	mesh->SetVertexCount(vertices.size());
	mesh->SetIndexCount(indices.size());
	mesh->SetFaceCount(indices.size() / 3);
	mesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mesh->SetVertexStride(sizeof(Vertex_PTNTan));
	mesh->SetVertexOffset(0U);
	mesh->SetIndexFormat(DXGI_FORMAT_R32_UINT);

	if (mesh->CreateVertexBuffer(&vertices[0], sizeof(Vertex_PTNTan) * mesh->GetVertexCount()) == false
		|| mesh->CreateIndexBuffer(&indices[0], sizeof(UINT) * mesh->GetIndexCount()) == false)
	{
		assert(!"CreateMesh Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	ID3DX11EffectTechnique* tech = g_pResouceMgr->GetEffect(L"FX/Basic.fx")->GetTech();
	if (mesh->CreateLayout(vertexPTNTanLayout, 4, tech, 0) == false)
	{
		assert(!"CreateLayout Failed");
		SAFE_DELETE(mesh);
		return NULL;
	}

	return mesh;
}