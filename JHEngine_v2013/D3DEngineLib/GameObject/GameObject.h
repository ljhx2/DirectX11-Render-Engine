#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <unordered_map>

#include "Component\Component.h"
#include "Component\TransformComponent.h"


const UINT GAMEOBJ_UID_ALL = 0U;

typedef UINT												GAMEOBJ_UID_T;
typedef std::wstring										GAMEOBJ_ID_T;
typedef std::unordered_map<COMPONENT_ID_T, IComponent*>		COMPONENT_MAP_T;


class CScene;

class CGameObject
{
public:
	bool		Setup();
	void		Update(float deltaTime);
	void		ShadowBuild();
	void		Render();

	bool		HandleMessage(const CMessage& msg);

public:
	template<typename T> T*			AddComponent();
	template<typename T> T*			GetComponent() const;
	CTransformComponent*			GetTransform() { return m_transformComponent; }

	bool							AddChild(CGameObject* child);
	bool							SubChild(CGameObject* child);
	CGameObject*					GetChild(const GAMEOBJ_ID_T& id);
	int								GetChildCount() { return m_children.size(); }
	CGameObject*					GetChild(int index);

	void							ClearAllComponents();
	void							ClearAllChild();

public:
	inline const GAMEOBJ_UID_T&		GetUID() const					{ return m_UID; }
	inline void						SetUID(GAMEOBJ_UID_T uid)		{ m_UID = uid; }

	inline const GAMEOBJ_ID_T&		GetID() const					{ return m_ID; }
	inline void						SetID(const GAMEOBJ_ID_T id)	{ m_ID.assign(id); }

	inline bool						GetIsDisable() const			{ return m_isDisable; }
	inline void						SetIsDisable(bool isDisable)	{ m_isDisable = isDisable; }

	inline CGameObject*				GetParent() const				{ return m_parent; }
	inline void						SetParent(CGameObject* parent)	{ m_parent = parent; }

	inline CScene*					GetOwnerScene() const			{ return m_ownerScene; }
	inline void						SetOwnerScene(CScene* scene)	{ m_ownerScene = scene; }
public:
	CGameObject(const GAMEOBJ_ID_T id);
	virtual ~CGameObject();

private:
	GAMEOBJ_UID_T			m_UID;
	GAMEOBJ_ID_T			m_ID;

	bool					m_isDisable;

	COMPONENT_MAP_T			m_components;

	CGameObject*			m_parent;
	std::list<CGameObject*>	m_children;

	CTransformComponent*	m_transformComponent;

	CScene*					m_ownerScene;

};

template<typename T>
T* CGameObject::AddComponent()
{
	//컴포넌트 ID는 클래스 이름
	COMPONENT_ID_T compID = T::ms_RTTI.GetClassNameRTTI();

	if (m_components.find(compID) != m_components.end())
	{
		assert(!"AddComponent error");
		return NULL;
	}

	//TODO : 같은 familID가 없는지 검사

	T* comp = new T(compID, this);
	//comp->Setup();

	m_components.insert(std::make_pair(compID, comp));

	return comp;
}

template<typename T>
T* CGameObject::GetComponent() const
{
	COMPONENT_ID_T compID = T::ms_RTTI.GetClassNameRTTI();

	auto iter = m_components.find(compID);
	if (iter != m_components.end())
	{
		return static_cast<T*>(iter->second);
	}
	return NULL;
	//COMPONENT_MAP_T::iterator comIter;
	//for (comIter = m_components.begin(); comIter != m_components.end(); ++comIter)
	//{
	//	if (IsKindOfClass(T, comIter->second))
	//	{
	//		return static_cast<T*>(comIter->second);
	//	}
	//}
	//
	//return NULL;
}

#endif	//_GAMEOBJECT_H_