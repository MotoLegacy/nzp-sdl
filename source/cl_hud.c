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
// cl_hud.c -- status bar code

// FIXME: we're wasting tons of fucking time with this Draw_CachePic spam lol

#include "quakedef.h"

char		sb_round[5][32];
char		sb_round_num[10][32];

// sigh..
#define 	sb_moneyback 	Draw_CachePic("gfx/hud/moneyback")

#define 	instapic 		Draw_CachePic("gfx/hud/in_kill")
#define 	x2pic 			Draw_CachePic("gfx/hud/2x")

#define 	revivepic 		Draw_CachePic("gfx/hud/revive")
#define 	jugpic 			Draw_CachePic("gfx/hud/jug")
#define 	floppic 		Draw_CachePic("gfx/hud/flopper")
#define 	staminpic 		Draw_CachePic("gfx/hud/stamin")
#define 	doublepic 		Draw_CachePic("gfx/hud/double")
#define 	speedpic 		Draw_CachePic("gfx/hud/speed")
#define 	deadpic 		Draw_CachePic("gfx/hud/dead")
#define 	mulepic 		Draw_CachePic("gfx/hud/mule")

#define 	fragpic 		Draw_CachePic("gfx/hud/frag")
#define 	bettypic 		Draw_CachePic("gfx/hud/betty")

// AAHHHH
char 		*b_leftbutton;
char 		*b_rightbutton;
char 		*b_centerbutton;
char 		*b_downbutton;
char 		*b_upbutton;

// not gonna touch em since they arent being used anyway tbh
#ifdef GFX_GOOD_BLOOD
char      *fx_blood_lu;
char      *fx_blood_ru;
char      *fx_blood_ld;
char      *fx_blood_rd;
#endif // GFX_GOOD_BLOOD

qboolean	sb_showscores;
qboolean 	domaxammo;

int  x_value, y_value;

void M_DrawPic (int x, int y, qpic_t *pic);

double HUD_Change_time;//hide hud when not chagned

extern cvar_t waypoint_mode;


int old_points;
int current_points;
int point_change_interval;
int point_change_interval_neg;
int alphabling = 0;
float round_center_x;
float round_center_y;

typedef struct
{
	int points;
	int negative;
	float x;
	float y;
	float move_x;
	float move_y;
	double alive_time;
} point_change_t;

point_change_t point_change[10];

/*
===============
HUD_Init
===============
*/
void HUD_Init (void)
{
	strcpy(sb_round[0], "gfx/hud/r1");
	strcpy(sb_round[1], "gfx/hud/r2");
	strcpy(sb_round[2], "gfx/hud/r3");
	strcpy(sb_round[3], "gfx/hud/r4");
	strcpy(sb_round[4], "gfx/hud/r5");


	strcpy(sb_round_num[0], "gfx/hud/r_num0");
	strcpy(sb_round_num[1], "gfx/hud/r_num1");
	strcpy(sb_round_num[2], "gfx/hud/r_num2");
	strcpy(sb_round_num[3], "gfx/hud/r_num3");
	strcpy(sb_round_num[4], "gfx/hud/r_num4");
	strcpy(sb_round_num[5], "gfx/hud/r_num5");
	strcpy(sb_round_num[6], "gfx/hud/r_num6");
	strcpy(sb_round_num[7], "gfx/hud/r_num7");
	strcpy(sb_round_num[8], "gfx/hud/r_num8");
	strcpy(sb_round_num[9], "gfx/hud/r_num9");

#ifdef GFX_GOOD_BLOOD
    fx_blood_lu = "gfx/hud/blood";
#endif // GFX_GOOD_BLOOD

    // naievil -- fixme
	//Achievement_Init();
}

extern char *hitmark;

#define PAL_STANDARD		0
#define PAL_WHITETORED 		1
#define PAL_WHITETOYELLOW	2

void HUD_CacheData(void)
{
	Con_Printf("HUD_CacheData: Caching .TGA images\n");

	for (int i = 0; i < 5; i++) {
		Draw_CachePic(sb_round[i]);
	}

	for (int i = 0; i < 10; i++) {
		Draw_CachePic(sb_round_num[i]);
	}

	// illusion kinda falls apart here but oh well
	// give em a first cache
	sb_moneyback;

	instapic;
	x2pic;

	revivepic;
	jugpic;
	floppic;
	staminpic;
	doublepic;
	speedpic;
	deadpic;
	mulepic;

	fragpic;
	bettypic;

	Draw_CachePic("gfx/butticons/facebt_left");
	Draw_CachePic("gfx/butticons/facebt_right");
	Draw_CachePic("gfx/butticons/facebt_center");
	Draw_CachePic("gfx/butticons/facebt_down");
	Draw_CachePic("gfx/butticons/facebt_up");


	// FUCK YOU!!!!
#ifdef GFX_GOOD_BLOOD
	Draw_CachePic(fx_blood_lu);
#endif // GFX_GOOD_BLOOD

	Draw_CachePic(hitmark);
}

