#pragma once


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <assert.h>


// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here


#ifndef _INC_MMSYSTEM
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma message("Automatically linking with winmm.lib")    
#endif

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include <d3dx11effect.h>
#include <D3DX11.h>
#include <xnamath.h>
//#include <DxErr.h>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
//#include "Core\dxerr.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11d.lib")
#pragma comment(lib, "D3DCompiler.lib")
#if defined( DEBUG ) || defined ( _DEBUG )
#pragma comment(lib, "Effects11d.lib")
#else
#pragma comment(lib, "Effects11.lib")
#endif
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "assimp-vc120-mtd.lib")


// 싱글톤
#include "Core\Singleton.h"
#include "Core\gDeviceManager.h"


#define SAFE_ARR_DELETE(x) { if(x) { delete[] x; x = 0 }}
#define SAFE_DELETE(x) { if(x) { delete x; x = 0; }}
#define SAFE_RELEASE(x) { if(x) { x->Release(); x = 0; }}


#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)												\
	{														\
		HRESULT hr = (x);									\
		if(FAILED(hr))										\
		{													\
			LPWSTR output;                             		\
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |		\
				FORMAT_MESSAGE_IGNORE_INSERTS 	 |			\
				FORMAT_MESSAGE_ALLOCATE_BUFFER,				\
				NULL,										\
				hr,											\
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),	\
				(LPTSTR) &output,							\
				0,											\
				NULL);										\
			MessageBox(NULL, output, L"Error", MB_OK);		\
		}													\
	}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif

#endif




namespace Colors
{
	XMGLOBALCONST XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
	XMGLOBALCONST XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Gray = { 0.5f, 0.5f, 0.5f, 1.0f };
}


