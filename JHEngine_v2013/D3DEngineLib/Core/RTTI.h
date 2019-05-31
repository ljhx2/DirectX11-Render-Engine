#pragma once

#ifndef _RTTI_H_
#define _RTTI_H_

#include <string>

//최상위 클래스에 선언
#define DeclRootRTTI(classname) \
	public: \
		static const RTTI ms_RTTI;	\
		virtual const RTTI* GetRTTI() const { return &ms_RTTI; } \
		static bool IsKindOf(const RTTI* pRTTI, const classname *pObject) \
		{ \
			if(NULL == pObject) \
			{ \
				return false; \
			} \
			return pObject->IsKindOf(pRTTI); \
		} \
		bool IsKindOf(const RTTI* pRTTI) const \
		{ \
			const RTTI* pTmp = GetRTTI(); \
			while(NULL != pTmp) \
			{ \
				if (pTmp == pRTTI) \
				{ \
					return true; \
				} \
				pTmp = pTmp->GetBaseRTTI(); \
			} \
			return false; \
		}

//자식 클래스들에 선언
#define DeclRTTI \
	public: \
		static const RTTI ms_RTTI; \
		virtual const RTTI* GetRTTI() const { return &ms_RTTI; }

#define ImplRootRTTI(classname) \
	const RTTI classname::ms_RTTI(L#classname, NULL);

#define ImplRTTI(classname, baseclassname) \
	const RTTI classname::ms_RTTI(L#classname, &baseclassname::ms_RTTI);

#define IsKindOfClass(classname, pObject) \
	classname::IsKindOf(&classname::ms_RTTI, pObject)


class RTTI
{
public:
	inline const std::wstring& GetClassNameRTTI() const { return m_strClassName; }
	inline const RTTI* GetBaseRTTI() const { return m_pBaseRTTI; }

public:
	RTTI(const std::wstring strClassName, const RTTI* pBaseRTTI);
	~RTTI();

private:
	const std::wstring	m_strClassName;
	const RTTI*			m_pBaseRTTI;
};

#endif // _RTTI_H_