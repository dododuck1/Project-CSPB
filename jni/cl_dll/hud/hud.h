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
//			
//  hud.h
//
// class CHud declaration
//
// CHud handles the message, calculation, and drawing the HUD
//
#pragma once

#define RGB_YELLOWISH 0x00FFA000 //255,160,0
#define RGB_REDISH 0x00FF1010 //255,16,16
#define RGB_GREENISH 0x0099CC00 //0,160,0
#define RGB_WHITE 0x00FFFFFF
#define RGB_LIGHTBLUE 0x0072C5FF //114, 197, 255

#include <assert.h>
#include <string.h>

#include "wrect.h"
#include "cl_dll.h"
#include "ammo.h"

#include "csprite.h"
#include "cvardef.h" // cvar_t

enum GameMode_e : byte; // #include "gamemode/mods_const.h"

#define MIN_ALPHA	 100	
#define	HUDELEM_ACTIVE	1
#define CHudMsgFunc(x) int MsgFunc_##x(const char *pszName, int iSize, void *buf)
#define CHudUserCmd(x) void UserCmd_##x()

class RGBA
{
public:
	unsigned char r, g, b, a;
};

enum 
{ 
	MAX_PLAYERS = 33, // including the bomb
	MAX_TEAMS = 3,
	MAX_TEAM_NAME = 16,
	MAX_HOSTAGES = 24,
};

extern const char *sPlayerModelFiles[];
extern wrect_t nullrc;

class CClientSprite;

inline bool BIsValidTModelIndex( int i )
{
	if ( i == 1 || i == 5 || i == 6 || i == 8 || i == 11 )
		return true;
	else
		return false;
}

inline bool BIsValidCTModelIndex( int i )
{
	if ( i == 7 || i == 2 || i == 10 || i == 4 || i == 9)
		return true;
	else
		return false;
}

#define HUD_DRAW         (1 << 0)
#define HUD_THINK        (1 << 1)
#define HUD_ACTIVE       (HUD_DRAW | HUD_THINK)
#define HUD_INTERMISSION (1 << 2)

#define MAX_PLAYER_NAME_LENGTH		32

#define	MAX_MOTD_LENGTH				1536

//
//-----------------------------------------------------
//
class CHudBase
{
public:
	int	  m_iFlags; // active, moving,
	virtual		~CHudBase() {}
	virtual int Init( void ) {return 0;}
	virtual int VidInit( void ) {return 0;}
	virtual int Draw(float flTime) {return 0;}
	virtual void Think(void) {return;}
	virtual void Reset(void) {return;}
	virtual void InitHUDData( void ) {}		// called every time a server is connected to
	virtual void Shutdown( void ) {}

};

struct HUDLIST {
	CHudBase	*p;
	HUDLIST		*pNext;
};



//
//-----------------------------------------------------
//
//#include "voice_status.h"
#include "hud_spectator.h"
#include "followicon.h"
#include "scenariostatus.h"
#include "health.h"
#include "radar.h"
#include "scoreboard.h"
#include "zbs/zbs.h"
#include "zb2/zb2.h"
#include "zb3/zb3.h"
#include "retina.h"
#include "moe/moe_touch.h"
#include "kill_effect.h"

//
//-----------------------------------------------------
//
class CHudAmmo: public CHudBase
{
	friend class WeaponsResource;
	friend class HistoryResource;

public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	void Think(void);
	void Reset(void);

//pb stuff 
int GetHudNumberWidth(int moe, wrect_t *prc, int iFlags, int iNumber);
void BuildHudNumberRect(int moe, wrect_t *prc, int w, int h, int xOffset, int yOffset);
int DrawHudNumberBill(int moe, wrect_t *prc, int x, int y, int iFlags, int iNumber, int r, int g, int b);


	void DrawCrosshair(float flTime);
	int DrawCrosshairEx(float flTime, int weaponid, int iBarSize, float flCrosshairDistance, bool bAdditive, int r, int g, int b, int a);
	void CalcCrosshairSize();
	void CalcCrosshairDrawMode();
	void CalcCrosshairColor();

	int DrawWList(float flTime);
	CHudMsgFunc(CurWeapon);
	CHudMsgFunc(WeaponList);
	CHudMsgFunc(AmmoX);
	CHudMsgFunc(AmmoPickup);
	CHudMsgFunc(WeapPickup);
	CHudMsgFunc(ItemPickup);
	CHudMsgFunc(HideWeapon);
	CHudMsgFunc(Crosshair);
	CHudMsgFunc(Brass);


	void SlotInput( int iSlot );
	CHudUserCmd(Slot1);
	CHudUserCmd(Slot2);
	CHudUserCmd(Slot3);
	CHudUserCmd(Slot4);
	CHudUserCmd(Slot5);
	CHudUserCmd(Slot6);
	CHudUserCmd(Slot7);
	CHudUserCmd(Slot8);
	CHudUserCmd(Slot9);
	CHudUserCmd(Slot10);
	CHudUserCmd(Close);
	CHudUserCmd(NextWeapon);
	CHudUserCmd(PrevWeapon);
	CHudUserCmd(Adjust_Crosshair);
	CHudUserCmd(Rebuy);
	CHudUserCmd(Autobuy);