/*
===============
HUD_NewMap
===============
*/
void HUD_NewMap (void)
{
	int i;
	alphabling = 0;

	for (i=0 ; i<10 ; i++)
	{
		point_change[i].points = 0;
		point_change[i].negative = 0;
		point_change[i].x = 0.0;
		point_change[i].y = 0.0;
		point_change[i].move_x = 0.0;
		point_change[i].move_y = 0.0;
		point_change[i].alive_time = 0.0;
	}

	old_points = 500;
	current_points = 500;
	point_change_interval = 0;
	point_change_interval_neg = 0;

	// moto -- before this used draw_cachepic for dimensions which fucked up
	// using palette hacks
	round_center_x = (vid.width/2 - (11)/2);
	round_center_y = (vid.width/2 - (48)/2);

	HUD_CacheData(); // naievil -- this is used to put stuff on cache during a new map
}


/*
=============
HUD_itoa
=============
*/
int HUD_itoa (int num, char *buf)
{
	char	*str;
	int		pow10;
	int		dig;

	str = buf;

	if (num < 0)
	{
		*str++ = '-';
		num = -num;
	}

	for (pow10 = 10 ; num >= pow10 ; pow10 *= 10)
	;

	do
	{
		pow10 /= 10;
		dig = num/pow10;
		*str++ = '0'+dig;
		num -= dig*pow10;
	} while (pow10 != 1);

	*str = 0;

	return str-buf;
}


//=============================================================================

int		pointsort[MAX_SCOREBOARD];

char	scoreboardtext[MAX_SCOREBOARD][20];
int		scoreboardtop[MAX_SCOREBOARD];
int		scoreboardbottom[MAX_SCOREBOARD];
int		scoreboardcount[MAX_SCOREBOARD];
int		scoreboardlines;

/*
===============
HUD_Sorpoints
===============
*/
void HUD_Sortpoints (void)
{
	int		i, j, k;

// sort by points
	scoreboardlines = 0;
	for (i=0 ; i<cl.maxclients ; i++)
	{
		if (cl.scores[i].name[0])
		{
			pointsort[scoreboardlines] = i;
			scoreboardlines++;
		}
	}

	for (i=0 ; i<scoreboardlines ; i++)
		for (j=0 ; j<scoreboardlines-1-i ; j++)
			if (cl.scores[pointsort[j]].points < cl.scores[pointsort[j+1]].points)
			{
				k = pointsort[j];
				pointsort[j] = pointsort[j+1];
				pointsort[j+1] = k;
			}
}

/*
===============
HUD_EndScreen
===============
*/
void HUD_EndScreen (void)
{
	scoreboard_t	*s;
	char			str[80];
	int				i, k, l;
	int				y, x, d;

	HUD_Sortpoints ();

	l = scoreboardlines;

	Draw_String((vid.width - 9*8)/2, 40, "GAME OVER");

	sprintf (str,"You survived %3i rounds", cl.stats[STAT_ROUNDS]);
	Draw_String((vid.width - strlen (str)*8)/2, 52, str);

	sprintf (str,"Name           Kills     Points");
	x = (vid.width - strlen (str)*8)/2;

	Draw_String (x, 68, str);
	y = 0;
	for (i=0; i<l ; i++)
	{
		k = pointsort[i];
		s = &cl.scores[k];
		if (!s->name[0])
			continue;

		Draw_String (x, 78 + y, s->name);

		d = strlen (va("%i",s->kills));
		Draw_String (x + (20 - d)*8, 78 + y, va("%i",s->kills));

		d = strlen (va("%i",s->points));
		Draw_String (x + (31 - d)*8, 78 + y, va("%i",s->points));
		y += 10;
	}

}

//=============================================================================

  //=============================================================================//
 //===============================DRAW FUNCTIONS================================//
//=============================================================================//

/*
==================
HUD_Points

==================
*/


void HUD_Parse_Point_Change (int points, int negative, int x_start, int y_start)
{
	int i, f;
	char str[10];
	i=9;
	while (i>0)
	{
		point_change[i] = point_change[i - 1];
		i--;
	}

	point_change[i].points = points;
	point_change[i].negative = negative;

	f = HUD_itoa (points, str);
	point_change[i].x = x_start + 10.0 + 8.0*f;
	point_change[i].y = y_start;
	point_change[i].move_x = 1.0;
	point_change[i].move_y = ((rand ()&0x7fff) / ((float)0x7fff)) - 0.5;

	point_change[i].alive_time = Sys_FloatTime() + 0.4;
}

