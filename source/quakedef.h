/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// quakedef.h -- primary header for client

#define qtrue 1
#define qfalse 0

#define	QUAKE_GAME			// as opposed to utilities

//
// MACRO FEATURE TOGGLING
//
#define OPT_STATICLIGHT 	// motolegacy -- use a static light level for models
#define OPT_NOLIGHTSTYLES	// motolegacy -- disable use of lightstyles, always on
#define OPT_WORSEHUNKDEBUG	// motolegacy -- removes 'name' from hunk and cache, useful for low memory systems.
#define OPT_FIXEDPOINT 		// FW: enable fixed-point optimizations

/* Fixed-point optimizations, thanks to Pocket Quake and Dan East. */
#ifdef OPT_FIXEDPOINT
#define USE_PQ_OPT
#define USE_PQ_OPT1
#define USE_PQ_OPT2
//#define USE_PQ_OPT3 // don't use
#define USE_PQ_OPT4
#define USE_PQ_OPT5
#endif


#undef VERSION
#define	VERSION				1.09
#define	GLQUAKE_VERSION		1.00
#define	D3DQUAKE_VERSION	0.01
#define	WINQUAKE_VERSION	0.996
#define	LINUX_VERSION		1.30
#define	X11_VERSION			1.10

//define	PARANOID			// speed sapping error checking

#define	GAMENAME	"nzp"

#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdbool.h>
#include <ctype.h>

#if id386
#define UNALIGNED_OK	1	// set to 0 if unaligned accesses are not supported
#else
#define UNALIGNED_OK	0
#endif

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
#define CACHE_SIZE	32		// used to align key data structures

#define UNUSED(x)	(x = x)	// for pesky compiler / lint warnings

#define	MINIMUM_MEMORY			0x550000
#define	MINIMUM_MEMORY_LEVELPAK	(MINIMUM_MEMORY + 0x100000)

#define MAX_NUM_ARGVS	50

// up / down
#define	PITCH	0

// left / right
#define	YAW		1

// fall over
#define	ROLL	2


#define	MAX_QPATH		64			// max length of a quake game pathname
#define	MAX_OSPATH		128			// max length of a filesystem pathname

#define	ON_EPSILON		0.1			// point on plane side epsilon

#define	MAX_MSGLEN		8000		// max length of a reliable message
#define	MAX_DATAGRAM	2048		// max length of unreliable message

//
// per-level limits
//
#define	MAX_EDICTS		600			// FIXME: ouch! ouch! ouch!
#define	MAX_LIGHTSTYLES	64
#define	MAX_MODELS		256			// these are sent over the net as bytes
#define	MAX_SOUNDS		256			// so they cannot be blindly increased

#define	SAVEGAME_COMMENT_LENGTH	39

#define	MAX_STYLESTRING	64

//
// stats are integers communicated to the client by the server
//
#define	MAX_CL_STATS		32
#define	STAT_HEALTH			0
#define	STAT_points			1
#define	STAT_WEAPON			2
#define	STAT_AMMO			3
#define	STAT_SECGRENADES	4
#define	STAT_WEAPONFRAME	5
#define	STAT_CURRENTMAG		6
#define	STAT_ZOOM			7
#define	STAT_WEAPONSKIN		8
#define	STAT_GRENADES		9
#define	STAT_ACTIVEWEAPON	10
#define	STAT_ROUNDS			11
#define	STAT_ROUNDCHANGE	12
#define	STAT_X2				13
#define	STAT_INSTA			14
#define	STAT_PRIGRENADES	15
#define	STAT_WEAPON2		17
#define	STAT_WEAPON2SKIN	18
#define	STAT_WEAPON2FRAME	19
#define STAT_CURRENTMAG2 	20

// stock defines

#define W_COLT 		1
#define W_KAR 		2
#define W_THOMPSON 	3
#define W_357		4
#define W_BAR		5
#define W_BK		6
#define W_BROWNING	7
#define W_DB		8
#define W_FG		9
#define W_GEWEHR	10
#define W_KAR_SCOPE	11
#define W_M1		12
#define W_M1A1		13
#define W_M2		14
#define W_MP40		15
#define W_MG		16
#define W_PANZER	17
#define W_PPSH		18
#define W_PTRS		19
#define W_RAY		20
#define W_SAWNOFF	21
#define W_STG		22
#define W_TRENCH	23
#define W_TYPE		24

