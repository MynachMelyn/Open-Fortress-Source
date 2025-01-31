//========= Copyright � 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "cbase.h"

#include <vgui_controls/Label.h>
#include <vgui_controls/Button.h>
#include <vgui_controls/ComboBox.h>
#include <vgui_controls/ImagePanel.h>
#include <vgui_controls/RichText.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/QueryBox.h>
#include <vgui/IScheme.h>
#include <vgui/ILocalize.h>
#include <vgui/ISurface.h>
#include "ienginevgui.h"
#include <game/client/iviewport.h>
#include "tf_tips.h"
#include "renderparm.h"
#include "animation.h"
#include "tf_controls.h"
#include "cvartogglecheckbutton.h"
#include "datacache/imdlcache.h"

#include "of_headeritem.h"
#include "of_loadoutheader.h"

#include "engine/IEngineSound.h"
#include "basemodelpanel.h"
#include "tf_gamerules.h"
#include "of_shared_schemas.h"
#include <convar.h>
#include <vgui_controls/ScrollBarSlider.h>
#include <vgui_controls/Slider.h>
#include "fmtstr.h"

#include "tier0/dbg.h"

using namespace vgui;


DECLARE_BUILD_FACTORY(CTFHeaderItem);

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------

CTFHeaderItem::CTFHeaderItem(Panel *parent, const char *panelName) : CTFEditableButton(parent, panelName)
{
	pLabel = new CExLabel(this, "Label", "");
	iBaseHeight = -999;
}

void CTFHeaderItem::ApplySettings(KeyValues *inResourceData)
{
	BaseClass::ApplySettings( inResourceData );

	KeyValues *inLabel = inResourceData->FindKey("Label");
	if( inLabel )
	{
		pLabel->ApplySettings(inLabel);
		IScheme *pScheme = scheme()->GetIScheme( GetScheme() );
		m_hTextFont = pScheme->GetFont( inLabel->GetString("font"), true );
	}
	SetConnectedPanel( inResourceData->GetString("panel") );
	
	CalculateBoxSize();
}

void CTFHeaderItem::CalculateBoxSize()
{
	int textLen = 0;

	wchar_t szUnicode[512];
	pLabel->GetText( szUnicode, sizeof( szUnicode ) );
	
	int len = wcslen( szUnicode );
	for ( int i=0;i<len;i++ )
	{
		textLen += surface()->GetCharacterWidth( m_hTextFont, szUnicode[i] );
	}
	
	textLen += 20; // Padding
	
	int w,h;
	GetSize( w, h );
	SetSize( textLen, h );
	
	pLabel->GetSize( w, h );
	pLabel->SetSize( textLen, h );
	
	pButton->GetSize( w, h );
	pButton->SetSize( textLen, h );
	
	pLabel->GetPos( w, h );
	pLabel->SetPos( w + 10, h );
}

void CTFHeaderItem::PerformLayout()
{
	BaseClass::PerformLayout();
}

void CTFHeaderItem::SetConnectedPanel( const char *szConnectedPanel )
{
	Panel *pContainer = GetParent();
	if( !pContainer )
		return;
	
	Panel *pParent = pContainer->GetParent();
	if( !pParent )
	{
		pParent = GetParent();
	}
	
	if( !pParent )
		return;

	pConnectedPanel = pParent->FindChildByName( szConnectedPanel );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFHeaderItem::OnMouseReleased(MouseCode code)
{
	if( m_bSelected )
		return;

	BaseClass::OnMouseReleased(code);
}

void CTFHeaderItem::OnReleasedSelected()
{
	BaseClass::OnReleasedSelected();

	if( pConnectedPanel )
		pConnectedPanel->SetVisible( false );
	
}

void CTFHeaderItem::OnReleasedUnselected()
{
	BaseClass::OnReleasedUnselected();

	if( pConnectedPanel )
		pConnectedPanel->SetVisible( true );
	
}

void CTFHeaderItem::SetSelected( bool bSelected )
{
	BaseClass::SetSelected( bSelected );
	
	int x, y;
	GetPos( x, y );	
	
	if( !bSelected )
	{
		if( iBaseHeight == -999 )
			iBaseHeight = y;
		SetPos( x , iBaseHeight );
	}
	else
	{
		if( iBaseHeight == -999 )
			iBaseHeight = y;			
		SetPos( x , iBaseHeight - 25 );
	}

	CTFLoadoutHeader *pHeaderList = dynamic_cast<CTFLoadoutHeader*>( GetParent() );
	
	if( pHeaderList )
	{
		if( bSelected )
		{
			if( pHeaderList->pSelectedHeader )
			{
				pHeaderList->pSelectedHeader->OnReleasedSelected();
				pHeaderList->pSelectedHeader->SetSelected( false );
			}
			pHeaderList->pSelectedHeader = this;
		}
		else if( pHeaderList->pSelectedHeader == this )
		{
				pHeaderList->pSelectedHeader = NULL;
		}
	}
}