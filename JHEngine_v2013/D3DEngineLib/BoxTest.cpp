#include "Common.h"
#include "BoxTest.h"


struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

BoxTest::BoxTest()
	: mBoxVB(0), mBoxIB(0), mFX(0), mTech(0),
	mfxWorldViewProj(0), mInputLayout(0),
	mTheta(1.5f * 3.1415926535f), mPhi(0.25f * 3.1415926535f), mRadius(5.0f)
{
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mWorld, I);
	XMStoreFloat4x4(&mView, I);
	XMStoreFloat4x4(&mProj, I);

	BuildGeometryBuffers();
	BuildFX();
	BuildVertexLayout();
}


BoxTest::~BoxTest()
{
	SAFE_RELEASE(mBoxVB);
	SAFE_RELEASE(mBoxIB);
	//SAFE_RELEASE(mFX);	//매니저에서 지워줌
	SAFE_RELEASE(mInputLayout);
}

void BoxTest::Update(float dt)
{
	// Convert Spherical to Cartesian coordinates.
	float x = mRadius*sinf(mPhi)*cosf(mTheta);
	float z = mRadius*sinf(mPhi)*sinf(mTheta);
	float y = mRadius*cosf(mPhi);

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, V);

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*3.14f, 800.0f / 600.0f, 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);
}

void BoxTest::Render()
{
	g_pDeviceMgr->GetDeviceContext()->IASetInputLayout(mInputLayout);
	g_pDeviceMgr->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pDeviceMgr->GetDeviceContext()->IASetVertexBuffers(0, 1, &mBoxVB, &stride, &offset);
	g_pDeviceMgr->GetDeviceContext()->IASetIndexBuffer(mBoxIB, DXGI_FORMAT_R32_UINT, 0);

	XMMATRIX world = XMLoadFloat4x4(&mWorld);
	XMMATRIX view = XMLoadFloat4x4(&mView);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);
	XMMATRIX worldViewProj = world*view*proj;

	mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	D3DX11_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0, g_pDeviceMgr->GetDeviceContext());

		g_pDeviceMgr->GetDeviceContext()->DrawIndexed(36, 0, 0);
	}

}

void BoxTest::BuildGeometryBuffers()
{
	// Create vertex buffer
	Vertex vertices[] =
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

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * 8;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	HR(g_pDeviceMgr->GetDevice()->CreateBuffer(&vbd, &vinitData, &mBoxVB));
	


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

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 36;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HR(g_pDeviceMgr->GetDevice()->CreateBuffer(&ibd, &iinitData, &mBoxIB));
}

void BoxTest::BuildFX()
{
//	mFX = g_pFXMgr->GetFX(L"FX/color.fx");
	mTech = mFX->GetTechniqueByName("ColorTech");
	mfxWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void BoxTest::BuildVertexLayout()
{
	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	mTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(g_pDeviceMgr->GetDevice()->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &mInputLayout));
}
