#ifndef WPN_G3SG1_H
#define WPN_G3SG1_H
#ifdef _WIN32
#pragma once
#endif

//g3sg1
#define G3SG1_MAX_SPEED		20
#define G3SG1_MAX_SPEED_ZOOM	150
#define G3SG1_DAMAGE		80
#define G3SG1_RANGE_MODIFER	0.98
#define G3SG1_RELOAD_TIME	3.5

class CAS50 : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override { return HEAVY_SNIPER_SPEED; }
	int iItemSlot() override { return PRIMARY_WEAPON_SLOT; }
	void PrimaryAttack() override;

void QuickDeploy() override;
void QuickReload() override;

void Fov2();
void Fov3();
void Fov4();
void Fov5();
void Fov6();
void Fov7();

void offFov2();
void offFov3();
void offFov4();
void offFov5();
void offFov6();
void offFov7();

void Holster(int skiplocal) override;
void breath();



void Trace(Vector vecSrc, Vector vecDir, float flDamage, float flRadius, int bitsDamageType,
		entvars_t* pevInflictor, entvars_t* pevAttacker);
	void SecondaryAttack() override;
	void Reload() override;
	void WeaponIdle() override;
	BOOL UseDecrement() override {
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}
	KnockbackData GetKnockBackData() override { return { 400.0f, 400.0f, 400.0f, 200.0f, 0.5f }; }

public:
	void M82a1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
int m_iSprBeam;

private:
	unsigned short m_usFireM82a1;
};

#endif