void HUD_Points (void)
{
	int				i, k, l;
	int				x, y, f, xplus;
	scoreboard_t	*s;
	char str[12];

// scores
	HUD_Sortpoints ();

// draw the text
	l = scoreboardlines;


    x = 5;
    y = 167;
	for (i=0 ; i<l ; i++)
	{
		k = pointsort[i];
		s = &cl.scores[k];
		if (!s->name[0])
			continue;

	// draw background

	// draw number
		f = s->points;
		if (f > current_points)
		{
			point_change_interval_neg = 0;
			if (!point_change_interval)
			{
				point_change_interval = (int)(f - old_points)/55;;
			}
			current_points = old_points + point_change_interval;
			if (f < current_points)
			{
				current_points = f;
				point_change_interval = 0;
			}
		}
		else if (f < current_points)
		{
			point_change_interval = 0;
			if (!point_change_interval_neg)
			{
				point_change_interval_neg = (int)(old_points - f)/55;
			}
			current_points = old_points - point_change_interval_neg;
			if (f > current_points)
			{
				current_points = f;
				point_change_interval_neg = 0;
			}
		}
		Draw_AdvancedPic(x, y, sb_moneyback, 255, PAL_STANDARD);
		xplus = strlen(va("%i", current_points))*8;

		Draw_String (((64 - xplus)/2)+5, y + 3, va("%i", current_points));

		if (old_points != f)
		{
			if (f > old_points)
				HUD_Parse_Point_Change(f - old_points, 0, ((64 - xplus)/2)+5, y + 3);
			else
				HUD_Parse_Point_Change(old_points - f, 1, ((64 - xplus)/2)+5, y + 3);

			old_points = f;
		}



		y += 10;
	}
}


/*
==================
HUD_Point_Change

==================
*/
void HUD_Point_Change (void)
{
	int	i;

	for (i=0 ; i<10 ; i++)
	{
		if (point_change[i].points)
		{
			if (point_change[i].negative)
				Draw_AdvancedString((int)point_change[i].x, (int)point_change[i].y, va ("-%i", point_change[i].points), 255, PAL_WHITETORED);
			else
				Draw_AdvancedString((int)point_change[i].x, (int)point_change[i].y, va ("+%i", point_change[i].points), 255, PAL_WHITETOYELLOW);
			point_change[i].y = point_change[i].y + point_change[i].move_y;
			point_change[i].x = point_change[i].x + point_change[i].move_x;
			if (point_change[i].alive_time && point_change[i].alive_time < Sys_FloatTime())
			{
				point_change[i].points = 0;
				point_change[i].negative = 0;
				point_change[i].x = 0.0;
				point_change[i].y = 0.0;
				point_change[i].move_x = 0.0;
				point_change[i].move_y = 0.0;
				point_change[i].alive_time = 0.0;
			}
		}
	}
}

/*
==================
HUD_Blood

==================
*/
void HUD_Blood (void)
{
#ifdef GFX_GOOD_BLOOD
	float alpha;
	//blubswillrule:
	//this function scales linearly from health = 0 to health = 100
	//alpha = (100.0 - (float)cl.stats[STAT_HEALTH])/100*255;
	//but we want the picture to be fully visible at health = 20, so use this function instead
	alpha = (100.0 - ((1.25 * (float) cl.stats[STAT_HEALTH]) - 25))/100*255;
	
    if (alpha <= 0.0)
        return;
    
    float modifier = (sin(cl.time * 10) * 20) - 20;//always negative

    if(modifier < -35.0)
	modifier = -35.0;
    
    alpha += modifier;
    
    if(alpha < 0.0)
	    return;
    
    Draw_AdvancedPic(0, 0, Draw_CachePic(fx_blood_lu), alpha, PAL_STANDARD);
#else
	// First Ring
	if (cl.stats[STAT_HEALTH] <= 75) {
		Draw_Fill(0, 0, vid.width, 6, 247); // top
		Draw_Fill(0, 0, 6, vid.height, 247); // left
		Draw_Fill(vid.width - 6, 0, 6, vid.height, 247); // right
		Draw_Fill(0, vid.height - 6, vid.width, 6, 247); // bottom
	}
	// Second Ring
	if (cl.stats[STAT_HEALTH] <= 50) {
		Draw_Fill(6, 6, vid.width - 12, 3, 248); // top
		Draw_Fill(6, 6, 3, vid.height - 12, 248); // left
		Draw_Fill(vid.width - 9, 6, 3, vid.height - 12, 248); // right
		Draw_Fill(6, vid.height - 9, vid.width - 12, 3, 248); // bottom
	}
	if (cl.stats[STAT_HEALTH] <= 20 && cl.stats[STAT_HEALTH] != -10) {
		Draw_Fill(9, 9, vid.width - 18, 2, 249); // top
		Draw_Fill(9, 9, 2, vid.height - 18, 249); // left
		Draw_Fill(vid.width - 11, 9, 2, vid.height - 18, 249); // right
		Draw_Fill(9, vid.height - 11, vid.width - 18, 2, 249); // bottom
	}
#endif // GFX_GOOD_BLOOD
}