#define W_BIATCH  28
#define W_KILLU   29 //357
#define W_COMPRESSOR 30 // Gewehr
#define W_M1000  31 //garand
#define W_KOLLIDER  32 // mp5
#define W_PORTER  33 // Ray
#define W_WIDDER  34 // M1A1
#define W_FIW  35 //upgraded flamethrower
#define W_ARMAGEDDON  36 //Kar
//#define W_WUNDER  37
#define W_GIBS  38 // thompson
#define W_SAMURAI  39 //Type
#define W_AFTERBURNER  40 //mp40
#define W_SPATZ  41 // stg
#define W_SNUFF  42 // sawn off
#define W_BORE  43 // double barrel
#define W_IMPELLER  44 //fg
#define W_BARRACUDA  45 //mg42
#define W_ACCELERATOR  46 //M1919 browning
#define W_GUT  47 //trench
#define W_REAPER  48 //ppsh
#define W_HEADCRACKER  49 //scoped kar
#define W_LONGINUS  50 //panzer
#define W_PENETRATOR  51 //ptrs
#define W_WIDOW  52 //bar
//#define W_KRAUS  53 //ballistic
#define W_MP5   54
#define W_M14   55

#define W_TESLA  56
#define W_DG3 	 57 //tesla

#define W_NOWEP   420

// stock defines

#define	IT_SHOTGUN				1
#define	IT_SUPER_SHOTGUN		2
#define	IT_NAILGUN				4
#define	IT_SUPER_NAILGUN		8
#define	IT_GRENADE_LAUNCHER		16
#define	IT_ROCKET_LAUNCHER		32
#define	IT_LIGHTNING			64
#define IT_SUPER_LIGHTNING      128
#define IT_SHELLS               256
#define IT_NAILS                512
#define IT_ROCKETS              1024
#define IT_CELLS                2048
#define IT_AXE                  4096
#define IT_ARMOR1               8192
#define IT_ARMOR2               16384
#define IT_ARMOR3               32768
#define IT_SUPERHEALTH          65536
#define IT_KEY1                 131072
#define IT_KEY2                 262144
#define	IT_INVISIBILITY			524288
#define	IT_INVULNERABILITY		1048576
#define	IT_SUIT					2097152
#define	IT_QUAD					4194304
#define IT_SIGIL1               (1<<28)
#define IT_SIGIL2               (1<<29)
#define IT_SIGIL3               (1<<30)
#define IT_SIGIL4               (1<<31)

//===========================================
//rogue changed and added defines

#define RIT_SHELLS              128
#define RIT_NAILS               256
#define RIT_ROCKETS             512
#define RIT_CELLS               1024
#define RIT_AXE                 2048
#define RIT_LAVA_NAILGUN        4096
#define RIT_LAVA_SUPER_NAILGUN  8192
#define RIT_MULTI_GRENADE       16384
#define RIT_MULTI_ROCKET        32768
#define RIT_PLASMA_GUN          65536
#define RIT_ARMOR1              8388608
#define RIT_ARMOR2              16777216
#define RIT_ARMOR3              33554432
#define RIT_LAVA_NAILS          67108864
#define RIT_PLASMA_AMMO         134217728
#define RIT_MULTI_ROCKETS       268435456
#define RIT_SHIELD              536870912
#define RIT_ANTIGRAV            1073741824
#define RIT_SUPERHEALTH         2147483648

//MED 01/04/97 added hipnotic defines
//===========================================
//hipnotic added defines
#define HIT_PROXIMITY_GUN_BIT 16
#define HIT_MJOLNIR_BIT       7
#define HIT_LASER_CANNON_BIT  23
#define HIT_PROXIMITY_GUN   (1<<HIT_PROXIMITY_GUN_BIT)
#define HIT_MJOLNIR         (1<<HIT_MJOLNIR_BIT)
#define HIT_LASER_CANNON    (1<<HIT_LASER_CANNON_BIT)
#define HIT_WETSUIT         (1<<(23+2))
#define HIT_EMPATHY_SHIELDS (1<<(23+3))

//===========================================

#define	MAX_SCOREBOARD		16
#define	MAX_SCOREBOARDNAME	32

