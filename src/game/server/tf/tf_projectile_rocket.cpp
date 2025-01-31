
//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======
//
// TF Rocket
//
//=============================================================================
#include "cbase.h"
#include "tf_projectile_rocket.h"
#include "tf_weaponbase.h"

//=============================================================================
//
// TF Rocket functions (Server specific).
//
#define ROCKET_MODEL "models/weapons/w_models/w_rocket.mdl"

LINK_ENTITY_TO_CLASS( tf_projectile_rocket, CTFProjectile_Rocket );
PRECACHE_REGISTER( tf_projectile_rocket );

IMPLEMENT_NETWORKCLASS_ALIASED( TFProjectile_Rocket, DT_TFProjectile_Rocket )

BEGIN_NETWORK_TABLE( CTFProjectile_Rocket, DT_TFProjectile_Rocket )
	SendPropInt( SENDINFO( m_bCritical ) ),
END_NETWORK_TABLE()

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CTFProjectile_Rocket *CTFProjectile_Rocket::Create ( CTFWeaponBase *pWeapon, const Vector &vecOrigin, const QAngle &vecAngles, CBaseEntity *pOwner, CBaseEntity *pScorer )
{
	CTFProjectile_Rocket *pRocket = static_cast<CTFProjectile_Rocket*>( CTFBaseRocket::Create( pWeapon, "tf_projectile_rocket", vecOrigin, vecAngles, pOwner ) );

	if ( pRocket )
	{
		pRocket->SetScorer( pScorer );
	}

	return pRocket;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFProjectile_Rocket::Spawn()
{
	SetModel( ROCKET_MODEL );
	
	BaseClass::Spawn();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFProjectile_Rocket::Precache()
{
	PrecacheModel( ROCKET_MODEL );
	PrecacheParticleSystem( "critical_rocket_blue" );
	PrecacheParticleSystem( "critical_rocket_red" );
	PrecacheParticleSystem( "rockettrail" );
	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFProjectile_Rocket::SetScorer( CBaseEntity *pScorer )
{
	m_Scorer = pScorer;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CBasePlayer *CTFProjectile_Rocket::GetScorer( void )
{
	return dynamic_cast<CBasePlayer *>( m_Scorer.Get() );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
int	CTFProjectile_Rocket::GetDamageType() 
{ 
	int iDmgType = BaseClass::GetDamageType();
	if ( m_bCritical )
	{
		iDmgType |= DMG_CRITICAL;
	}

	return iDmgType;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
int	CTFProjectile_Rocket::GetCustomDamageType() 
{ 
	if ( m_bCritical >= 2)
	{
		return TF_DMG_CUSTOM_CRIT_POWERUP;
	}
	else
	{
		return TF_DMG_CUSTOM_NONE;
	}
}



//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CTFCProjectile_IncendRocket *CTFCProjectile_IncendRocket::Create ( CTFWeaponBase *pWeapon, const Vector &vecOrigin, const QAngle &vecAngles, CBaseEntity *pOwner, CBaseEntity *pScorer )
{
	CTFCProjectile_IncendRocket *pRocket = static_cast<CTFCProjectile_IncendRocket*>( CTFBaseRocket::Create( pWeapon, "tfc_projectile_incendrocket", vecOrigin, vecAngles, pOwner ) );

	if ( pRocket )
	{
		pRocket->SetScorer( pScorer );
	}

	return pRocket;
}

LINK_ENTITY_TO_CLASS( tfc_projectile_incendrocket, CTFCProjectile_IncendRocket );
PRECACHE_REGISTER( tfc_projectile_incendrocket );