/*
===============
HUD_GetWorldText
===============
*/

// modified from scatter's worldspawn parser
// FIXME - unoptimized, could probably save a bit of
// memory here in the future.
void HUD_WorldText(int alpha)
{
	// for parser
	char key[128], value[4096];
	char *data;

	// first, parse worldspawn
	data = COM_Parse(cl.worldmodel->entities);

	if (!data)
		return; // err
	if (com_token[0] != '{')
		return; // err

	while(1) {
		data = COM_Parse(data);

		if (!data)
			return; // err
		if (com_token[0] == '}')
			break; // end of worldspawn
		
		if (com_token[0] == '_')
			strcpy(key, com_token + 1);
		else
			strcpy(key, com_token);
		
		while (key[strlen(key)-1] == ' ') // remove trailing spaces
			key[strlen(key)-1] = 0;
		
		data = COM_Parse(data);
		if (!data)
			return; // err

		strcpy(value, com_token);

		if (!strcmp("location", key)) // search for location key
		{
			Draw_String(4, vid.height/2 + 16, value);
		}
		if (!strcmp("date", key)) // search for date key
		{
			Draw_String(4, vid.height/2 + 26, value);
		}
		if (!strcmp("person", key)) // search for person key
		{
			Draw_String(4, vid.height/2 + 36, value);
		}
	}
}

/*
===============
HUD_MaxAmmo
===============
*/
int maxammoy;
int maxammoopac;

void HUD_MaxAmmo(void)
{
	maxammoy -= cl.time * 0.003;
	maxammoopac -= 5;

	Draw_String(vid.width/2 - strlen("MAX AMMO!")*2, maxammoy, "MAX AMMO!");

	if (maxammoopac <= 0) {
		domaxammo = false;
	}
}

/*
===============
HUD_Rounds
===============
*/

float 	color_shift[3];
float 	color_shift_end[3];
float 	color_shift_steps[3];
int		color_shift_init;
int 	red_to_white_alpha;
int 	blinking;
int 	textstate;
int 	value, value2;

int 	reallydumbvalue;
int 	f222;
int 	maxammoy;
int 	maxammoopac;

