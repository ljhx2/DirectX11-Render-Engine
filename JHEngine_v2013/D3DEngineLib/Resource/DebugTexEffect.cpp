#include "..\Common.h"
#include "DebugTexEffect.h"


CDebugTexEffect::CDebugTexEffect(ID3D11Device* device, const std::wstring& filename)
{

	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined ( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DX11CompileFromFile(filename.c_str(), 0, 0, 0, "fx_5_0", shaderFlags,
		0, 0, &compiledShader, &compilationMsgs, 0);

	// compilationMsgs cn store errors or warnings.
	//if (compilationMsgs != 0)
	//{
	//	MessageBox(0, (TCHAR*)compilationMsgs->GetBufferPointer(), 0, 0);
	//	SAFE_RELEASE(compilationMsgs);
	//
	//	return false;
	//}

	// Even if there are no compilationMsgs, check to make sure there were no other errors.
	if (FAILED(hr))
	{
		HR(hr);
		//DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
		assert(false && "Create ShadowBuildEffect Failed");
	}

	HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(),
		0, g_pDeviceMgr->GetDevice(), &mFX));

	// Done with compiled shader.
	SAFE_RELEASE(compiledShader);

	//////////////////////////////////////////


	ViewArgbTech = mFX->GetTechniqueByName("ViewArgbTech");
	ViewRedTech = mFX->GetTechniqueByName("ViewRedTech");
	ViewGreenTech = mFX->GetTechniqueByName("ViewGreenTech");
	ViewBlueTech = mFX->GetTechniqueByName("ViewBlueTech");
	ViewAlphaTech = mFX->GetTechniqueByName("ViewAlphaTech");

	WorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	Texture = mFX->GetVariableByName("gTexture")->AsShaderResource();
}


CDebugTexEffect::~CDebugTexEffect()
{
	SAFE_RELEASE(mFX);
}
