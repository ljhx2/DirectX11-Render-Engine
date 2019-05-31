#include "stdafx.h"
#include "..\stdafx.h"
#include "TreePanel.h"

#include <Scene\SceneMgr.h>


#include "..\Frame\cMainFrame.h"

BEGIN_EVENT_TABLE(CTreePanel, wxTreeCtrl)

	EVT_TREE_BEGIN_DRAG(-1, CTreePanel::OnBeginDrag)
	EVT_TREE_END_DRAG(-1, CTreePanel::OnEndDrag)
	EVT_TREE_BEGIN_LABEL_EDIT(-1, CTreePanel::OnBeginLabelEdit)
	EVT_TREE_END_LABEL_EDIT(-1, CTreePanel::OnEndLabelEdit)
	EVT_TREE_DELETE_ITEM(-1, CTreePanel::OnDeleteItem)
	EVT_TREE_SEL_CHANGED(-1, CTreePanel::OnSelChanged)
	EVT_TREE_ITEM_ACTIVATED(-1, CTreePanel::OnItemActivated)
	EVT_TREE_ITEM_RIGHT_CLICK(-1, CTreePanel::OnItemRightClick)
	EVT_TREE_KEY_DOWN(-1, CTreePanel::OnKeyDown)

END_EVENT_TABLE()



CTreePanel::CTreePanel(cMainFrame* parent)
	: wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 500), 
	wxTR_EDIT_LABELS | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_HIDE_ROOT | wxTR_SINGLE)
	, m_mainFrame(parent)
{
	m_rootID = AddRoot(wxString("Root"));

	m_draggedItem = (wxTreeItemId)0L;

	
}


CTreePanel::~CTreePanel()
{
	
}

void CTreePanel::AppendRoot(CGameObject* go)
{
	CTreeItem* treeItem = new CTreeItem(go);
	AppendItem(m_rootID, wxString(go->GetID().c_str()), -1, -1, treeItem);
	
	for (int i = 0; i < go->GetChildCount(); ++i)
	{
		Append(go->GetChild(i), treeItem->GetId());
	}
}

void CTreePanel::Append(CGameObject* go, wxTreeItemId parentID)
{
	CTreeItem* treeItem = new CTreeItem(go);
	AppendItem(parentID, wxString(go->GetID().c_str()), -1, -1, treeItem);

	for (int i = 0; i < go->GetChildCount(); ++i)
	{
		Append(go->GetChild(i), treeItem->GetId());
	}
}

//Event
void CTreePanel::OnBeginDrag(wxTreeEvent& event)
{
	m_draggedItem = event.GetItem();
	event.Allow();
}

void CTreePanel::OnEndDrag(wxTreeEvent& event)
{
	wxTreeItemId itemSrc = m_draggedItem, 
		itemDst = event.GetItem();
	m_draggedItem = (wxTreeItemId)0L;
	
	if (!itemDst.IsOk())
	{
		if (m_rootID == GetItemParent(itemSrc)) return;

		CTreeItem* item = (CTreeItem*)GetItemData(itemSrc);
		CGameObject* srcGo = item->GetGameObject();
		srcGo->GetParent()->SubChild(srcGo);
		srcGo->SetParent(NULL);


		AppendRoot(srcGo);
		Delete(itemSrc);
	}
	else
	{
		CTreeItem* item = (CTreeItem*)GetItemData(itemSrc);
		CGameObject* srcGo = item->GetGameObject();
		item = (CTreeItem*)GetItemData(itemDst);
		CGameObject* dstGo = item->GetGameObject();

		if (srcGo->GetParent())
		{
			srcGo->GetParent()->SubChild(srcGo);
		}
		srcGo->SetParent(dstGo);
		dstGo->AddChild(srcGo);

		Append(srcGo, itemDst);
		Delete(itemSrc);
	}

}

void CTreePanel::OnBeginLabelEdit(wxTreeEvent& event)
{

}

void CTreePanel::OnEndLabelEdit(wxTreeEvent& event)
{
	wxTreeItemId itemID = event.GetItem();
	if (!itemID.IsOk()) return;

	CTreeItem* item = (CTreeItem*)GetItemData(itemID);
	CGameObject* go = item->GetGameObject();

	wxString newID = event.GetLabel();

	wxLogMessage(wxT("GameObject Name [Change %s -> %s]"), go->GetID().c_str(), newID);

	go->SetID(newID.c_str().AsWChar());

	
}

void CTreePanel::OnDeleteItem(wxTreeEvent& event)
{

}

void CTreePanel::OnSelChanged(wxTreeEvent& event)
{
	wxTreeItemId itemID = event.GetItem();
	CTreeItem* item = (CTreeItem*)GetItemData(itemID);
	CGameObject* go = item->GetGameObject();

	m_mainFrame->SetSelectedGameObject(go);
	m_mainFrame->GetPropertyPanel()->ShowGameObjectProperty(go);
}

void CTreePanel::OnItemActivated(wxTreeEvent& event)
{
	wxTreeItemId itemID = event.GetItem();
	CTreeItem* item = (CTreeItem*)GetItemData(itemID);
	CGameObject* go = item->GetGameObject();
	XMVECTOR pos = go->GetTransform()->GetWorldPosition();
	XMFLOAT3 posF;
	XMStoreFloat3(&posF, pos);
	posF.z -= 20.0f;
	CCameraComponent* camera = g_pSceneMgr->GetCurrScene()->GetMainCamera();
	camera->SetPosition(posF.x, posF.y, posF.z);
	camera->SetRotation(0.0f, 0.0f, 0.0f);

}

void CTreePanel::OnItemRightClick(wxTreeEvent& event)
{
	
}

void CTreePanel::OnKeyDown(wxTreeEvent& event)
{
	if (!HasFocus()) return;

	if (event.GetKeyCode() == WXK_DELETE)
	{
		wxTreeItemId itemID = GetFocusedItem();
		if (itemID.IsOk())
		{
			CTreeItem* item = (CTreeItem*)GetItemData(itemID);
			CGameObject* go = item->GetGameObject();

			wxLogMessage(wxT("Delete %s"), go->GetID().c_str());
			
			SAFE_DELETE(go);
			Delete(itemID);

			m_mainFrame->SetSelectedGameObject(NULL);
			m_mainFrame->GetPropertyPanel()->AllComponentPanelHide();

			
		}
	}
}
//////// event end /////
