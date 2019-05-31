#pragma once

#ifndef _FX_MGR_H_
#define _FX_MGR_H_

#include "..\Core\Singleton.h"

#define g_pFXMgr gFXManager::GetInstance()

class gFXManager : public CSingleton<gFXManager>
{

public:
	
	virtual void Destroy();
	ID3DX11Effect* GetFX(const TCHAR* fileName);

private:
	void AddFX(const TCHAR* fileName);

public:
	gFXManager();
	virtual ~gFXManager();


private:
	std::map<std::string, ID3DX11Effect*> m_mapEffect;
};


#endif // !_FX_MGR_H_