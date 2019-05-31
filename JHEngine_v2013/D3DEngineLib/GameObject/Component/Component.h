#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "..\..\Core\RTTI.h"
#include "..\Message\Message.h"

typedef std::wstring COMPONENT_ID_T;


class CGameObject;

class IComponent
{
	DeclRootRTTI(IComponent);

public:
	virtual bool		Setup() = 0;
	virtual bool		Update(float deltaTime) = 0;

	virtual bool		HandleMessage(const CMessage& msg) { return false; }

public:
	inline const COMPONENT_ID_T&	GetID() const							{ return m_ID; }
	inline void						SetID(const COMPONENT_ID_T id)			{ m_ID.assign(id); }

	inline const COMPONENT_ID_T&	GetFamilyID()							{ return m_familyID; }
	inline void						SetFamilyID(const COMPONENT_ID_T id)	{ m_familyID.assign(id); }

	inline CGameObject*				GetOwner() const						{ return m_pOwner; }
	inline void						SetOwner(CGameObject* owner)			{ m_pOwner = owner; }

public:
	IComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~IComponent();

protected:
	COMPONENT_ID_T	m_ID;
	COMPONENT_ID_T	m_familyID;
	
	CGameObject*	m_pOwner;
};

#endif	//_COMPONENT_H_