#include "RTTI.h"



RTTI::RTTI(const std::wstring strClassName, const RTTI* pBaseRTTI)
	: m_strClassName(strClassName), m_pBaseRTTI(pBaseRTTI)
{
}


RTTI::~RTTI()
{
}
