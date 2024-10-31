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
#include "wpn_spectre.h"

enum m4a1_e
{
	AUG_IDLE1,
	AUG_RELOAD,
	AUG_DRAW,
	AUG_SHOOT1,
	AUG_SHOOT2,
	AUG_SHOOT3, 
OFF,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

LINK_ENTITY_TO_CLASS(weapon_spectre, CSPECTRE)

void CSPECTRE::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_spectre");

	Precache();
	m_iId = WEAPON_GALIL;
	SET_MODEL(ENT(pev), "models/w_aug_a3.mdl");

	m_iDefaultAmmo = 45;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;

	FallInit();
}

void CSPECTRE::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_spectre.mdl");
PRECACHE_MODEL("models/p_spectre.mdl");

//test

	PRECACHE_SOUND("weapons/spectre-1.wav");
	PRECACHE_SOUND("weapons/aug_clipout.wav");
	PRECACHE_SOUND("weapons/aug_clipin.wav");
	PRECACHE_SOUND("weapons/aug_boltpull.wav");
	PRECACHE_SOUND("weapons/aug_boltslap.wav");
	PRECACHE_SOUND("weapons/aug_forearm.wav");
PRECACHE_SOUND("weapons/zoom_generic_in.wav");
PRECACHE_SOUND("weapons/zoom_generic_out.wav");


	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireM4A1 = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CSPECTRE::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = 45;
	p->iSlot = 0;
	p->iPosition = 17;
	p->iId = WEAPON_GALIL;
	p->iFlags = 0;
	p->iWeight = 25;

	return 1;
}


BOOL CSPECTRE::Deploy(void)
{
m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

return DefaultDeploy("models/billflx/v_spectre.mdl", "models/p_spectre.mdl", AUG_DRAW, "rifle", 0);

}

