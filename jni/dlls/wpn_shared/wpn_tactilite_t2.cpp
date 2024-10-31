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
#include "wpn_tactilite_t2.h"

enum awp_e
{
	AWP_IDLE,
	AWP_SHOOT1,
	AWP_SHOOT2,
	AWP_SHOOT3,
	AWP_RELOAD,
	AWP_DRAW,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5,
ANIM6
};

LINK_ENTITY_TO_CLASS(weapon_tactilite_t2, CTactilite_t2)

void CTactilite_t2::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_tactilite_t2");

	Precache();
	m_iId = WEAPON_AWP;
	SET_MODEL(ENT(pev), "models/w_awp.mdl");

	m_iDefaultAmmo = 10;
	FallInit();
}

void CTactilite_t2::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_tactilite_t2.mdl");

	PRECACHE_MODEL("models/p_tactilite_t2.mdl");

	PRECACHE_SOUND("weapons/tactilite_t2-1.wav");
	PRECACHE_SOUND("weapons/boltpull1.wav");
	PRECACHE_SOUND("weapons/boltup.wav");
	PRECACHE_SOUND("weapons/boltdown.wav");
	PRECACHE_SOUND("weapons/zoom_sniper_in.wav");
PRECACHE_SOUND("weapons/zoom_sniper_out.wav");

	PRECACHE_SOUND("weapons/awp_deploy.wav");
	PRECACHE_SOUND("weapons/awp_clipin.wav");
	PRECACHE_SOUND("weapons/awp_clipout.wav");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/rshell_big.mdl");
	m_usFireTactilite_t2 = PRECACHE_EVENT(1, "events/awp.sc");
}

int CTactilite_t2::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "338Magnum";
	p->iMaxAmmo1 = MAX_AMMO_338MAGNUM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = 10;
	p->iSlot = 0;
	p->iPosition = 2;
	p->iId = WEAPON_AWP;
	p->iFlags = 0;
	p->iWeight = AWP_WEIGHT;

	return 1;
}

BOOL CTactilite_t2::Deploy(void)
{
	if (DefaultDeploy("models/billflx/v_tactilite_t2.mdl", "models/p_tactilite_t2.mdl", AWP_DRAW, "rifle", 0)) 
		{

	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 1;
	m_flNextSecondaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.6;
	
	return TRUE;
	}
	return FALSE;
			
}

void CTactilite_t2::QuickDeploy()
{
SendWeaponAnim(ANIM5, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CTactilite_t2::SecondaryAttack(void)
{
	switch (m_pPlayer->m_iFOV)
	{
		case 90: 

SetThink(&CTactilite_t2::Fov2);
	pev->nextthink = gpGlobals->time + 0.000001;
break;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;

		default: 
SetThink(&CTactilite_t2::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
	}

	m_pPlayer->ResetMaxSpeed();
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;

}

void CTactilite_t2::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CTactilite_t2::Fov3);
	pev->nextthink = gpGlobals->time + 0.000001;

}

void CTactilite_t2::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CTactilite_t2::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;

//m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");

#ifndef CLIENT_DLL
if (weapon_sight_tactilite_t2.value == 0)
CLIENT_COMMAND(m_pPlayer->edict(), "sniper_scope\n");
else if (weapon_sight_tactilite_t2.value == 1) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 1; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 2) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 2; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 3) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 3; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 4) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 4; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 5) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 5; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 6) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 6; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 7) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 7; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 8) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 8; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 9) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 9; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 10) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 10; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 11) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 11; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 12) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 12; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 13) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 13; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 14) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 14; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 15) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 15; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 16) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 16; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 17) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 17; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 18) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 18; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 19) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 19; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 20) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 20; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 21) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 21; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 22) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 22; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 23) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 23; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 24) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 24; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 25) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 25; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 26) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 26; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 27) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 27; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 28) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 28; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 29) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 29; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 30) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 30; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 31) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 31; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 32) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 32; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 33) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 33; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 34) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 34; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 35) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 35; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 36) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 36; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 37) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 37; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 38) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 38; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 39) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 39; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 40) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 40; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 41) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 41; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 42) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 42; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 43) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 43; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 44) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 44; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 45) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 45; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 46) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 46; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 47) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 47; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 48) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 48; Custom_Scope\n");
else if (weapon_sight_tactilite_t2.value == 49) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 49; Custom_Scope\n");
#endif
}

void CTactilite_t2::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 50; 

