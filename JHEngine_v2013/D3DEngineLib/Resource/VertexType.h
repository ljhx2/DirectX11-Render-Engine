#pragma once

#ifndef _VERTEX_TYPE_H_
#define _VERTEX_TYPE_H_


struct Vertex_PC
{
	Vertex_PC()
		: pos(0.0f, 0.0f, 0.0f), color(0.0f, 0.0f, 0.0f, 0.0f) {}
	Vertex_PC(FLOAT x, FLOAT y, FLOAT z,
		FLOAT cr, FLOAT cg, FLOAT cb, FLOAT ca)
		: pos(x, y, z), color(cr, cg, cb, ca) {}
	Vertex_PC(XMFLOAT3 _pos, XMFLOAT4 _color)
		: pos(_pos), color(_color)	{}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};

const D3D11_INPUT_ELEMENT_DESC vertexPCLayout[] = 
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};




struct Vertex_PNT
{
	Vertex_PNT()
	{
		ZeroMemory(this, sizeof(Vertex_PNT));
	}
	Vertex_PNT(float px, float py, float pz,
		float nx, float ny, float nz,
		float tu, float tv)
	{
		Pos = XMFLOAT3(px, py, pz);
		Normal = XMFLOAT3(nx, ny, nz);
		Tex = XMFLOAT2(tu, tv);
	}
	
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 Tex;
};

const D3D11_INPUT_ELEMENT_DESC vertexPNTLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};


struct Vertex_PTNTan
{
	Vertex_PTNTan()
	{
		ZeroMemory(this, sizeof(Vertex_PTNTan));
	}
	Vertex_PTNTan(
		float px, float py, float pz,
		float nx, float ny, float nz,
		float tx, float ty, float tz,
		float u, float v)
		: Pos(px, py, pz), Normal(nx, ny, nz),
		Tangent(tx, ty, tz), Tex(u, v){}

	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
	XMFLOAT3 Normal;
	XMFLOAT3 Tangent;
};
const D3D11_INPUT_ELEMENT_DESC vertexPTNTanLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};



const INT MAX_VERTEX_WEIGHT = 3;
const INT MAX_VERTEX_JOINTINDEX = 4;
const INT MAX_JOINT_COUNT = 96;
struct Vertex_PTNTanWB
{
	Vertex_PTNTanWB()
	{
		ZeroMemory(this, sizeof(Vertex_PTNTanWB));
	}

	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
	XMFLOAT3 Normal;
	XMFLOAT3 Tangent;
	FLOAT	 Weights[3];
	BYTE	 JointIndices[4];
};

const D3D11_INPUT_ELEMENT_DESC vertexPTNTanWBLayout[] = 
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "WEIGHTS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "JOINTINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

#endif // !_VERTEX_TYPE_H_
