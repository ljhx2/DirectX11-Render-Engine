#include "..\Common.h"
#include "GameObject.h"

#include "GameObjectMgr.h"

#include "Component\RendererComponent\RenderComponent.h"
#include "Component\RendererComponent\SkinnedMeshRenderer.h"
#include "..\Scene\Scene.h"

CGameObject::CGameObject(const GAMEOBJ_ID_T id)
	: m_UID(0U), m_ID(id)
	, m_isDisable(false)
	, m_parent(NULL), m_ownerScene(NULL)
{
	//모든 GameObject는 기본적으로 transformComponent를 가진다.
	AddComponent<CTransformComponent>();
	m_transformComponent = GetComponent<CTransformComponent>();

	m_UID = g_pGameObjectMgr->GenUID();
	g_pGameObjectMgr->AddWaitingObject(this);

	m_children.clear();
	
}


CGameObject::~CGameObject()
{
	if (m_parent)
	{
		m_parent->SubChild(this);
	}
	ClearAllChild();
	ClearAllComponents();
	
	
	
	g_pGameObjectMgr->EraseObjct(this);
}


bool CGameObject::Setup()
{
	COMPONENT_MAP_T::iterator comIter;
	for (comIter = m_components.begin(); comIter != m_components.end(); ++comIter)
	{
		if (!comIter->second->Setup())
		{
			return false;
		}
	}

	return true;
}

void CGameObject::Update(float deltaTime)
{
	if (m_isDisable)
	{
		return;
	}

	COMPONENT_MAP_T::iterator comIter;
	for (comIter = m_components.begin(); comIter != m_components.end(); ++comIter)
	{
		comIter->second->Update(deltaTime);
	}

	std::list<CGameObject*>::iterator childIter;
	for (childIter = m_children.begin(); childIter != m_children.end(); ++childIter)
	{
		(*childIter)->Update(deltaTime);
	}
	
}

void CGameObject::ShadowBuild()
{
	if (m_isDisable)
	{
		return;
	}

	COMPONENT_ID_T compID = CRenderComponent::ms_RTTI.GetClassNameRTTI();
	COMPONENT_MAP_T::iterator comIter = m_components.find(compID);
	if (comIter != m_components.end())
	{
		CRenderComponent* renderComp = static_cast<CRenderComponent*>(comIter->second);
		renderComp->BuildShadowMap(m_transformComponent->GetWorldMatrix());
	}
	COMPONENT_ID_T compID2 = CSkinnedMeshRenderer::ms_RTTI.GetClassNameRTTI();
	COMPONENT_MAP_T::iterator comIter2 = m_components.find(compID2);
	if (comIter2 != m_components.end())
	{
		CSkinnedMeshRenderer* renderComp = static_cast<CSkinnedMeshRenderer*>(comIter2->second);
		renderComp->BuildShadowMap(m_transformComponent->GetWorldMatrix());
	}



	std::list<CGameObject*>::iterator childIter;
	for (childIter = m_children.begin(); childIter != m_children.end(); ++childIter)
	{
		(*childIter)->ShadowBuild();
	}
}

void CGameObject::Render()
{
	if (m_isDisable)
	{
		return;
	}


	COMPONENT_ID_T compID = CRenderComponent::ms_RTTI.GetClassNameRTTI();
	COMPONENT_MAP_T::iterator comIter = m_components.find(compID);
	if (comIter != m_components.end())
	{
		CRenderComponent* renderComp = static_cast<CRenderComponent*>(comIter->second);
		renderComp->Render(m_transformComponent->GetWorldMatrix());
	}
	COMPONENT_ID_T compID2 = CSkinnedMeshRenderer::ms_RTTI.GetClassNameRTTI();
	COMPONENT_MAP_T::iterator comIter2 = m_components.find(compID2);
	if (comIter2 != m_components.end())
	{
		CSkinnedMeshRenderer* renderComp = static_cast<CSkinnedMeshRenderer*>(comIter2->second);
		renderComp->Render(m_transformComponent->GetWorldMatrix());
	}

	std::list<CGameObject*>::iterator childIter;
	for (childIter = m_children.begin(); childIter != m_children.end(); ++childIter)
	{
		(*childIter)->Render();
	}
}

bool CGameObject::HandleMessage(const CMessage& msg)
{
	COMPONENT_MAP_T::iterator comIter;
	for (comIter = m_components.begin(); comIter != m_components.end(); ++comIter)
	{
		if (comIter->second->HandleMessage(msg))
		{
			return true;
		}
	}

	std::list<CGameObject*>::iterator childIter;
	for (childIter = m_children.begin(); childIter != m_children.end(); ++childIter)
	{
		if ((*childIter)->HandleMessage(msg))
		{
			return true;
		}
	}

	return false;
}

bool CGameObject::AddChild(CGameObject* child)
{
	if (this == child)
	{
		return false;
	}

	std::list<CGameObject*>::iterator childIter;
	for (childIter = m_children.begin(); childIter != m_children.end(); ++childIter)
	{
		if ((*childIter) == child)
		{
			return false;
		}
	}

	m_children.push_back(child);
	child->SetParent(this);

	this->GetTransform()->AddChild(child->GetTransform());

	return true;
}

bool CGameObject::SubChild(CGameObject* child)
{
	if (this == child)
	{
		return false;
	}

	m_children.remove(child);
	child->SetParent(NULL);

	this->GetTransform()->DetechChild(child->GetTransform());

	return true;
}

CGameObject* CGameObject::GetChild(const GAMEOBJ_ID_T& id)
{

	std::list<CGameObject*>::iterator childIter;
	for (childIter = m_children.begin(); childIter != m_children.end(); ++childIter)
	{
		if ((*childIter)->GetID() == id)
		{
			return (*childIter);
		}

		CGameObject* child = (*childIter)->GetChild(id);
		if (child)
		{
			return child;
		}
	}

	return NULL;
}

CGameObject* CGameObject::GetChild(int index)
{
	if (index >= m_children.size() || index < 0) return NULL;

	std::list<CGameObject*>::iterator childIter = m_children.begin();
	for (int i = 0; i < index; ++i)
	{
		++childIter;
	}

	return (*childIter);
}

void CGameObject::ClearAllComponents()
{
	COMPONENT_MAP_T::iterator comIter;
	for (comIter = m_components.begin(); comIter != m_components.end(); )
	{
		delete (comIter->second);
		comIter = m_components.erase(comIter);
	}

	m_components.clear();
}

void CGameObject::ClearAllChild()
{ 
	std::list<CGameObject*>::iterator childIter;
	for (childIter = m_children.begin(); childIter != m_children.end(); )
	{
		CGameObject* child = (CGameObject*)(*childIter);
		childIter = m_children.erase(childIter);
		delete (child);
	}
	
	m_children.clear();
}