	bool FHasSecondaryAmmo() { return m_pWeapon && m_pWeapon->iAmmo2Type > 0; }

public:
	float m_fFade;
	RGBA  m_rgba;
	WEAPON *m_pWeapon;
	int	m_HUD_bucket0;
	int m_HUD_selection;

	int m_iAlpha;
	int m_R, m_G, m_B;
	int m_cvarR, m_cvarG, m_cvarB;
	int m_iCurrentCrosshair;
	int m_iCrosshairScaleBase;
	float m_flCrosshairDistance;
	bool m_bAdditive;
	bool m_bObserverCrosshair ;
	bool m_bDrawCrosshair;
	int m_iAmmoLastCheck;

	cvar_t *m_pClCrosshairColor;
	cvar_t *m_pClCrosshairTranslucent;
	cvar_t *m_pClCrosshairSize;
	cvar_t *m_pClDynamicCrosshair;
	cvar_t *m_pHud_FastSwitch;
	cvar_t *m_pHud_DrawHistory_Time;

	cvar_t *cl_crosshair_type;

private:
UniqueTexture pb_crosshair[4];
UniqueTexture m_weaponbg;
UniqueTexture weaponname_bg;;
wrect_t m_rcNumber_Large[10];
wrect_t m_rcNumber_Small[10];
wrect_t m_rcNumber_csgo[10];
wrect_t m_rcNumber_csgo_sml[10];

UniqueTexture m_specials[10];

int m_iNum_csgo;
int m_iNum_L;
int m_iNum_csgo_sml;

wrect_t m_rcNumber_Large_ammo[10];
wrect_t m_rcNumber_Small_ammo[10];
int m_iNum_L_ammo;
int m_iNum_S_ammo;


};

//
//-----------------------------------------------------
//


//
class CHudBackground: public CHudBase
{
    public:
    int Init(void);
    int VidInit(void);
    int Draw(float flTime);
    CHudUserCmd(Cmd1);
    
    CHudMsgFunc(ImgFade);
    
    private:
    float ffade;
    int ffade2;
    float m_fFade;
    float m_fFade2;
    float m_fFade3;
    float m_fFade4;
    float m_fFade5;
    
    float m_fFade6;
    float m_fFade7;
    float m_fFade8;
    float m_fFade9;
    float m_fFade10;
    
    UniqueTexture m_dmg;
    
};

class CHudAmmoSecondary: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	void Reset( void );
	int Draw(float flTime);

	CHudMsgFunc(SecAmmoVal);
	CHudMsgFunc(SecAmmoIcon);

private:
	enum {
		MAX_SEC_AMMO_VALUES = 4
	};

	int m_HUD_ammoicon; // sprite indices
	int m_iAmmoAmounts[MAX_SEC_AMMO_VALUES];
	float m_fFade;
};

#define FADE_TIME 100


//
//-----------------------------------------------------
//
class CHudGeiger: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	CHudMsgFunc(Geiger);
	
private:
	int m_iGeigerRange;

};

//
//-----------------------------------------------------
//
class CHudTrain: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	CHudMsgFunc(Train);

private:
	HSPRITE m_hSprite;
	int m_iPos;

};

//
//-----------------------------------------------------
//
//  MOTD in cs16 must render HTML, so it disabled
//

class CHudMOTD : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );
	void Reset( void );

	CHudMsgFunc(MOTD);
	void Scroll( int dir );
	void Scroll( float amount );
	float scroll;
	bool m_bShow;
	cvar_t *cl_hide_motd;

protected:
	static int MOTD_DISPLAY_TIME;
	char m_szMOTD[ MAX_MOTD_LENGTH ];
	
	int m_iLines;
	int m_iMaxLength;
	bool ignoreThisMotd;
};

//
//-----------------------------------------------------
//
class CHudStatusBar : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );
	void Reset( void );
	void ParseStatusString( int line_num );
	CHudMsgFunc(StatusText);
	CHudMsgFunc(StatusValue);
int m_dotc;

protected:
	enum {
		MAX_STATUSTEXT_LENGTH = 128,
		MAX_STATUSBAR_VALUES = 8,
		MAX_STATUSBAR_LINES = 2,
	};

	char m_szStatusText[MAX_STATUSBAR_LINES][MAX_STATUSTEXT_LENGTH];  // a text string describing how the status bar is to be drawn
	char m_szStatusBar[MAX_STATUSBAR_LINES][MAX_STATUSTEXT_LENGTH];	// the constructed bar that is drawn
	int m_iStatusValues[MAX_STATUSBAR_VALUES];  // an array of values for use in the status bar

	int m_bReparseString; // set to TRUE whenever the m_szStatusBar needs to be recalculated

	// an array of colors...one color for each line
	float *m_pflNameColors[MAX_STATUSBAR_LINES];

	cvar_t *hud_centerid;
};

struct extra_player_info_t 
{
	short frags;
	short deaths;
	short playerclass;
	short teamnumber;
	char teamname[MAX_TEAM_NAME];
	bool has_c4;
	bool vip;
	bool dead;
	bool zombie;
	bool showhealth;
	bool nextflash;
	bool talking;
	Vector origin;
	int health;
	int radarflashes;
	float radarflashtime;
	float radarflashtimedelta;
	char location[32];
};

struct team_info_t 
{
	char name[MAX_TEAM_NAME];
	short frags;
	short deaths;
	short ownteam;
	short players;
	int already_drawn;
	int scores_overriden;
	int sumping;
	int teamnumber;
};

