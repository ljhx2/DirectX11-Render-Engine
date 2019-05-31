#include "LightComponent.h"


ImplRTTI(CLightComponent, IComponent);

CLightComponent::CLightComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: IComponent(id, owner)
{
}


CLightComponent::~CLightComponent()
{
}
