//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef TFWINPANEL_H
#define TFWINPANEL_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/EditablePanel.h>
#include <game/client/iviewport.h>
#include <vgui/IScheme.h>
#include "hud.h"
#include "hudelement.h"
#include "basemodelpanel.h"
#include "tf_controls.h"

using namespace vgui;

class CTFWinPanel : public EditablePanel, public CHudElement
{
private:
	DECLARE_CLASS_SIMPLE(CTFWinPanel, EditablePanel);

public:
	CTFWinPanel(const char *pElementName);

	virtual void Reset();
	virtual void FireGameEvent(IGameEvent * event);
	virtual void OnThink();
	virtual bool ShouldDraw(void);
	virtual void SetVisible(bool state);

	virtual int GetRenderGroupPriority() { return 70; }

private:
	EditablePanel *m_pTeamScorePanel;

	float	m_flTimeUpdateTeamScore;
	int		m_iBlueTeamScore;
	int		m_iRedTeamScore;
	int		m_iMercenaryTeamScore;
};

class ExitCircle : public ImagePanel
{
	DECLARE_CLASS_SIMPLE(ExitCircle, ImagePanel);

public:
	ExitCircle(Panel *parent, const char *name, const char *cmd);
	virtual void OnMouseReleased(MouseCode code);

private:
	char command[32];
	Panel *m_pParent;
};

class CTFWinPanelDM : public EditablePanel, public CHudElement
{
private:
	DECLARE_CLASS_SIMPLE(CTFWinPanelDM, EditablePanel);

public:
	CTFWinPanelDM(const char *pElementName);

	virtual void Reset();
	virtual void FireGameEvent(IGameEvent *event);
	virtual bool ShouldDraw(void);
	virtual void SetVisible(bool state);
	virtual void OnCommand(const char *command);
	virtual bool HasInputElements(void) { return true; }
	virtual int GetRenderGroupPriority() { return 70; }

private:
	ExitCircle	  *m_XClose;
};

#endif //TFWINPANEL_H