struct hostage_info_t
{
	vec3_t origin;
	float radarflashtimedelta;
	float radarflashtime;
	bool dead;
	bool nextflash;
	int radarflashes;
};

extern hud_player_info_t	g_PlayerInfoList[MAX_PLAYERS+1];	   // player info from the engine
extern extra_player_info_t  g_PlayerExtraInfo[MAX_PLAYERS+1];   // additional player info sent directly to the client dll
extern team_info_t			g_TeamInfo[MAX_TEAMS+1];
extern hostage_info_t		g_HostageInfo[MAX_HOSTAGES+1];
extern int					g_IsSpectator[MAX_PLAYERS+1];


//
//-----------------------------------------------------
//
class CHudDeathNotice : public CHudBase
{
public:
	int Init( void );
	void Reset(void);
	void InitHUDData( void );
	int VidInit( void );
	void Shutdown(void);
	int Draw( float flTime );
	CHudMsgFunc(DeathMsg);
int m_hKill1;
int m_hKill2;
int m_hKill3;
int m_hKill4;

private:
	int m_HUD_d_skull;  // sprite index of skull icon
	int m_HUD_d_headshot;
	cvar_t *hud_deathnotice_time;

	int m_killNums, m_multiKills;
int numberkills;
	int m_iconIndex;
	bool m_showIcon, m_showKill;
	float m_killEffectTime, m_killIconTime;

private:
	SharedTexture m_killBg[3];
SharedTexture m_ann_hs[1];
	SharedTexture m_deathBg[3];
UniqueTexture m_kills[7];
SharedTexture m_headshot;
	int m_KM_Number0;
int m_KM_Star;
	int m_KM_Number1;
	int m_KM_Number2;
	int m_KM_Number3;
	int m_KM_KillText;
	int m_KM_Icon_Head;
	int m_KM_Icon_Knife;
	int m_KM_Icon_Frag;
};

class CHudDeathNotice1 : public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	int Draw( float flTime );
	CHudMsgFunc(DeathMsg);

private:
	int m_HUD_d_skull;  // sprite index of skull icon
	int m_HUD_d_headshot;
	cvar_t *hud_deathnotice_time;
};

//
//-----------------------------------------------------
//
class CHudMenu : public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	void Reset( void );
	int Draw( float flTime );

	CHudMsgFunc(ShowMenu);
	CHudMsgFunc(BuyClose);
	CHudMsgFunc(VGUIMenu);
	// server sends false when spectating is not allowed, and true when allowed
	CHudMsgFunc(AllowSpec);

	CHudUserCmd(OldStyleMenuClose);
	CHudUserCmd(OldStyleMenuOpen);
	CHudUserCmd(ShowVGUIMenu);

	void ShowVGUIMenu( int menuType ); // cs16client extension

	void SelectMenuItem( int menu_item );

	int m_fMenuDisplayed;
	bool m_bAllowSpec;
	cvar_t *_extended_menus;
	int m_bitsValidSlots;
	float m_flShutoffTime;
	int m_fWaitingForMore;

};

//
//-----------------------------------------------------
//
class CHudSayText : public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	int Draw( float flTime );
	CHudMsgFunc(SayText);
	void SayTextPrint( const char *pszBuf, int iBufSize, int clientIndex = -1 );
	void SayTextPrint( char szBuf[3][256] );
	void EnsureTextFitsInOneLineAndWrapIfHaveTo( int line );
	friend class CHudSpectator;

private:

	struct cvar_s *	m_HUD_saytext;
	struct cvar_s *	m_HUD_saytext_time;
};

//
//-----------------------------------------------------
//
class CHudBattery: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	void InitHUDData( void );
	CHudMsgFunc(Battery);
	CHudMsgFunc(ArmorType);
	
private:
	enum armortype_t {
		Vest = 0,
		VestHelm
	} m_enArmorType;

	CClientSprite m_hEmpty[VestHelm + 1];
	CClientSprite m_hFull[VestHelm + 1];
	int	  m_iBat;
	float m_fFade;
	int	  m_iHeight;		// width of the battery innards
};


//
//-----------------------------------------------------
//
class CHudFlashlight: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	void Reset( void );
	CHudMsgFunc(Flashlight);
	CHudMsgFunc(FlashBat);
	
private:
	CClientSprite m_hSprite1;
	CClientSprite m_hSprite2;
	CClientSprite m_hBeam;
	float m_flBat;
	int	  m_iBat;
	int	  m_fOn;
	float m_fFade;
	int	  m_iWidth;		// width of the battery innards
};

//
//-----------------------------------------------------
//
const int maxHUDMessages = 16;
struct message_parms_t
{
	client_textmessage_t	*pMessage;
	float	time;
	int x, y;
	int	totalWidth, totalHeight;
	int width;
	int lines;
	int lineLength;
	int length;
	int r, g, b;
	int text;
	int fadeBlend;
	float charTime;
	float fadeTime;
};

//
//-----------------------------------------------------
//

class CHudTextMessage: public CHudBase
{
public:
	int Init( void );
	static char *LocaliseTextString( const char *msg, char *dst_buffer, int buffer_size );
	static char *BufferedLocaliseTextString( const char *msg );
	static char *LookupString( char *msg_name, int *msg_dest = NULL );
	CHudMsgFunc(TextMsg);
};

