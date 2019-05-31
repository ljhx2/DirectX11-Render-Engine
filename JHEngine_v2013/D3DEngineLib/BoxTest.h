#pragma once
class BoxTest
{
public:
	BoxTest();
	~BoxTest();

	void Update(float dt);
	void Render();

private:
	void BuildGeometryBuffers();
	void BuildFX();
	void BuildVertexLayout();

private:

	ID3D11Buffer* mBoxVB;
	ID3D11Buffer* mBoxIB;

	ID3DX11Effect* mFX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;

	ID3D11InputLayout* mInputLayout;

	XMFLOAT4X4 mWorld;
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;

	float mTheta;
	float mPhi;
	float mRadius;


};