void HUD_Rounds (void)
{
	int i, x_offset, icon_num, savex;
	int num[3];
	x_offset = 0;
	savex = 0;

	// Round and Title text - moto
	// extra creds to scatterbox for some x/y vals
	// ------------------
	// First, fade from white to red, ~3s duration
	if (!textstate) {
		if (!value) {
			red_to_white_alpha = 255;
			value = 255;
		}

		Draw_String(vid.width/2 - (strlen("Round")*8/2), 80, "Round");
		
		value -= cl.time * 0.4;

		// prep values for next stage
		if (value <= 0) {
			value = 255;
			value2 = 0;
			textstate = 1;
		}
	} 
	// Now, fade out, and start fading worldtext in
	// ~3s for fade out, 
	else if (textstate == 1) {
		Draw_AdvancedString(vid.width/2 - (strlen("Round")*8/2), 80, "Round", value, PAL_WHITETORED);

		HUD_WorldText(value2);
		Draw_String(4, vid.height/2 + 6, "'Nazi Zombies'");
		
		value -= cl.time * 0.4;
		value2 += cl.time * 0.4;

		// prep values for next stage
		if (value <= 0) {
			value2 = 0;
			textstate = 2;
		}
	}
	// Hold world text for a few seconds
	else if (textstate == 2) {
		HUD_WorldText(255);
		Draw_String(4, vid.height/2 + 6, "'Nazi Zombies'");

		value2 += cl.time * 0.4;

		if (value2 >= 255) {
			value2 = 255;
			textstate = 3;
		}
	}
	// Fade worldtext out, finally.
	else if (textstate == 3) {
		HUD_WorldText(value2);
		Draw_String(4, vid.height/2 + 6, "'Nazi Zombies'");

		value2 -= cl.time * 0.4;

		// prep values for next stage
		if (value2 <= 0) {
			textstate = -1;
		}
	}
	// ------------------
	// End Round and Title text - moto

	if (cl.stats[STAT_ROUNDCHANGE] == 1)//this is the rounds icon at the middle of the screen
	{
		if (textstate == -1) {
			value = 0;
			value2 = 0;
			textstate = 0;
		}

		Draw_AdvancedPic((vid.width - Draw_CachePic(sb_round[0])->width) /2, (vid.height - Draw_CachePic(sb_round[0])->height) /2, Draw_CachePic(sb_round[0]), 255, PAL_WHITETORED);

		alphabling = alphabling + 15;

		if (alphabling < 0)
			alphabling = 0;
		else if (alphabling > 255)
			alphabling = 255;
	}
	else if (cl.stats[STAT_ROUNDCHANGE] == 2)//this is the rounds icon moving from middle
	{
		Draw_AdvancedPic((int)round_center_x, (int)round_center_y, Draw_CachePic(sb_round[0]), 255, PAL_WHITETORED);
		round_center_x = round_center_x - (320/110);
		round_center_y = round_center_y + 1.4;
		if (round_center_x <= 5)
			round_center_x = 5;
		if (round_center_y >= vid.height - Draw_CachePic(sb_round[0])->height)
			round_center_y = vid.height - Draw_CachePic(sb_round[0])->height;
	}
	else if (cl.stats[STAT_ROUNDCHANGE] == 3)//shift to white
	{
		if (red_to_white_alpha > 0)
			red_to_white_alpha -= cl.time * 0.4;
		else
			red_to_white_alpha = 0;

		if (cl.stats[STAT_ROUNDS] > 0 && cl.stats[STAT_ROUNDS] < 11)
		{

			for (i = 0; i < cl.stats[STAT_ROUNDS]; i++)
			{
				if (i == 4)
				{
					Draw_AdvancedPic(5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, PAL_STANDARD);
					Draw_AdvancedPic(5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), red_to_white_alpha, PAL_WHITETORED);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_AdvancedPic(5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, PAL_STANDARD);
					Draw_AdvancedPic(5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), red_to_white_alpha, PAL_WHITETORED);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_AdvancedPic(5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), 255, PAL_STANDARD);
				Draw_AdvancedPic(5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), red_to_white_alpha, PAL_WHITETORED);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), 255, PAL_STANDARD);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), red_to_white_alpha, PAL_WHITETORED);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), 255, PAL_STANDARD);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), red_to_white_alpha, PAL_WHITETORED);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), 255, PAL_STANDARD);
			Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), red_to_white_alpha, PAL_WHITETORED);
			x_offset = x_offset + Draw_CachePic(sb_round_num[num[0]])->width - 8;
		}
	}
	else if (cl.stats[STAT_ROUNDCHANGE] == 4)//blink white
	{
		blinking = ((int)(realtime*1000)&510) - 255;
		blinking = abs(blinking);
		if (cl.stats[STAT_ROUNDS] > 0 && cl.stats[STAT_ROUNDS] < 11)
		{
			for (i = 0; i < cl.stats[STAT_ROUNDS]; i++)
			{
				if (i == 4)
				{
					Draw_AdvancedPic(5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), blinking, PAL_STANDARD);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_AdvancedPic(5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), blinking, PAL_STANDARD);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_AdvancedPic(5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), blinking, PAL_STANDARD);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), blinking, PAL_STANDARD);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), blinking, PAL_STANDARD);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), blinking, PAL_STANDARD);
			x_offset = x_offset + Draw_CachePic(sb_round_num[num[0]])->width - 8;
		}
	}
	else if (cl.stats[STAT_ROUNDCHANGE] == 5)//blink white
	{
		if (blinking > 0)
			blinking = blinking - 10;
		if (blinking < 0)
			blinking = 0;
		if (cl.stats[STAT_ROUNDS] > 0 && cl.stats[STAT_ROUNDS] < 11)
		{
			for (i = 0; i < cl.stats[STAT_ROUNDS]; i++)
			{
				if (i == 4)
				{
					Draw_AdvancedPic(5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), blinking, PAL_STANDARD);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_AdvancedPic(5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), blinking, PAL_STANDARD);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_AdvancedPic(5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), blinking, PAL_STANDARD);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), blinking, PAL_STANDARD);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), blinking, PAL_STANDARD);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), blinking, PAL_STANDARD);
			x_offset = x_offset + Draw_CachePic(sb_round_num[num[0]])->width - 8;
		}
	}
	else if (cl.stats[STAT_ROUNDCHANGE] == 6)//blink white while fading back
	{
		color_shift_init = 0;
		blinking = ((int)(realtime*1000)&510) - 255;
		blinking = abs(blinking);
		if (cl.stats[STAT_ROUNDS] > 0 && cl.stats[STAT_ROUNDS] < 11)
		{
			for (i = 0; i < cl.stats[STAT_ROUNDS]; i++)
			{
				if (i == 4)
				{
					Draw_AdvancedPic(5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), blinking, PAL_STANDARD);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_AdvancedPic(5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), blinking, PAL_STANDARD);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_AdvancedPic(5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), blinking, PAL_STANDARD);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), blinking, PAL_STANDARD);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), blinking, PAL_STANDARD);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), blinking, PAL_STANDARD);
			x_offset = x_offset + Draw_CachePic(sb_round_num[num[0]])->width - 8;
		}
	}
	else if (cl.stats[STAT_ROUNDCHANGE] == 7)//blink white while fading back
	{
		if (red_to_white_alpha < 255)
			red_to_white_alpha += cl.time * 0.4;
		else
			red_to_white_alpha = 255;

		if (cl.stats[STAT_ROUNDS] > 0 && cl.stats[STAT_ROUNDS] < 11)
		{
			for (i = 0; i < cl.stats[STAT_ROUNDS]; i++)
			{
				if (i == 4)
				{
					Draw_AdvancedPic(5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, PAL_STANDARD);
					Draw_AdvancedPic(5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), red_to_white_alpha, PAL_WHITETORED);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_AdvancedPic(5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, PAL_STANDARD);
					Draw_AdvancedPic(5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), red_to_white_alpha, PAL_WHITETORED);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_AdvancedPic(5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), 255, PAL_STANDARD);
				Draw_AdvancedPic(5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), red_to_white_alpha, PAL_WHITETORED);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), 255, PAL_STANDARD);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), red_to_white_alpha, PAL_WHITETORED);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), 255, PAL_STANDARD);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), red_to_white_alpha, PAL_WHITETORED);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), 255, PAL_STANDARD);
			Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), red_to_white_alpha, PAL_WHITETORED);
			x_offset = x_offset + Draw_CachePic(sb_round_num[num[0]])->width - 8;
		}
	}
	else
	{
		red_to_white_alpha = 255;
		alphabling = 0;
		if (cl.stats[STAT_ROUNDS] > 0 && cl.stats[STAT_ROUNDS] < 11)
		{
			for (i = 0; i < cl.stats[STAT_ROUNDS]; i++)
			{
				if (i == 4)
				{
					Draw_AdvancedPic(5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, PAL_WHITETORED);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_AdvancedPic(5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, PAL_WHITETORED);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_AdvancedPic(5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), 255, PAL_WHITETORED);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), 255, PAL_WHITETORED);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), 255, PAL_WHITETORED);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			
			if(cl.stats[STAT_ROUNDS] == 0)
				return;
			
			Draw_AdvancedPic(2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), 255, PAL_WHITETORED);
			x_offset = x_offset + Draw_CachePic(sb_round_num[num[0]])->width - 8;
		}
	}
}