//
//-----------------------------------------------------
//

class CHudMessage: public CHudBase
{
public:
	friend class CHudTextMessage;
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	CHudMsgFunc(HudText);
	CHudMsgFunc(GameTitle);
	CHudMsgFunc(HudTextArgs);
	CHudMsgFunc(HudTextPro);

	float FadeBlend( float fadein, float fadeout, float hold, float localTime );
	int	XPosition( float x, int width, int lineWidth );
	int YPosition( float y, int height );

	void MessageAdd( const char *pName, float time );
	void MessageAdd(client_textmessage_t * newMessage );
	void MessageDrawScan( client_textmessage_t *pMessage, float time );
	void MessageScanStart( void );
	void MessageScanNextChar( void );
	void Reset( void );

private:
	client_textmessage_t		*m_pMessages[maxHUDMessages];
	float						m_startTime[maxHUDMessages];
	message_parms_t				m_parms;
	float						m_gameTitleTime;
	client_textmessage_t		*m_pGameTitle;

	int m_HUD_title_life;
	int m_HUD_title_half;
};

//
//-----------------------------------------------------
//
#define MAX_SPRITE_NAME_LENGTH	24

class CHudStatusIcons: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	void Reset( void );
	void Shutdown(void);
	int Draw(float flTime);
	CHudMsgFunc(StatusIcon);

	enum {
		MAX_ICONSPRITENAME_LENGTH = MAX_SPRITE_NAME_LENGTH,
		MAX_ICONSPRITES = 4,
	};

	
	//had to make these public so CHud could access them (to enable concussion icon)
	//could use a friend declaration instead...
	void EnableIcon( const char *pszIconName, unsigned char red, unsigned char green, unsigned char blue );
	void DisableIcon( const char *pszIconName );

	friend class CHudScoreboard;

private:

	typedef struct
	{
		char szSpriteName[MAX_ICONSPRITENAME_LENGTH];
		HSPRITE spr;
		wrect_t rc;
		unsigned char r, g, b;
		unsigned char secR, secG, secB;
		float flTimeToChange;
	} icon_sprite_t;

	icon_sprite_t m_IconList[MAX_ICONSPRITES];
	UniqueTexture m_tgaC4[2];
};


//
//-----------------------------------------------------
//
#define MONEY_YPOS ScreenHeight - 3 * gHUD.m_iFontHeight

class CHudMoney : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );
	CHudMsgFunc(Money);
	CHudMsgFunc(BlinkAcct);

private:
	int m_iMoneyCount;
	int m_iDelta;
	int m_iBlinkAmt;
	float m_fBlinkTime;
	float m_fFade;
	CClientSprite m_hDollar;
	CClientSprite m_hPlus;
	CClientSprite m_hMinus;
};
//
//-----------------------------------------------------
//
class CHudRadio: public CHudBase
{
public:
	int Init( void );
	void Voice(int entindex, bool bTalking );
	// play a sentence from a radio
	// [byte] unknown (always 1)
	// [string] sentence name
	// [short] unknown. (always 100, it's a volume?)
	CHudMsgFunc(SendAudio);
	CHudMsgFunc(ReloadSound);
	CHudMsgFunc(BotVoice);
};

//
//-----------------------------------------------------
//
class CHudTimer: public CHudBase
{
	friend class CHudSpectatorGui;
	friend class CHudScenarioStatus;
public:
	int Init( void );
	int VidInit( void );
	void Reset(void);
void BuildHudNumberRect(int moe, wrect_t *prc, int w, int h, int xOffset, int yOffset);
	int Draw(float fTime);
	// set up the timer.
	// [short]
	CHudMsgFunc(RoundTime);
	// show the timer
	// [empty]
	CHudMsgFunc(ShowTimer);

CHudMsgFunc(Respawning);
CHudUserCmd(CommandActiveRespawning);

CHudMsgFunc(C4_hud);
//CHudUserCmd(CommandActiveC4_hud);
private:
	int m_HUD_timer;
	int m_iTime;
int m_Text_Round;

//
int GetHudNumberWidth(int moe, wrect_t *prc, int iFlags, int iNumber);

int DrawHudNumber(int moe, wrect_t *prc, int x, int y, int iFlags, int iNumber, int r, int g, int b);


int m_iNum_L;

	float m_fStartTime;
	bool m_bPanicColorChange;
	float m_flPanicTime;
	int m_closestRight;
UniqueTexture m_pTexture_Black;
UniqueTexture m_pTexture_Blackevo;
wrect_t m_rcNumber_Large[10];

UniqueTexture m_respawning;
UniqueTexture m_c4_bg;

int c4Time;
bool enable_c4hud;
float StartC4;
};
//
//-----------------------------------------------------
//
class CHudProgressBar: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );

	// start progress bar
	// [short] Duration
	CHudMsgFunc(BarTime);

	// [short] Duration
	// [short] percent
	CHudMsgFunc(BarTime2);
	CHudMsgFunc(BotProgress);

private:
	int m_iDuration;
	float m_fPercent;
	float m_fStartTime;
	char m_szHeader[256];
	const char *m_szLocalizedHeader;
};

//
//-----------------------------------------------------
//
// class for drawing sniper scope
class CHudSniperScope: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );

