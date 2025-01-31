#ifndef _INCLUDED_NB_HEADER_FOOTER_H
#define _INCLUDED_NB_HEADER_FOOTER_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui/VGUI.h>
#include <vgui_controls/EditablePanel.h>

#include "video/ivideoservices.h"
#include "SoundEmitterSystem/isoundemittersystembase.h"

#define GAMEIU_MULTI_MOVIES

#include "avi/ibik.h"
#include "avi/iavi.h"

class HUDVideoPanel;
class CNB_Gradient_Bar;

enum NB_Title_Style
{
	NB_TITLE_BRIGHT,
	NB_TITLE_MEDIUM,
};

enum NB_Background_Style
{
	NB_BACKGROUND_DARK,
	NB_BACKGROUND_TRANSPARENT_BLUE,
	NB_BACKGROUND_BLUE,
	NB_BACKGROUND_TRANSPARENT_RED,
	NB_BACKGROUND_IMAGE,
	NB_BACKGROUND_NONE,
};

class CASW_Background_Movie
{
public:
	CASW_Background_Movie();
	~CASW_Background_Movie();

	void Update();
	void SetCurrentMovie( const char *szFilename );
	int SetTextureMaterial();
	IVideoMaterial* GetVideoMaterial()	{ return m_pVideoMaterial; }
	void ClearCurrentMovie();
	void SetEnabled( bool bEnabled ){ m_bEnabled = bEnabled; }
private:
	IVideoMaterial *m_pVideoMaterial;
	BIKMaterial_t m_nBIKMaterial;
	float m_flStartTime;
	int m_nTextureID;
	char m_szCurrentMovie[ MAX_PATH ];
	int m_nLastGameState;
	bool m_bEnabled;
public:
	float m_flU;
	float m_flV;
	int m_nPlaybackWidth;
	int m_nPlaybackHeight;
};

CASW_Background_Movie* ASWBackgroundMovie();

class CNB_Header_Footer : public vgui::EditablePanel
{
	DECLARE_CLASS_SIMPLE( CNB_Header_Footer, vgui::EditablePanel );
public:
	CNB_Header_Footer( vgui::Panel *parent, const char *name );
	virtual ~CNB_Header_Footer();
	
	virtual void ApplySchemeSettings( vgui::IScheme *pScheme );
	virtual void PerformLayout();
	virtual void OnThink();
	virtual void PaintBackground();
	void SetTitle( const char *pszTitle );
	void SetTitle( wchar_t *pwszTitle );
	void SetHeaderEnabled( bool bEnabled );
	void SetFooterEnabled( bool bEnabled );
	void SetTitleStyle( NB_Title_Style nTitleStyle );
	void SetBackgroundStyle( NB_Background_Style nBackgroundStyle );
	void SetMovieEnabled( bool bMovieEnabled );
	void SetGradientBarEnabled( bool bEnabled );
	void SetGradientBarPos( int nY, int nHeight );
	
	// == MANAGED_MEMBER_POINTERS_START: Do not edit by hand ==
	vgui::Panel	*m_pBackground;
	vgui::ImagePanel *m_pBackgroundImage;	
	vgui::Label	*m_pTitle;	
	vgui::Panel	*m_pTopBar;
	vgui::Panel	*m_pTopBarLine;	
	vgui::Panel	*m_pBottomBar;
	vgui::Panel	*m_pBottomBarLine;
	// == MANAGED_MEMBER_POINTERS_END ==
	HUDVideoPanel *m_pVideoPanel;
	CNB_Gradient_Bar *m_pGradientBar;

	bool m_bHeaderEnabled;
	bool m_bFooterEnabled;
	bool m_bMovieEnabled;
	bool m_bGradientBarEnabled;
	int m_nGradientBarY;
	int m_nGradientBarHeight;

	NB_Title_Style m_nTitleStyle;
	NB_Background_Style m_nBackgroundStyle;
};

class CNB_Gradient_Bar : public vgui::EditablePanel
{
	DECLARE_CLASS_SIMPLE( CNB_Gradient_Bar, vgui::EditablePanel );
public:
	CNB_Gradient_Bar( vgui::Panel *parent, const char *name );

	virtual void PaintBackground();
};

#endif // _INCLUDED_NB_HEADER_FOOTER_H