#define	SOUND_CHANNELS		8

// This makes anyone on id's net privileged
// Use for multiplayer testing only - VERY dangerous!!!
// #define IDGODS

#include "common.h"
#include "bspfile.h"
#include "vid.h"
#include "sys.h"
#include "zone.h"
#include "mathlib.h"

typedef struct
{
	vec3_t	origin;
	vec3_t	angles;
	unsigned short 	modelindex; //johnfitz -- was int
	unsigned short 	frame; //johnfitz -- was int
	unsigned char 	colormap; //johnfitz -- was int
	unsigned char 	skin; //johnfitz -- was int
	int		effects;
} entity_state_t;


#include "wad.h"
#include "draw.h"
#include "cvar.h"
#include "screen.h"
#include "net.h"
#include "protocol.h"
#include "cmd.h"
#include "sbar.h"
#include "sound.h"
#include "render.h"
#include "client.h"
#include "progs.h"
#include "server.h"

#include "model.h"
#include "d_iface.h"

#include "input.h"
#include "world.h"
#include "keys.h"
#include "console.h"
#include "view.h"
#include "menu.h"
#include "crc.h"
#include "cdaudio.h"

#include "cl_hud.h"


//=============================================================================

// the host system specifies the base of the directory tree, the
// command line parms passed to the program, and the amount of memory
// available for the program to use

typedef struct
{
	char	*basedir;
	char	*cachedir;		// for development over ISDN lines
	int		argc;
	char	**argv;
	void	*membase;
	int		memsize;
} quakeparms_t;


//=============================================================================



extern qboolean noclip_anglehack;


//
// host
//
extern	quakeparms_t host_parms;

extern	cvar_t		sys_ticrate;
extern	cvar_t		sys_nostdout;
extern	cvar_t		developer;

extern	qboolean	host_initialized;		// true if into command execution
extern	double		host_frametime;
extern	byte		*host_basepal;
extern	byte		*host_colormap;
extern	int			host_framecount;	// incremented every frame, never reset
extern	double		realtime;			// not bounded in any way, changed at
										// start of every frame, never reset

void Host_ClearMemory (void);
void Host_ServerFrame (void);
void Host_InitCommands (void);
void Host_Init (quakeparms_t *parms);
void Host_Shutdown(void);
void Host_Error (char *error, ...);
void Host_EndGame (char *message, ...);
void Host_Frame (float time);
void Host_Quit_f (void);
void Host_ClientCommands (char *fmt, ...);
void Host_ShutdownServer (qboolean crash);

extern qboolean		msg_suppress_1;		// suppresses resolution and cache size console output
										//  an fullscreen DIB focus gain/loss
extern int			current_skill;		// skill level for currently loaded level (in case
										//  the user changes the cvar while the level is
										//  running, this reflects the level actually in use)

extern qboolean		isDedicated;

extern int			minimum_memory;

//
// chase
//
extern	cvar_t	chase_active;

void Chase_Init (void);
void Chase_Reset (void);
void Chase_Update (void);

//ZOMBIE AI STUFF
#define MAX_WAYPOINTS 256 //max waypoints
typedef struct
{
	int pathlist [MAX_WAYPOINTS];
	int zombienum;
} zombie_ai;

typedef struct
{
	vec3_t origin;
	int id;
	float g_score, f_score;
	int open; // Determine if the waypoint is "open" a.k.a avaible
	int target_id [8]; // Targets array number
	char special[64]; //special tag is required for the closed waypoints
	int target [8]; //Each waypoint can have up to 8 targets
	float dist [8]; // Distance to the next waypoints
	int came_from; // Used for pathfinding store where we got here to this
	qboolean used; //if the waypoint is in use
} waypoint_ai;

extern waypoint_ai waypoints[MAX_WAYPOINTS];


extern func_t	EndFrame;

// naievil -- texture conversion start 
#define MAX_SINGLE_PLANE_PIXEL_SIZE 		512*512*1 		// naievil -- 512 x 512 single plane (paletted) texture
extern byte converted_pixels[MAX_SINGLE_PLANE_PIXEL_SIZE]; 
extern byte temp_pixel_storage_pixels[MAX_SINGLE_PLANE_PIXEL_SIZE*4]; // naievil -- rgba storage for max pic size 
// naievil -- texture conversion end