CHudMsgFunc(Reddot_Scope);
CHudUserCmd(CommandActiveReddot);

CHudMsgFunc(Eotech_Scope);
CHudUserCmd(CommandActiveEotech);

CHudMsgFunc(Acog_Scope);
CHudUserCmd(CommandActiveAcog);

CHudMsgFunc(Dot_l_Scope);
CHudUserCmd(CommandActiveDot_l);

CHudMsgFunc(Telescopic_Scope);
CHudUserCmd(CommandActiveTelescopic);

CHudMsgFunc(EotechCrb_Scope);
CHudUserCmd(CommandActiveEotechCrb);

CHudMsgFunc(EotechPandora_Scope);
CHudUserCmd(CommandActiveEotechPandora);

CHudMsgFunc(Sks_Scope);
CHudUserCmd(CommandActiveSksScope);

CHudMsgFunc(Sniper_Scope);
CHudUserCmd(CommandActiveSniperScope);

CHudMsgFunc(Azure_Scope);
CHudUserCmd(CommandActiveAzureScope);

CHudMsgFunc(EotechDot_Scope);
CHudUserCmd(CommandActiveEotechDot);

CHudMsgFunc(Disable_Scope);
CHudUserCmd(CommandActiveDisableScope);

CHudMsgFunc(Custom_Scope);
CHudUserCmd(CommandActiveCustomScope);

public:

float time_Reddot; 
float time_Eotech;
float time_Acog;
float time_Dot_l;
float time_Telescopic;
float time_EotechCrb;
float time_EotechPandora;
float time_SksScope;
float time_SniperScope;
float time_AzureScope;
float time_EotechDot;
float Disable_Scope;
float time_CustomSight;

bool active_Reddot; 
bool active_Eotech;
bool active_Acog;
bool active_Dot_l;
bool active_Telescopic;
bool active_EotechCrb;
bool active_EotechPandora;
bool active_SksScope;
bool active_SniperScope;
bool active_AzureScope;
bool active_EotechDot;
bool active_CustomSight;

private:
	float left, right, centerx, centery;
	UniqueTexture m_sight[13];
	UniqueTexture m_CustomSight[50];
};


//
//-----------------------------------------------------
//
// class for drawing keys
class CHudKeys: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );

CHudMsgFunc(ShowQ);
CHudUserCmd(CommandActiveShowQ);

private:
	UniqueTexture m_keys[12];

public:
long Q_time;
};

class CHudNVG: public CHudBase
{
public:
	int Init( void );
	int VidInit(void);
	int Draw( float flTime );
	CHudMsgFunc(NVGToggle);

	CHudUserCmd(NVGAdjustUp);
	CHudUserCmd(NVGAdjustDown);
private:
	int m_iAlpha;
	cvar_t *cl_fancy_nvg;
	dlight_t *m_pLight;
	float m_LightStypeBackup;
};

//
//-----------------------------------------------------
//

class CHudSpectatorGui: public CHudBase
{
public:
	int Init();
	int VidInit();
	int Draw( float flTime );
	void InitHUDData();
	void Reset();
	void Shutdown();

	CHudMsgFunc( SpecHealth );
	CHudMsgFunc( SpecHealth2 );

	CHudUserCmd( ToggleSpectatorMenu );
	CHudUserCmd( ToggleSpectatorMenuOptions );
	CHudUserCmd( ToggleSpectatorMenuOptionsSettings );
	CHudUserCmd( ToggleSpectatorMenuSpectateOptions );

	void CalcAllNeededData( );

	bool m_bBombPlanted;
	int m_iPlayerLastPointedAt;
	static float m_fTextScale;

private:	
	// szMapName is 64 bytes only. Removing "maps/" and ".bsp" gived me this result
	class Labels
	{
	public:
		short m_iTerrorists;
		short m_iCounterTerrorists;
		char m_szTimer[64];
		char m_szMap[64];
		char m_szNameAndHealth[80];
	} label;
	UniqueTexture m_hTimerTexture;
UniqueTexture m_respawnimage;
UniqueTexture m_spectatortex[2];

	enum {
		ROOT_MENU = (1<<0),
		MENU_OPTIONS = (1<<1),
		MENU_OPTIONS_SETTINGS = (1<<2),
		MENU_SPEC_OPTIONS = (1<<3)
	};
	byte m_menuFlags;
};

//
//-----------------------------------------------------
//

class CHudHeadName : public CHudBase
{
public:
	int Init();
	int VidInit();
	int Draw(float flTime);
	bool CheckForPlayer(cl_entity_s *pEnt);

CHudMsgFunc(HeadName);
CHudUserCmd(CommandActiveHeadName);

private:
Vector m_TargetOrigin;

int enable;

};


//
//-----------------------------------------------------
//

//damaga
class CHudDamagePb: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );

CHudMsgFunc(DamagePb);
CHudUserCmd(CommandActive);

public:
float m_fFade;
float ffade;

private:
int m_damage_tex;
};

//

//DeathScreen 
class CHudDeathScreen: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );

CHudMsgFunc(DeathScreen);
CHudUserCmd(CommandActiveDeathScreen);


public:
float m_fFade;
float ffade;

private:
int m_death_tex;
};

//inventory give 
class CHudInventoryGive : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );

