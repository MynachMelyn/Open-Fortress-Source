//========= Copyright � 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#ifndef TF_TEAMMENU_H
#define TF_TEAMMENU_H
#ifdef _WIN32
#pragma once
#endif

#include "tf_controls.h"
#include <teammenu.h>
#include "basemodelpanel.h"

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CTFTeamButton : public CExButton
{
private:
	DECLARE_CLASS_SIMPLE( CTFTeamButton, CExButton );

public:
	CTFTeamButton( vgui::Panel *parent, const char *panelName );

	void ApplySettings( KeyValues *inResourceData );
	void ApplySchemeSettings( vgui::IScheme *pScheme );

	void OnCursorExited();
	void OnCursorEntered();

	void OnTick( void );

	void SetDefaultAnimation( const char *pszName );

private:
	bool IsTeamFull();
	void SendAnimation( const char *pszAnimation );
	void SetMouseEnteredState( bool state );

private:
	char	m_szModelPanel[64];		// the panel we'll send messages to
	int		m_iTeam;				// the team we're associated with (if any)

	float	m_flHoverTimeToWait;	// length of time to wait before reporting a "hover" message (-1 = no hover)
	float	m_flHoverTime;			// when should a "hover" message be sent?
	bool	m_bMouseEntered;		// used to track when the mouse is over a button
	bool	m_bTeamDisabled;		// used to keep track of whether our team is a valid team for selection
};

//-----------------------------------------------------------------------------
// Purpose: Displays the team menu
//-----------------------------------------------------------------------------
class CTFTeamMenu : public CTeamMenu
{
private:
	DECLARE_CLASS_SIMPLE( CTFTeamMenu, CTeamMenu );
		
public:
	CTFTeamMenu( IViewPort *pViewPort );
	~CTFTeamMenu();

	void Update();
	void ShowPanel( bool bShow );

#ifdef _X360
	CON_COMMAND_MEMBER_F( CTFTeamMenu, "join_team", Join_Team, "Send a jointeam command", 0 );
#endif


	bool IsBlueTeamDisabled(){ return m_bBlueDisabled; }
	bool IsRedTeamDisabled(){ return m_bRedDisabled; }

protected:
	virtual void ApplySchemeSettings(vgui::IScheme *pScheme);
	virtual void OnKeyCodePressed( vgui::KeyCode code );

	// command callbacks
	virtual void OnCommand( const char *command );

	virtual void LoadMapPage( const char *mapName );

	virtual void OnTick( void );

private:

	CTFTeamButton	*m_pBlueTeamButton;
	CTFTeamButton	*m_pRedTeamButton;
	CTFTeamButton	*m_pMercenaryTeamButton;
	CTFTeamButton	*m_pAutoTeamButton;
	CTFTeamButton	*m_pSpecTeamButton;
	CExLabel		*m_pSpecLabel;

#ifdef _X360
	CTFFooter		*m_pFooter;
#else
	CExButton		*m_pCancelButton;
#endif

	bool m_bRedDisabled;
	bool m_bBlueDisabled;
	bool m_bMercenaryDisabled;

private:
	enum { NUM_TEAMS = 4 };

	ButtonCode_t m_iTeamMenuKey;
};

//-----------------------------------------------------------------------------
// Purpose: Displays the DM team menu
//-----------------------------------------------------------------------------
class CTFDMTeamMenu : public CTeamMenu
{
private:
	DECLARE_CLASS_SIMPLE(CTFDMTeamMenu, CTeamMenu);

public:
	CTFDMTeamMenu(IViewPort *pViewPort);
	~CTFDMTeamMenu();

	virtual const char *GetName(void) { return PANEL_DMTEAMSELECT; }
	void Update();
	void ShowPanel(bool bShow);
	const char *GetGamemodeMessage(void);
	int	GetGamemodeSkin(void);
protected:
	virtual void ApplySchemeSettings(vgui::IScheme *pScheme);
	virtual void OnKeyCodePressed(vgui::KeyCode code);

	// command callbacks
	virtual void OnCommand(const char *command);

	virtual void LoadMapPage(const char *mapName);

	virtual void OnTick(void);

private:

	CTFTeamButton	*m_pAutoTeamButton;
	CTFTeamButton	*m_pSpecTeamButton;
	CExLabel		*m_pSpecLabel;
	CExButton		*m_pCancelButton;
	
	CModelPanel		*m_pBackgroundModel;


private:
	enum { NUM_TEAMS = 3 };

	ButtonCode_t m_iTeamMenuKey;
};

#endif // TF_TEAMMENU_H
