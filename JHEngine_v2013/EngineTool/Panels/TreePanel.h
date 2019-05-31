#pragma once

#ifndef _TREE_PANEL_H_
#define _TREE_PANEL_H_

#include <wx/treectrl.h>

#include <GameObject\GameObject.h>

class cMainFrame;

class CTreeItem : public wxTreeItemData
{
public:
	CTreeItem(CGameObject* go) : m_GameObject(go) {}
	~CTreeItem() {}

	CGameObject*	GetGameObject() { return m_GameObject; }
	void			SetGameObject(CGameObject* go) { m_GameObject = go; }

private:
	CGameObject*		m_GameObject;
};


class CTreePanel : public wxTreeCtrl
{

public:
	//Event
	void OnBeginDrag(wxTreeEvent& event);
	void OnEndDrag(wxTreeEvent& event);
	void OnBeginLabelEdit(wxTreeEvent& event);
	void OnEndLabelEdit(wxTreeEvent& event);
	void OnDeleteItem(wxTreeEvent& event);
	void OnSelChanged(wxTreeEvent& event);	//클릭
	void OnItemActivated(wxTreeEvent& event); //더블클릭
	void OnItemRightClick(wxTreeEvent& event);
	void OnKeyDown(wxTreeEvent& event);

public:
	CTreePanel(cMainFrame* parent);
	virtual ~CTreePanel();

	void					AppendRoot(CGameObject* go);
	void					Append(CGameObject* go, wxTreeItemId parentID);

private:
	wxTreeItemId			m_rootID;
	wxTreeItemId			m_draggedItem;

	cMainFrame*				m_mainFrame;

	DECLARE_EVENT_TABLE()
};

#endif // !_TREE_PANEL_H_