CHudMsgFunc(InventoryGive);
CHudUserCmd(CommandActiveInventoryGive);

CHudMsgFunc(FadeViewModel);
CHudUserCmd(CommandActiveFadeViewModel);

CHudMsgFunc(QuickDeploy_client);
CHudUserCmd(CommandActiveQuickDeploy_client);

CHudMsgFunc(QuickReload_client);
CHudUserCmd(CommandActiveQuickReload_client);

CHudMsgFunc(Mode_ui);
CHudUserCmd(CommandActiveMode_ui);

CHudMsgFunc(BlinkViewmodel);
CHudUserCmd(CommandActiveBlinkViewmodel);

public:
float FadeViewModel_time;
float BlinkViewmodel_time;

};


//hb
class CHudHealthbar : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );
int DrawBar(int x, int y, int width, int height, float f, int& r, int& g, int& b, int& a);

CHudMsgFunc(HealthBar);
CHudUserCmd(CommandActiveHealthBar);

public:
float m_fFade;
long fade_time;

private:
UniqueTexture m_healthbar[12];
Vector m_TargetOrigin;

int ehealth;
int instantDeath;

};


class CHudMission_Announcement_Red: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );

CHudMsgFunc(Mission_Announcement_Red);
CHudUserCmd(CommandActiveMission_Announcement_Red);

public:
float m_fFade;
float ffade;

private:
//int m_win;
UniqueTexture m_win;
};

class CHudMission_Announcement_Blue: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );

CHudMsgFunc(Mission_Announcement_Blue);
CHudUserCmd(CommandActiveMission_Announcement_Blue);

public:
float m_fFade;
float ffade;

private:
//int m_win;
UniqueTexture m_win;
};


//inventory ui
class CHudInventoryUi : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );

CHudMsgFunc(Openinv);
CHudUserCmd(CommandActiveOpeninv);

CHudMsgFunc(Closeinv);
CHudUserCmd(CommandActiveCloseinv);

CHudMsgFunc(Nextprim);
CHudUserCmd(CommandActiveNextprim);
CHudMsgFunc(Prevprim);
CHudUserCmd(CommandActivePrevprim);

CHudMsgFunc(Nextsec);
CHudUserCmd(CommandActiveNextsec);
CHudMsgFunc(Prevsec);
CHudUserCmd(CommandActivePrevsec);

CHudMsgFunc(Nextmelee);
CHudUserCmd(CommandActiveNextmelee);
CHudMsgFunc(Prevmelee);
CHudUserCmd(CommandActivePrevmelee);

CHudMsgFunc(Nextexplo);
CHudUserCmd(CommandActiveNextexplo);
CHudMsgFunc(Prevexplo);
CHudUserCmd(CommandActivePrevexplo);

CHudMsgFunc(Nextspe);
CHudUserCmd(CommandActiveNextspe);
CHudMsgFunc(Prevspe);
CHudUserCmd(CommandActivePrevspe);

public:
bool open;
float m_fFade;

UniqueTexture bg;
UniqueTexture select_prim;
UniqueTexture select_sec;
UniqueTexture select_melee;
UniqueTexture select_explo;
UniqueTexture select_spe;

UniqueTexture primary[500];
UniqueTexture secondary[500];
UniqueTexture melee[500];
UniqueTexture special[500];
UniqueTexture explosive[500];

};

//
//-----------------------------------------------------
//

//
//-----------------------------------------------------
//

class CHud
{
public:
	CHud() : m_pHudList(NULL), m_iSpriteCount(0)  {}
	~CHud();			// destructor, frees allocated memory // thanks, Captain Obvious

	void Init( void );
	void VidInit( void );
	void Think( void );
	void Shutdown( void );
	int Redraw( float flTime, int intermission );
	int UpdateClientData( client_data_t *cdata, float time );
	void AddHudElem(CHudBase *p);

	inline float GetSensitivity() { return m_flMouseSensitivity; }
	inline HSPRITE GetSprite( int index )
	{
		assert( index >= -1 && index <= m_iSpriteCount );

		return (index >= 0) ? m_rghSprites[index] : 0;
	}

	inline wrect_t& GetSpriteRect( int index )
	{
		assert( index >= -1 && index <= m_iSpriteCount );

		return (index >= 0) ? m_rgrcRects[index]: nullrc;
	}

	// GetSpriteIndex()
	// searches through the sprite list loaded from hud.txt for a name matching SpriteName
	// returns an index into the gHUD.m_rghSprites[] array
	// returns -1 if sprite not found
	inline int GetSpriteIndex( const char *SpriteName )
	{
		// look through the loaded sprite name list for SpriteName
		for ( int i = 0; i < m_iSpriteCount; i++ )
		{
			if ( strnicmp( SpriteName, m_rgszSpriteNames + (i * MAX_SPRITE_NAME_LENGTH), MAX_SPRITE_NAME_LENGTH ) == 0 )
				return i;
		}

		gEngfuncs.Con_Printf( "GetSpriteIndex: %s sprite not found", SpriteName );
		return -1; // invalid sprite
	}

	inline short GetCharWidth ( unsigned char ch )
	{
		return m_scrinfo.charWidths[ ch ];
	}
	inline int GetCharHeight( )
	{
		return m_scrinfo.iCharHeight;
	}

	inline bool IsCZero( )
	{
		return m_bIsCZero;
	}