/*
===============
HUD_Perks
===============
*/
#define 	P_JUG		1
#define 	P_DOUBLE	2
#define 	P_SPEED		4
#define 	P_REVIVE	8
#define 	P_FLOP		16
#define 	P_STAMIN	32
#define 	P_DEAD 		64
#define 	P_MULE 		128

int perk_order[9];
int current_perk_order;

void HUD_Perks (void)
{
	int i;
	int x = 1;

	for (i = 0; i < 9; i++)
	{
		if (perk_order[i])
		{
			if (perk_order[i] == P_JUG)
			{
				Draw_AdvancedPic(x, 1, jugpic, 255, PAL_STANDARD);
				x += 15;
			}
			else if (perk_order[i] == P_DOUBLE)
			{
				Draw_AdvancedPic(x, 1, doublepic, 255, PAL_STANDARD);
				x += 15;
			}
			else if (perk_order[i] == P_SPEED)
			{
				Draw_AdvancedPic(x, 1, speedpic, 255, PAL_STANDARD);
				x += 15;
			}
			else if (perk_order[i] == P_REVIVE)
			{
				Draw_AdvancedPic(x, 1, revivepic, 255, PAL_STANDARD);
				x += 15;
			}
			else if (perk_order[i] == P_FLOP)
			{
				Draw_AdvancedPic(x, 1, floppic, 255, PAL_STANDARD);
				x += 15;
			}
			else if (perk_order[i] == P_STAMIN)
			{
				Draw_AdvancedPic(x, 1, staminpic, 255, PAL_STANDARD);
				x += 15;
			}
			else if (perk_order[i] == P_DEAD)
			{
				Draw_AdvancedPic(x, 1, deadpic, 255, PAL_STANDARD);
				x += 15;
			}
			else if (perk_order[i] == P_MULE)
			{
				Draw_AdvancedPic(x, 1, mulepic, 255, PAL_STANDARD);
				x += 15;
			}
		}
	}
}