SetThink(&CTactilite_t2::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CTactilite_t2::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; 

SetThink(&CTactilite_t2::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;


}

void CTactilite_t2::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 30; 

SetThink(&CTactilite_t2::Fov7);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CTactilite_t2::Fov7(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 20;
	
	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_sniper_in.wav", 0.2, 2.4);


SetThink(&CTactilite_t2::breath);
switch (RANDOM_LONG(1, 3))
{
case 1:
	pev->nextthink = gpGlobals->time + 4;
break;
case 2:
	pev->nextthink = gpGlobals->time + 5;
break;
case 3:
	pev->nextthink = gpGlobals->time + 7;
break;
}

}


void CTactilite_t2::breath()
{
switch (m_pPlayer->m_iModelName)
		{
case MODEL_URBAN:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breath\"\n");
			break;
case MODEL_GSG9:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_SAS:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breath\"\n");
			break;
case MODEL_GIGN:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_SPETSNAZ:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_TERROR:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breath\"\n");
			break;
case MODEL_LEET:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_ARCTIC:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breath\"\n");
			break;
case MODEL_GUERILLA:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_MILITIA:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
}

}

void CTactilite_t2::Holster(int skiplocal)
{
m_fInReload = FALSE;
SetThink(nullptr);
}

//offfov

void CTactilite_t2::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 30; 

SetThink(&CTactilite_t2::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTactilite_t2::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; 

SetThink(&CTactilite_t2::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTactilite_t2::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 50; 

SetThink(&CTactilite_t2::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTactilite_t2::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CTactilite_t2::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTactilite_t2::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CTactilite_t2::offFov7);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTactilite_t2::offFov7(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90;
	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_sniper_out.wav", 0.2, 2.4);

m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_tactilite_t2.mdl");

}



void CTactilite_t2::PrimaryAttack(void)
{

	if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		Tactilite_t2Fire(0.0, 2.5, FALSE);
	else if (m_pPlayer->pev->velocity.Length2D() > 140)
		Tactilite_t2Fire(0.0, 2.5, FALSE);
	else if (m_pPlayer->pev->velocity.Length2D() > 10)
		Tactilite_t2Fire(0.0, 2.5, FALSE);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		Tactilite_t2Fire(0.0, 2.5, FALSE);
	else
		Tactilite_t2Fire(0.0, 2.5, FALSE);


}

void CTactilite_t2::Tactilite_t2Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	if (m_pPlayer->pev->fov != 90)
	{
		m_pPlayer->m_iLastZoom = m_pPlayer->m_iFOV;
		m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90;


	}
	else // not zoomed, so bullets diverts more
		flSpread += 0.1;

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

	m_pPlayer->m_flEjectBrass = gpGlobals->time + 0.55;
	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	Vector vecDir = FireBullets3(m_pPlayer->GetGunPosition(), gpGlobals->v_forward, flSpread, 8192, 3, BULLET_PLAYER_338MAG, 135, 0.99, m_pPlayer->pev, TRUE, m_pPlayer->random_seed);

Vector vecSrc = m_pPlayer->GetGunPosition();

SendWeaponAnim(AWP_SHOOT1, 0);
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/tactilite_t2-1.wav", VOL_NORM, ATTN_NORM);

	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev),m_usFireTactilite_t2, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.x * 100), FALSE, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;

#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;
	m_pPlayer->pev->punchangle.x -= 2;
}

void CTactilite_t2::Reload(void)
{
	if (m_pPlayer->ammo_338mag <= 0)
		return;
if (m_iClip == AWP_MAX_CLIP)
return;
	if (DefaultReload(AWP_MAX_CLIP, NULL, 3.1))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		
			//m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 10;
			SetThink(&CTactilite_t2::offFov7);
	pev->nextthink = gpGlobals->time + 0.0000009;


		
	}
SendWeaponAnim(AWP_RELOAD,  0);
}

void CTactilite_t2::QuickReload()
{
	if (m_pPlayer->ammo_338mag <= 0)
		return;
if (m_iClip == AWP_MAX_CLIP)
return;
	if (DefaultReloadQuick(AWP_MAX_CLIP, NULL, 2.1))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		
			//m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 10;
			SetThink(&CTactilite_t2::offFov7);
	pev->nextthink = gpGlobals->time + 0.0000009;


		
	}
SendWeaponAnim(ANIM6,  0);
}

void CTactilite_t2::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60;
		SendWeaponAnim(AWP_IDLE, UseDecrement() != FALSE);
	}
}