	float   m_flTime;      // the current client time
	float   m_fOldTime;    // the time at which the HUD was last redrawn
	double  m_flTimeDelta; // the difference between flTime and fOldTime
	float   m_flScale;     // hud_scale->value
	float   m_flScaleRadar;     // hud_scale->value
	Vector	m_vecOrigin;
	Vector	m_vecAngles;
	int		m_iKeyBits;
	int		m_iHideHUDDisplay;
	int		m_iFOV;
	int		m_Teamplay;
	int		m_iRes;
	cvar_t *m_pCvarDraw;
	cvar_t *cl_shadows;
	cvar_t *fastsprites;
	cvar_t *cl_predict;
	cvar_t *cl_weapon_wallpuff;
	cvar_t *cl_weapon_sparks;
	cvar_t *zoom_sens_ratio;
	cvar_t *cl_lw;
	cvar_t *cl_righthand;
	cvar_t *cl_weather;
	cvar_t *cl_minmodels;
	cvar_t *cl_min_t;
	cvar_t *cl_min_ct;
	cvar_t *cl_gunsmoke;
cvar_t *m_csgohud;
cvar_t *m_pb_crosshair;
cvar_t *m_sniperhud;
cvar_t *m_bluewinann;
cvar_t *m_redwinann;
cvar_t *m_clearkill;
cvar_t *m_pbteam;
cvar_t *m_pbredclass;
cvar_t *m_pbblueclass;
cvar_t *m_spectatorgui;
cvar_t *m_respawnann;
cvar_t *m_laser;
cvar_t *m_grenadec;
cvar_t *m_killcmd1;
cvar_t *m_killcmd2;
cvar_t *m_killcmd3;
cvar_t *m_killcmd4;
cvar_t *m_headshot;
cvar_t *m_hspoint;
cvar_t *m_stopper;
cvar_t *m_chainheadshot;
cvar_t *m_helmet;
cvar_t *m_chainslugger;
cvar_t *m_pbhudvar;
cvar_t *m_hudevo;
cvar_t *m_annhs;
cvar_t *m_pointcmd;
cvar_t *m_animcmd;
cvar_t *m_iconbomb;

cvar_t *m_star1cmd;
cvar_t *m_star2cmd;
cvar_t *m_star3cmd;
cvar_t *m_star4cmd;
cvar_t *m_star5cmd;
cvar_t *m_star6cmd;
cvar_t *m_star7cmd;
cvar_t *m_star8cmd;
cvar_t *m_star9cmd;
cvar_t *m_star10cmd;

cvar_t *m_starpos;

cvar_t *m_disable_ek;

cvar_t *m_redccmd;


cvar_t *slugger_killed;
//

cvar_t *helmet_enable;
//

cvar_t *inventory_primary;
cvar_t *inventory_secondary;
cvar_t *inventory_melee;
cvar_t *inventory_explosive;
cvar_t *inventory_special;

cvar_t *weaponName;

cvar_t *enable_key_overlay;
cvar_t *enable_healthbar_overlay;

cvar_t *pb_mission;

cvar_t *item_QuickDeploy;
cvar_t *item_QuickReload;
cvar_t *item_MegaHp;
cvar_t *item_mask;
cvar_t *item_qrespawn;

cvar_t *bought_item_QuickDeploy;
cvar_t *bought_item_QuickReload;
cvar_t *bought_item_MegaHp;
cvar_t *bought_item_mask_1;
cvar_t *bought_item_mask_2;
cvar_t *bought_item_mask_3;
cvar_t *bought_item_mask_4;
cvar_t *bought_item_mask_5;
cvar_t *bought_item_mask_6;
cvar_t *bought_item_mask_7;
cvar_t *bought_item_mask_8;
cvar_t *bought_item_mask_9;
cvar_t *bought_item_mask_10;
cvar_t *bought_item_mask_11;
cvar_t *bought_item_mask_12;
cvar_t *bought_item_mask_13;
cvar_t *bought_item_qrespawn;

cvar_t *unit_item_QuickDeploy;
cvar_t *unit_item_QuickReload;
cvar_t *unit_item_MegaHp;
cvar_t *unit_item_mask_1;
cvar_t *unit_item_mask_2;
cvar_t *unit_item_mask_3;
cvar_t *unit_item_mask_4;
cvar_t *unit_item_mask_5;
cvar_t *unit_item_mask_6;
cvar_t *unit_item_mask_7;
cvar_t *unit_item_mask_8;
cvar_t *unit_item_mask_9;
cvar_t *unit_item_mask_10;
cvar_t *unit_item_mask_11;
cvar_t *unit_item_mask_12;
cvar_t *unit_item_mask_13;
cvar_t *unit_item_qrespawn;

cvar_t *custom_scope_cmd;

cvar_t *pb_new_hud;

cvar_t *hitmark_size;

	cvar_t *default_fov;
	cvar_t *hud_textmode;
	cvar_t *hud_colored;
	cvar_t *sv_skipshield;

	cvar_t *cl_headname;
#ifdef __ANDROID__
	cvar_t *cl_android_force_defaults;
#endif

	HSPRITE m_hGasPuff;