/*
===============
HUD_Powerups
===============
*/
void HUD_Powerups (void)
{
	int count;

	// nai why the fuck would you keep this
	// horrible way to offset check :)))))))))))))))))) :DDDDDDDD XOXO

	if (cl.stats[STAT_X2])
		count++;

	if (cl.stats[STAT_INSTA])
		count++;

	// both are avail draw fixed order
	if (count == 2) {
		Draw_AdvancedPic((vid.width/2) - x2pic->width, vid.height - x2pic->height, x2pic, 255, PAL_STANDARD);
		Draw_AdvancedPic((vid.width/2) + 3, vid.height - x2pic->height, instapic, 255, PAL_STANDARD);
	} else {
		if (cl.stats[STAT_X2])
			Draw_AdvancedPic((vid.width/2) - 13, vid.height - x2pic->height, x2pic, 255, PAL_STANDARD);
		if(cl.stats[STAT_INSTA])
			Draw_AdvancedPic((vid.width/2) - 13, vid.height - x2pic->height, instapic, 255, PAL_STANDARD);
	}
}

/*
===============
HUD_ProgressBar
===============
*/
void HUD_ProgressBar (void)
{
	float progressbar;

	if (cl.progress_bar)
	{
		progressbar = 100 - ((cl.progress_bar-sv.time)*10);
		if (progressbar >= 100)
			progressbar = 100;

 		Draw_FillByColor  (((vid.width) >> 1) - 51, (int)(vid.height*0.75 - 1), 102, 5, 0, 0, 0,100);
 		Draw_FillByColor (((vid.width) >> 1) - 50, (int)((vid.height*3) >> 2), (int)progressbar, 3, 255, 255, 255,100);

		Draw_String ((vid.width - (88))/2, vid.height*0.75 + 10, "Reviving...");
	}
}

#if 0
/*
===============
HUD_Achievement

Achievements based on code by Arkage
===============
*/


int		achievement; // the background image
int		achievement_unlocked;
char		achievement_text[MAX_QPATH];
double		achievement_time;
float smallsec;
int ach_pic;

void HUD_Achievement (void)
{

	if (achievement_unlocked == 1)
	{
		smallsec = smallsec + 0.7;
		if (smallsec >= 55)
			smallsec = 55;
		//Background image
		//Sbar_DrawPic (176, 5, achievement);
		// The achievement text
		Draw_AlphaPic (30, smallsec - 50, achievement_list[ach_pic].img, 0.7f);
	}

	// Reset the achievement
	if (Sys_FloatTime() >= achievement_time)
	{
		achievement_unlocked = 0;
	}

}

void HUD_Parse_Achievement (int ach)
{
    if (achievement_list[ach].unlocked)
        return;

	achievement_unlocked = 1;
	smallsec = 0;
	achievement_time = Sys_FloatTime() + 10;
	ach_pic = ach;
	achievement_list[ach].unlocked = 1;
	//Save_Achivements();
}
#endif
/*
===============
HUD_Ammo
===============
*/

int GetLowAmmo(int weapon, int type)
{
	switch (weapon)
	{
		case W_COLT: if (type) return 2; else return 16;
		case W_KAR: if (type) return 1; else return 10;
		case W_KAR_SCOPE: if (type) return 1; else return 10;
		case W_M1A1: if (type) return 4; else return 24;
		case W_SAWNOFF: if (type) return 1; else return 12;
		case W_DB: if (type) return 1; else return 12;
		case W_THOMPSON: if (type) return 6; else return 40;
		case W_BAR: if (type) return 6; else return 28;
		default: return 0;
	}
}

int IsDualWeapon(int weapon)
{
	switch(weapon) {
		case W_BIATCH:
		case W_SNUFF:
			return 1;
		default:
			return 0;
	}

	return 0;
}

void HUD_Ammo (void)
{
	char* magstring;
	int reslen;

	reslen = strlen(va("/%i", cl.stats[STAT_AMMO]));

	//
	// Magazine
	//
	magstring = va("%i", cl.stats[STAT_CURRENTMAG]);
	if (GetLowAmmo(cl.stats[STAT_ACTIVEWEAPON], 1) >= cl.stats[STAT_CURRENTMAG]) {
		Draw_AdvancedString((vid.width-(reslen*8)) - strlen(magstring)*8, 188, magstring, 255, PAL_WHITETORED);
	} else {
		Draw_String((vid.width-(reslen*8)) - strlen(magstring)*8, 188, magstring);
	}

	//
	// Reserve Ammo
	//
	magstring = va("/%i", cl.stats[STAT_AMMO]);
	if (GetLowAmmo(cl.stats[STAT_ACTIVEWEAPON], 0) >= cl.stats[STAT_AMMO]) {
		Draw_AdvancedString(vid.width - strlen(magstring)*8, 188, magstring, 255, PAL_WHITETORED);
	} else {
		Draw_String(vid.width - strlen(magstring)*8, 188, magstring);
	}
}

/*
===============
HUD_AmmoString
===============
*/