void CSPECTRE::QuickDeploy()
{
SendWeaponAnim(ANIM4, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CSPECTRE::SecondaryAttack(void)
{

m_bOnZoom = true;

	switch (m_pPlayer->m_iFOV)
	{
		case 90:

SetThink(&CSPECTRE::Fov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;

		default:
SetThink(&CSPECTRE::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
SendWeaponAnim(OFF, 0);


 break;
	}

	m_pPlayer->ResetMaxSpeed();
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}


void CSPECTRE::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CSPECTRE::Fov3);
	pev->nextthink = gpGlobals->time + 0.0000009;


#ifndef CLIENT_DLL
if (weapon_sight_spectre.value == 0)
CLIENT_COMMAND(m_pPlayer->edict(), "disable_scope\n");
else if (weapon_sight_spectre.value == 1) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 1; Custom_Scope\n");
else if (weapon_sight_spectre.value == 2) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 2; Custom_Scope\n");
else if (weapon_sight_spectre.value == 3) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 3; Custom_Scope\n");
else if (weapon_sight_spectre.value == 4) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 4; Custom_Scope\n");
else if (weapon_sight_spectre.value == 5) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 5; Custom_Scope\n");
else if (weapon_sight_spectre.value == 6) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 6; Custom_Scope\n");
else if (weapon_sight_spectre.value == 7) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 7; Custom_Scope\n");
else if (weapon_sight_spectre.value == 8) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 8; Custom_Scope\n");
else if (weapon_sight_spectre.value == 9) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 9; Custom_Scope\n");
else if (weapon_sight_spectre.value == 10) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 10; Custom_Scope\n");
else if (weapon_sight_spectre.value == 11) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 11; Custom_Scope\n");
else if (weapon_sight_spectre.value == 12) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 12; Custom_Scope\n");
else if (weapon_sight_spectre.value == 13) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 13; Custom_Scope\n");
else if (weapon_sight_spectre.value == 14) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 14; Custom_Scope\n");
else if (weapon_sight_spectre.value == 15) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 15; Custom_Scope\n");
else if (weapon_sight_spectre.value == 16) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 16; Custom_Scope\n");
else if (weapon_sight_spectre.value == 17) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 17; Custom_Scope\n");
else if (weapon_sight_spectre.value == 18) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 18; Custom_Scope\n");
else if (weapon_sight_spectre.value == 19) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 19; Custom_Scope\n");
else if (weapon_sight_spectre.value == 20) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 20; Custom_Scope\n");
else if (weapon_sight_spectre.value == 21) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 21; Custom_Scope\n");
else if (weapon_sight_spectre.value == 22) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 22; Custom_Scope\n");
else if (weapon_sight_spectre.value == 23) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 23; Custom_Scope\n");
else if (weapon_sight_spectre.value == 24) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 24; Custom_Scope\n");
else if (weapon_sight_spectre.value == 25) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 25; Custom_Scope\n");
else if (weapon_sight_spectre.value == 26) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 26; Custom_Scope\n");
else if (weapon_sight_spectre.value == 27) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 27; Custom_Scope\n");
else if (weapon_sight_spectre.value == 28) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 28; Custom_Scope\n");
else if (weapon_sight_spectre.value == 29) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 29; Custom_Scope\n");
else if (weapon_sight_spectre.value == 30) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 30; Custom_Scope\n");
else if (weapon_sight_spectre.value == 31) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 31; Custom_Scope\n");
else if (weapon_sight_spectre.value == 32) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 32; Custom_Scope\n");
else if (weapon_sight_spectre.value == 33) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 33; Custom_Scope\n");
else if (weapon_sight_spectre.value == 34) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 34; Custom_Scope\n");
else if (weapon_sight_spectre.value == 35) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 35; Custom_Scope\n");
else if (weapon_sight_spectre.value == 36) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 36; Custom_Scope\n");
else if (weapon_sight_spectre.value == 37) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 37; Custom_Scope\n");
else if (weapon_sight_spectre.value == 38) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 38; Custom_Scope\n");
else if (weapon_sight_spectre.value == 39) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 39; Custom_Scope\n");
else if (weapon_sight_spectre.value == 40) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 40; Custom_Scope\n");
else if (weapon_sight_spectre.value == 41) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 41; Custom_Scope\n");
else if (weapon_sight_spectre.value == 42) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 42; Custom_Scope\n");
else if (weapon_sight_spectre.value == 43) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 43; Custom_Scope\n");
else if (weapon_sight_spectre.value == 44) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 44; Custom_Scope\n");
else if (weapon_sight_spectre.value == 45) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 45; Custom_Scope\n");
else if (weapon_sight_spectre.value == 46) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 46; Custom_Scope\n");
else if (weapon_sight_spectre.value == 47) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 47; Custom_Scope\n");
else if (weapon_sight_spectre.value == 48) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 48; Custom_Scope\n");
else if (weapon_sight_spectre.value == 49) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 49; Custom_Scope\n");
#endif

}

void CSPECTRE::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CSPECTRE::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CSPECTRE::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CSPECTRE::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CSPECTRE::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 65; 

SetThink(&CSPECTRE::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CSPECTRE::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_in.wav", 0.2, 2.4);



SendWeaponAnim(AUG_IDLE1, UseDecrement() != FALSE);


}

//offfov

void CSPECTRE::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CSPECTRE::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CSPECTRE::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CSPECTRE::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CSPECTRE::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CSPECTRE::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}
void CSPECTRE::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 
SendWeaponAnim(AUG_IDLE1, 0);
SetThink(&CSPECTRE::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CSPECTRE::offFov6(void)
{
	m_bOnZoom = false;
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_out.wav", 0.2, 2.4);

}


void CSPECTRE::PrimaryAttack(void)
{
		M4A1Fire((0.0) * m_flAccuracy, 0.0825, FALSE);
}

void CSPECTRE::M4A1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((float)(m_iShotsFired * m_iShotsFired * m_iShotsFired) / 215.0) + 0.3;

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
	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_556MM, 20, 0.96, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);


//Vector vecSrc = m_pPlayer->GetGunPosition();


if (m_bOnZoom == true)
{

if (m_iClip > 0)
{
SendWeaponAnim(AUG_SHOOT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(AUG_IDLE1, 0);
}

}
else
{

if (m_iClip > 0)
{
SendWeaponAnim(AUG_SHOOT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(AUG_IDLE1, 0);
}

}


EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/spectre-1.wav", VOL_NORM, ATTN_NORM);



	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(),m_usFireM4A1, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;

#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.9;

	m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomFloat(m_pPlayer->random_seed + 4, 1.5, 1.75) + m_pPlayer->pev->punchangle.x * 0.25;
	m_pPlayer->pev->punchangle.y += UTIL_SharedRandomFloat(m_pPlayer->random_seed + 5, -1.0, 1.0);
}

void CSPECTRE::Reload(void)
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == M4A1_MAX_CLIP)
return;
	if (DefaultReload(M4A1_MAX_CLIP, NULL, 2.5))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		
			SetThink(&CSPECTRE::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 3;


		
	}
SendWeaponAnim(AUG_RELOAD, 0);
}

void CSPECTRE::QuickReload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == M4A1_MAX_CLIP)
return;
	if (DefaultReloadQuick(M4A1_MAX_CLIP, NULL, 1.5))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		
			SetThink(&CSPECTRE::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 3;
		
	}
SendWeaponAnim(ANIM5, 0);
}

void CSPECTRE::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(AUG_IDLE1, UseDecrement() != FALSE);
}