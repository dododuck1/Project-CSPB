/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"
#include "game.h"
#include "wpn_mp7.h"

enum sg550_e
{
	SG550_IDLE,
SG550_RELOAD,
	SG550_DRAW, 
	SG550_SHOOT,
	SG550_SHOOT2,
	SG550_SHOOT3,
OFF,
ANIM1,
ANIM2,
ANIM3,
QUICKDEPLOY,
ANIM4
};

LINK_ENTITY_TO_CLASS(weapon_mp7, CMP7)

void CMP7::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_mp7");

	Precache();
	m_iId = WEAPON_SG552;
	SET_MODEL(ENT(pev), "models/w_sg550.mdl");
	m_iDefaultAmmo = 45;

	FallInit();
}

void CMP7::Precache(void)
{
	PRECACHE_MODEL("models/billflx/v_mp7.mdl");
	PRECACHE_MODEL("models/p_mp7.mdl");

	PRECACHE_SOUND("weapons/mp7-1.wav");
	PRECACHE_SOUND("weapons/sg550_boltpull.wav");
	PRECACHE_SOUND("weapons/sg550_clipin.wav");
	PRECACHE_SOUND("weapons/sg550_clipout.wav");
	PRECACHE_SOUND("weapons/zoom_generic_in.wav");
PRECACHE_SOUND("weapons/zoom_generic_out.wav");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireMP7 = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CMP7::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = 45;
	p->iSlot = 0;
	p->iPosition = 16;
	p->iId = WEAPON_SG552;
	p->iFlags = 0;
	p->iWeight = SG552_WEIGHT;

	return 1;
}

BOOL CMP7::Deploy(void)
{

m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	//iShellOn = 1;

return DefaultDeploy("models/billflx/v_mp7.mdl", "models/p_mp7.mdl", SG550_DRAW, "carbine", 0);
	
}

void CMP7::QuickDeploy()
{
SendWeaponAnim(QUICKDEPLOY, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
}

void CMP7::SecondaryAttack(void)
{
switch (m_pPlayer->m_iFOV)
	{
		case 90:

SetThink(&CMP7::Fov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;

		default:
SetThink(&CMP7::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;



 break;
	}
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}


void CMP7::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CMP7::Fov3);
	pev->nextthink = gpGlobals->time + 0.0000009;


#ifndef CLIENT_DLL
if (weapon_sight_mp7.value == 0)
CLIENT_COMMAND(m_pPlayer->edict(), "eotech_scope\n");
else if (weapon_sight_mp7.value == 1) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 1; Custom_Scope\n");
else if (weapon_sight_mp7.value == 2) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 2; Custom_Scope\n");
else if (weapon_sight_mp7.value == 3) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 3; Custom_Scope\n");
else if (weapon_sight_mp7.value == 4) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 4; Custom_Scope\n");
else if (weapon_sight_mp7.value == 5) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 5; Custom_Scope\n");
else if (weapon_sight_mp7.value == 6) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 6; Custom_Scope\n");
else if (weapon_sight_mp7.value == 7) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 7; Custom_Scope\n");
else if (weapon_sight_mp7.value == 8) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 8; Custom_Scope\n");
else if (weapon_sight_mp7.value == 9) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 9; Custom_Scope\n");
else if (weapon_sight_mp7.value == 10) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 10; Custom_Scope\n");
else if (weapon_sight_mp7.value == 11) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 11; Custom_Scope\n");
else if (weapon_sight_mp7.value == 12) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 12; Custom_Scope\n");
else if (weapon_sight_mp7.value == 13) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 13; Custom_Scope\n");
else if (weapon_sight_mp7.value == 14) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 14; Custom_Scope\n");
else if (weapon_sight_mp7.value == 15) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 15; Custom_Scope\n");
else if (weapon_sight_mp7.value == 16) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 16; Custom_Scope\n");
else if (weapon_sight_mp7.value == 17) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 17; Custom_Scope\n");
else if (weapon_sight_mp7.value == 18) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 18; Custom_Scope\n");
else if (weapon_sight_mp7.value == 19) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 19; Custom_Scope\n");
else if (weapon_sight_mp7.value == 20) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 20; Custom_Scope\n");
else if (weapon_sight_mp7.value == 21) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 21; Custom_Scope\n");
else if (weapon_sight_mp7.value == 22) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 22; Custom_Scope\n");
else if (weapon_sight_mp7.value == 23) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 23; Custom_Scope\n");
else if (weapon_sight_mp7.value == 24) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 24; Custom_Scope\n");
else if (weapon_sight_mp7.value == 25) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 25; Custom_Scope\n");
else if (weapon_sight_mp7.value == 26) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 26; Custom_Scope\n");
else if (weapon_sight_mp7.value == 27) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 27; Custom_Scope\n");
else if (weapon_sight_mp7.value == 28) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 28; Custom_Scope\n");
else if (weapon_sight_mp7.value == 29) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 29; Custom_Scope\n");
else if (weapon_sight_mp7.value == 30) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 30; Custom_Scope\n");
else if (weapon_sight_mp7.value == 31) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 31; Custom_Scope\n");
else if (weapon_sight_mp7.value == 32) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 32; Custom_Scope\n");
else if (weapon_sight_mp7.value == 33) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 33; Custom_Scope\n");
else if (weapon_sight_mp7.value == 34) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 34; Custom_Scope\n");
else if (weapon_sight_mp7.value == 35) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 35; Custom_Scope\n");
else if (weapon_sight_mp7.value == 36) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 36; Custom_Scope\n");
else if (weapon_sight_mp7.value == 37) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 37; Custom_Scope\n");
else if (weapon_sight_mp7.value == 38) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 38; Custom_Scope\n");
else if (weapon_sight_mp7.value == 39) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 39; Custom_Scope\n");
else if (weapon_sight_mp7.value == 40) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 40; Custom_Scope\n");
else if (weapon_sight_mp7.value == 41) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 41; Custom_Scope\n");
else if (weapon_sight_mp7.value == 42) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 42; Custom_Scope\n");
else if (weapon_sight_mp7.value == 43) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 43; Custom_Scope\n");
else if (weapon_sight_mp7.value == 44) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 44; Custom_Scope\n");
else if (weapon_sight_mp7.value == 45) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 45; Custom_Scope\n");
else if (weapon_sight_mp7.value == 46) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 46; Custom_Scope\n");
else if (weapon_sight_mp7.value == 47) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 47; Custom_Scope\n");
else if (weapon_sight_mp7.value == 48) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 48; Custom_Scope\n");
else if (weapon_sight_mp7.value == 49) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 49; Custom_Scope\n");
#endif
}

void CMP7::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CMP7::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CMP7::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CMP7::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CMP7::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 65; 

SetThink(&CMP7::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CMP7::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 55; 

m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_in.wav", 0.2, 2.4);
SendWeaponAnim(SG550_IDLE, UseDecrement() != FALSE);

}

//offfov

void CMP7::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CMP7::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CMP7::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CMP7::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CMP7::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CMP7::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}
void CMP7::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 
SendWeaponAnim(SG550_IDLE, 0);
SetThink(&CMP7::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CMP7::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_out.wav", 0.2, 2.4);


m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_mp7.mdl");



}

