#include "..\Common.h"
#include "Effect.h"

#include "..\Core\StringHelper.h"
#include "ResourceMgr.h"

CEffect::CEffect()
	: cObject(), m_fx(NULL)
{
	XMFLOAT4X4 identity;
	XMStoreFloat4x4(&identity, XMMatrixIdentity());
	m_IdentityTransforms.resize(MAX_JOINT_COUNT, identity);
}


CEffect::~CEffect()
{
	SAFE_RELEASE(m_fx);
	g_pResouceMgr->EraseEffect(m_id);
}

void CEffect::SetDirLights(std::vector<CDirectionalLightComponent*>& vecDir)
{
	m_dirLightCnt->SetInt(vecDir.size());

	DirectionalLight dirL[3];
	for (int i = 0; i < vecDir.size(); i++)
	{
		dirL[i].Ambient = vecDir[i]->GetAmbient();
		dirL[i].Diffuse = vecDir[i]->GetDiffuse();
		dirL[i].Specular = vecDir[i]->GetSpecular();
		dirL[i].Direction = vecDir[i]->GetDirection();
		dirL[i].Pad = 0.0f;

	}

	m_dirLights->SetRawValue(dirL, 0, 3 * sizeof(DirectionalLight));
}


void CEffect::SetMaterial(CMaterial& mat)
{
	Material m;
	m.Ambient = mat.GetAmbient();
	m.Diffuse = mat.GetDiffuse();
	m.Reflect = mat.GetReflect();
	m.Specular = mat.GetSpecular();
	m_mat->SetRawValue(&m, 0, sizeof(Material));

	CTexture* diffuseMap = mat.GetDiffuseMap();
	if (diffuseMap)
	{
		m_useTexture->SetBool(true);
		m_diffuseMap->SetResource(diffuseMap->GetTexture());
	}
	else
	{
		m_useTexture->SetBool(false);
	}

	CTexture* normalMap = mat.GetNormalMap();
	if (normalMap)
	{
		m_useNormalMap->SetBool(true);
		m_normalMap->SetResource(normalMap->GetTexture());
	}
	else
	{
		m_useNormalMap->SetBool(false);
	}
}

bool CEffect::CreateFX(ID3D11Device* device, const std::wstring& fileName)
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined ( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DX11CompileFromFile(fileName.c_str(), 0, 0, 0, "fx_5_0", shaderFlags,
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
		return false;
	}

	HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(),
		0, g_pDeviceMgr->GetDevice(), &m_fx));

	// Done with compiled shader.
	SAFE_RELEASE(compiledShader);

	m_id.assign(fileName);

	return true;
}

void CEffect::CreateMember()
{
	m_tech = m_fx->GetTechniqueByName("Basic");
	m_skineedTech = m_fx->GetTechniqueByName("SkinBasic");

	m_worldViewProj			= m_fx->GetVariableByName("gWorldViewProj")->AsMatrix();
	m_world					= m_fx->GetVariableByName("gWorld")->AsMatrix();
	m_worldInvTranspose		= m_fx->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	m_texTransform			= m_fx->GetVariableByName("gTexTransform")->AsMatrix();
	m_eyePosW				= m_fx->GetVariableByName("gEyePosW")->AsVector();
	m_dirLights				= m_fx->GetVariableByName("gDirLights");
	m_mat					= m_fx->GetVariableByName("gMaterial");
	m_diffuseMap			= m_fx->GetVariableByName("gDiffuseMap")->AsShaderResource();
	m_normalMap				= m_fx->GetVariableByName("gNormalMap")->AsShaderResource();
	m_dirLightCnt			= m_fx->GetVariableByName("gDirLightCount")->AsScalar();
	m_useTexture			= m_fx->GetVariableByName("gUseTexure")->AsScalar();
	m_useNormalMap			= m_fx->GetVariableByName("gUseNormalMap")->AsScalar();
	m_receiveShadow			= m_fx->GetVariableByName("gReceiveShadow")->AsScalar();
	BoneTransforms			= m_fx->GetVariableByName("gBoneTransforms")->AsMatrix();
	ShadowTransform			= m_fx->GetVariableByName("gShadowTransform")->AsMatrix();
	m_shadowMap				= m_fx->GetVariableByName("gShadowMap")->AsShaderResource();
}