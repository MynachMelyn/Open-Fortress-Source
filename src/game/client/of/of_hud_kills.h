//========= Copyright � 1996-2006, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef TF_HUD_KILLS_H
#define TF_HUD_KILLS_H
#ifdef _WIN32
#pragma once
#endif

#include "vgui_avatarimage.h"

using namespace vgui;

#define TF_MAX_FILENAME_LENGTH	128

//-----------------------------------------------------------------------------
// Purpose:  Displays weapon ammo data
//-----------------------------------------------------------------------------
class CTFHudKills : public CHudElement, public vgui::EditablePanel
{
	DECLARE_CLASS_SIMPLE( CTFHudKills, vgui::EditablePanel );

public:

	CTFHudKills( const char *pElementName );

	virtual void ApplySchemeSettings( vgui::IScheme *pScheme );
	virtual void Reset();

	virtual bool ShouldDraw( void );
	virtual void ShowBottom( bool bShow );
protected:

	virtual void OnThink();

private:
	
	void UpdateKillLabel( bool bKills );

private:

	bool							bBottomVisible;

	float							m_flNextThink;

	CHandle<C_BaseCombatWeapon>		m_hCurrentActiveWeapon;
	int								m_nKills;

	CAvatarImagePanel				*m_pAvatar;
	CAvatarImagePanel				*m_pLeadAvatar;

	CExLabel						*m_pKills;
	CExLabel						*m_pKillsShadow;
};

#endif	// TF_HUD_KILLS_H