void CMP7::PrimaryAttack(void)
{
		MP7Fire((0.0) * m_flAccuracy, 0.0825, FALSE);

}

void CMP7::MP7Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((float)(m_iShotsFired * m_iShotsFired * m_iShotsFired) / 220.0) + 0.25;

	if (m_flAccuracy > 1)
		m_flAccuracy = 1;

	if (m_iClip <= 0)
	{
		if (m_fFireOnEmpty)
		{
			PlayEmptySound();
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.2;
		}

		return;
	}

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif


	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_556MM, 20, 0.97, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);

//Vector vecSrc = m_pPlayer->GetGunPosition();
if (m_iClip > 0)
{
SendWeaponAnim(SG550_SHOOT, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(SG550_IDLE, 0);
}
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/mp7-1.wav", VOL_NORM, ATTN_NORM);



	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(),m_usFireMP7, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 10000000), (int)(m_pPlayer->pev->punchangle.y * 10000000), FALSE, FALSE);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;

#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.9;

	if (m_pPlayer->pev->velocity.Length2D() > 0)
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
}

void CMP7::Reload(void)
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == SG550_MAX_CLIP)
return;
	if (DefaultReload(SG550_MAX_CLIP, NULL, 2.3))
	{
		m_flAccuracy = 0.2;
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

		
			SetThink(&CMP7::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 2.5;



		
	}
SendWeaponAnim(SG550_RELOAD, 0);
}

void CMP7::QuickReload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == SG550_MAX_CLIP)
return;
	if (DefaultReloadQuick(SG550_MAX_CLIP, NULL, 1.3))
	{
		m_flAccuracy = 0.2;
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

		
			SetThink(&CMP7::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.5;
	}
SendWeaponAnim(ANIM4, 0);
}

void CMP7::WeaponIdle(void)
{
	ResetEmptySound();

	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60;
		SendWeaponAnim(SG550_IDLE, UseDecrement() != FALSE);
	}
}
