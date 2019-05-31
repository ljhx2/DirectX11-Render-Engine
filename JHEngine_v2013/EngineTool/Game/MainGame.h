#pragma once

#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_

#include <GameObject\GameObjectMgr.h>
#include <GameObject\Message\MessageMgr.h>
#include <Scene\SceneMgr.h>

#include <Resource\DebugTexEffect.h>

class CMainGame
{
public:
	bool			Setup();
	void			Update(float deltaTime);
	void			ShadowRender();
	void			Render();
	void			Destroy();

public:
	CMainGame(wxPanel* parnet);
	~CMainGame();


protected:
	wxPanel*		m_pParent;

	
};

#endif // !_MAIN_GAME_H_