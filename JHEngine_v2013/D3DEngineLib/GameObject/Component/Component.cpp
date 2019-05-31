#include "Component.h"

ImplRootRTTI(IComponent);

IComponent::IComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: m_ID(id), m_pOwner(owner)
{
	m_familyID.clear();
}


IComponent::~IComponent()
{
}