	int m_iFontHeight;

CHudHealth      m_Health;
CHudKillEffect m_KillEffect;
CHudInventoryUi m_InventoryUi;
CHudBackground m_Background;
	CHudAmmo        m_Ammo;
	CHudSpectator   m_Spectator;
	CHudGeiger      m_Geiger;
	CHudBattery	    m_Battery;
	CHudTrain       m_Train;
	CHudFlashlight  m_Flash;
	CHudMessage     m_Message;
	CHudStatusBar   m_StatusBar;
	CHudDeathNotice m_DeathNotice;
	CHudSayText     m_SayText;
	CHudMenu        m_Menu;
	CHudAmmoSecondary m_AmmoSecondary;
	CHudTextMessage m_TextMessage;
	CHudStatusIcons m_StatusIcons;
	CHudScoreboard  m_Scoreboard;
	CHudMOTD        m_MOTD;
	CHudMoney       m_Money;
	CHudTimer       m_Timer;
	CHudRadio       m_Radio;
	CHudProgressBar m_ProgressBar;
	CHudSniperScope m_SniperScope;
	CHudNVG         m_NVG;
	CHudRadar       m_Radar;
	CHudSpectatorGui m_SpectatorGui;
	CHudFollowIcon	m_FollowIcon;
	CHudScenarioStatus m_scenarioStatus;
	CHudHeadName	m_HeadName;
CHudHealthbar	m_HealthBar;
	CHudRetina		m_Retina;
	CHudZBS	m_ZBS;
	CHudZB2 m_ZB2;
	CHudZB3 m_ZB3;
	CHudMoeTouch m_MoeTouch;

CHudDamagePb m_DamagePb;
CHudDeathScreen m_DeathScreen;
CHudInventoryGive m_InventoryGive;
CHudMission_Announcement_Red m_Mission_Announcement_Red;
CHudMission_Announcement_Blue m_Mission_Announcement_Blue;

	CHudKeys m_Keys;

	// user messages
	CHudMsgFunc(Damage);
	CHudMsgFunc(GameMode);
	CHudMsgFunc(Logo);
	CHudMsgFunc(ResetHUD);
	CHudMsgFunc(InitHUD);
	CHudMsgFunc(ViewMode);
	CHudMsgFunc(SetFOV);
	CHudMsgFunc(Concuss);
	CHudMsgFunc(ShadowIdx);

	// Screen information
	SCREENINFO	m_scrinfo;
	// As Xash3D can fake m_scrinfo for hud scailing
	// we will use a real screen parameters
	SCREENINFO  m_truescrinfo;

	int	m_iWeaponBits;
	int	m_fPlayerDead;
	int m_iIntermission;
	int m_iNoConsolePrint;
bool m_bMordenRadar;
bool hideRadarScore;
bool hideRadar;

bool mass_kill;
bool piercing_shot;
bool slugger_kill;
bool bomb_kill;
bool delay_kill;

bool special_gunner;
bool bomb_shot;
bool one_shot;
bool helmet_on;

bool reddot_scope;
bool disable_scope;
//key
bool key_tab;
bool key_change;

float slugger_count;

bool Announcement_Red;
bool Announcement_Blue;

bool respawning;

bool megahp;

bool mKill1;
bool mKill2;
bool mKill3;
bool mKill4;
bool mKill5;
bool mKill6;
bool mKill7;
bool mKill8;
bool mKill9;
bool mKill10;

bool pShot1;
bool pShot2;
bool pShot3;
bool pShot4;
bool pShot5;
bool pShot6;
bool pShot7;
bool pShot8;
bool pShot9;
bool pShot10;

bool display_hb;

	// sprite indexes
	int m_HUD_number_0;
	int m_HUD_number_small_0;
	int m_HUD_round_0;

	char m_szServerName[64];

	GameMode_e m_iModRunning;

private:
	HUDLIST	*m_pHudList;
	HSPRITE	m_hsprLogo;
	int	m_iLogo;
	client_sprite_t	*m_pSpriteList;
	int	m_iSpriteCount;
	int	m_iSpriteCountAllRes;
	float m_flMouseSensitivity;
	int	m_iConcussionEffect;
	int	m_iForceCamera;
	int m_iForceChaseCam;
	int m_iFadeToBlack;
	bool m_bIsCZero;

	// the memory for these arrays are allocated in the first call to CHud::VidInit(), when the hud.txt and associated sprites are loaded.
	// freed in ~CHud()
	HSPRITE *m_rghSprites;	/*[HUD_SPRITE_COUNT]*/			// the sprites loaded from hud.txt
	wrect_t *m_rgrcRects;	/*[HUD_SPRITE_COUNT]*/
	char *m_rgszSpriteNames; /*[HUD_SPRITE_COUNT][MAX_SPRITE_NAME_LENGTH]*/
};

extern CHud gHUD;
extern cvar_t *sensitivity;

extern int g_iTeamNumber;
extern int g_iUser1;
extern int g_iUser2;
extern int g_iUser3;

extern cvar_t *mission_kill;
extern cvar_t *mission_doublekill;
extern cvar_t *mission_triplekill;
extern cvar_t *mission_chainkiller;
extern cvar_t *mission_headshot;
extern cvar_t *mission_chainheadshot;
extern cvar_t *mission_slugger;
extern cvar_t *mission_masskill;
extern cvar_t *mission_piercingshot;
extern cvar_t *pb_point;
extern cvar_t *pb_qc_enable;
