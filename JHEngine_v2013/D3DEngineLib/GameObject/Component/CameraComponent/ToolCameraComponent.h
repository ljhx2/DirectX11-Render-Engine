#pragma once

#ifndef _TOOL_CAMERA_COMPONENT_H_
#define _TOOL_CAMERA_COMPONENT_H_


#include "CameraComponent.h"

class CToolCameraComponent : public CCameraComponent
{
	DeclRTTI;

public:
	virtual bool		Update(float deltaTime) override;

public:
	bool				GetIsControl()					{ return m_isControl; }
	void				SetIsControl(bool control)		{ m_isControl = control; }

	float				GetDelta()						{ return m_delta; }
	void				SetDelta(float delta)			{ m_delta = delta; }


public:
	CToolCameraComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CToolCameraComponent();

private:
	bool				m_isControl;
	float				m_delta;

};

#endif // !_TOOL_CAMERA_COMPONENT_H_
