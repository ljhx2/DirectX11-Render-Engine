#include "..\Common.h"
#include "gFXManager.h"

#include "..\Core\StringHelper.h"

gFXManager::gFXManager()
{
}


gFXManager::~gFXManager()
{
}

void gFXManager::Destroy()
{
	std::map<std::string, ID3DX11Effect*>::iterator iter;
	for (iter = m_mapEffect.begin(); iter != m_mapEffect.end(); ++iter)
	{
		SAFE_RELEASE(iter->second);
	}
	m_mapEffect.clear();
}

ID3DX11Effect * gFXManager::GetFX(const TCHAR * fileName)
{
#ifdef UNICODE
	std::wstring wstr(fileName);
	std::string str;
	CStringHelper::WStringToString(wstr, str);
#else
	std::string str(fileName);
#endif /* UNICODE */

	//맵에 없을 경우
	if (m_mapEffect.find(str) == m_mapEffect.end())
	{
		AddFX(fileName);
	}

	return m_mapEffect[str];
}

void gFXManager::AddFX(const TCHAR * fileName)
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined ( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DX11CompileFromFile(fileName, 0, 0, 0, "fx_5_0", shaderFlags,
		0, 0, &compiledShader, &compilationMsgs, 0);

	// compilationMsgs cn store errors or warnings.
	if (compilationMsgs != 0)
	{
		MessageBox(0, (TCHAR*)compilationMsgs->GetBufferPointer(), 0, 0);
		SAFE_RELEASE(compilationMsgs);
	}

	// Even if there are no compilationMsgs, check to make sure there were no other errors.
	if (FAILED(hr))
	{
		HR(hr);
		//DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
	}

	ID3DX11Effect* mFX;
	HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(),
		0, g_pDeviceMgr->GetDevice(), &mFX));

	// Done with compiled shader.
	SAFE_RELEASE(compiledShader);

#ifdef UNICODE
	std::wstring wstr(fileName);
	std::string str;
	CStringHelper::WStringToString(wstr, str);
#else
	std::string str(fileName);
#endif /* UNICODE */

	m_mapEffect[str] = mFX;
}