void HUD_AmmoString (void)
{
	if (GetLowAmmo(cl.stats[STAT_ACTIVEWEAPON], 1) >= cl.stats[STAT_CURRENTMAG])
	{
		int x;

		if (0 < cl.stats[STAT_AMMO] && cl.stats[STAT_CURRENTMAG] >= 0) {
			x = (vid.width - strlen("Reload")*8)/2;
			Draw_String(x, 140, "Reload");
		} else if (0 < cl.stats[STAT_CURRENTMAG]) {
			x = (vid.width - strlen("LOW AMMO")*8)/2;
			Draw_AdvancedString(x, 140, "LOW AMMO", 255, PAL_WHITETOYELLOW);
		} else {
			x = (vid.width - strlen("NO AMMO")*8)/2;
			Draw_AdvancedString(x, 140, "NO AMMO", 255, PAL_WHITETORED);
		}
	}
}

/*
===============
HUD_Grenades
===============
*/
#define 	UI_FRAG		1
#define 	UI_BETTY	2

void HUD_Grenades (void)
{
	Draw_AdvancedPic(vid.width - fragpic->width, vid.height - fragpic->height, fragpic);
	if (cl.stats[STAT_GRENADES] & UI_FRAG)
	{
		if (cl.stats[STAT_PRIGRENADES] <= 0)
			Draw_AdvancedString(vid.width - fragpic->width/2, vid.height - fragpic->height / 2, va ("%i",cl.stats[STAT_PRIGRENADES]), 255, PAL_STANDARD);
		else
			Draw_String (vid.width - fragpic->width/2, vid.height - fragpic->height / 2, va ("%i",cl.stats[STAT_PRIGRENADES]));
	}
	if (cl.stats[STAT_GRENADES] & UI_BETTY)
	{
		Draw_StretchPic (vid.width - (2 * fragpic->width) - 4, vid.height - (2 * fragpic->height), bettypic, 22, 22);
		if (cl.stats[STAT_PRIGRENADES] <= 0)
			Draw_AdvancedString(vid.width - (1.5 * fragpic->width) - 4, vid.height - (1.5 * fragpic->height), va ("%i",cl.stats[STAT_SECGRENADES]), 255, PAL_STANDARD);
		else
			Draw_String (vid.width - (1.5 * fragpic->width) - 4, vid.height - (1.5 * fragpic->height), va ("%i",cl.stats[STAT_SECGRENADES]));
	}
}

/*
===============
HUD_Weapon
===============
*/
void HUD_Weapon (void)
{
	char str[32];
	float l;
	x_value = vid.width;
	y_value = 180;

	strcpy(str, pr_strings+sv_player->v.Weapon_Name);
	l = strlen(str);

	x_value = vid.width - l*8;
	Draw_String (x_value, y_value, str);
}

/*
===============
HUD_Draw
===============
*/
void HUD_Draw (void)
{
	if (scr_con_current == vid.height)
		return;		// console is full screen

	//if (key_dest == key_menu_pause) // naievil -- fixme we don't have key_menu_pause yet
	//	return;

	scr_copyeverything = 1;


	if (waypoint_mode.value)
	{
		Draw_String (vid.width - 112, 0, "WAYPOINTMODE");
		Draw_String (vid.width - 240, 8, "Press fire to create waypoint");
		Draw_String (vid.width - 232, 16, "Press use to select waypoint");
		Draw_String (vid.width - 216, 24, "Press aim to link waypoint");
		Draw_String (vid.width - 248, 32, "Press knife to remove waypoint");
		Draw_String (vid.width - 272, 40, "Press switch to move waypoint here");
		Draw_String (vid.width - 304, 48, "Press reload to make special waypoint");
		return;
	}


	if (cl.stats[STAT_HEALTH] <= 0)
	{
		HUD_EndScreen ();
		return;
	}
	HUD_Blood();
	HUD_Rounds();
	HUD_Perks();
	HUD_Powerups();
	HUD_ProgressBar();
	if ((HUD_Change_time > Sys_FloatTime() || GetLowAmmo(cl.stats[STAT_ACTIVEWEAPON], 1) >= cl.stats[STAT_CURRENTMAG] || GetLowAmmo(cl.stats[STAT_ACTIVEWEAPON], 0) >= cl.stats[STAT_AMMO]) && cl.stats[STAT_HEALTH] >= 20)
	{ //these elements are only drawn when relevant for few seconds
		HUD_Ammo();
		HUD_Grenades();
		HUD_Weapon();
		HUD_AmmoString();
	}
	HUD_Points();
	HUD_Point_Change();
#if 0 // naievil -- we are not doing this shit
	HUD_Achievement();
#endif
	if (domaxammo == true) {
		if (maxammoopac <= 0) {
			maxammoopac = 255;
			maxammoy = 100;
		}
		HUD_MaxAmmo();
	}
}