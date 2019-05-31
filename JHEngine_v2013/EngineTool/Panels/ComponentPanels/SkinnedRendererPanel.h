#pragma once

#ifndef _SKINNED_RENDERER_PANEL_H_
#define _SKINNED_RENDERER_PANEL_H_

#include "RendererPanel.h"

#include <GameObject\Component\RendererComponent\SkinnedMeshRenderer.h>

class CSkinnedRendererPanel : public CRendererPanel
{
public:
	CSkinnedRendererPanel(wxWindow* parent);
	virtual ~CSkinnedRendererPanel();
};

#endif // !_SKINNED_RENDERER_PANEL_H_