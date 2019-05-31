#include "stdafx.h"
#include "..\..\stdafx.h"
#include "SkinnedRendererPanel.h"

#include <Core\StringHelper.h>

CSkinnedRendererPanel::CSkinnedRendererPanel(wxWindow* parent)
	: CRendererPanel(parent)
{
	m_sbSizer->GetStaticBox()->SetLabel(wxT("SkinnedMesh Renderer"));
}


CSkinnedRendererPanel::~CSkinnedRendererPanel()
{
}
