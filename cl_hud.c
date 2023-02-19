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

#include "quakedef.h"

char		sb_round[5][32];
char		sb_round_num[10][32];
qpic_t		*sb_moneyback;
qpic_t		*instapic;
qpic_t		*x2pic;
char 		*revivepic;
char		*jugpic;
char		*floppic;
char		*staminpic;
char		*doublepic;
char		*speedpic;
char		*deadpic;
char 		*mulepic;
char		*fragpic;
char		*bettypic;


char 		*b_leftbutton;
char 		*b_rightbutton;
char 		*b_centerbutton;
char 		*b_downbutton;
char  		*b_upbutton;

char      *fx_blood_lu;
char      *fx_blood_ru;
char      *fx_blood_ld;
char      *fx_blood_rd;

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
	int		i;

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

	sb_moneyback = Draw_CachePic ("gfx/hud/moneyback");
	instapic = Draw_CachePic ("gfx/hud/in_kill");
	x2pic = Draw_CachePic ("gfx/hud/2x");

	revivepic = "gfx/hud/revive";
	jugpic = "gfx/hud/jug";
	floppic = "gfx/hud/flopper";
	staminpic = "gfx/hud/stamin";
	doublepic = "gfx/hud/double";
	speedpic = "gfx/hud/speed";
	deadpic = "gfx/hud/dead";
	mulepic = "gfx/hud/mule";
	fragpic =  "gfx/hud/frag";
	bettypic = "gfx/hud/betty";

	b_leftbutton = "gfx/butticons/facebt_left";
	b_rightbutton = "gfx/butticons/facebt_right";
	b_centerbutton = "gfx/butticons/facebt_center";
	b_downbutton = "gfx/butticons/facebt_down";
	b_upbutton = "gfx/butticons/facebt_up";

    fx_blood_lu = "gfx/hud/blood";
    Draw_Pic(0, 0, Draw_CachePic(fx_blood_lu));
    /*fx_blood_lu = "gfx/hud/blood_tl";
    /fx_blood_ru = "gfx/hud/blood_tr";
    fx_blood_ld = "gfx/hud/blood_bl";
    fx_blood_rd = "gfx/hud/blood_br";*/

    // naievil -- fixme
	//Achievement_Init();
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

	round_center_x = (vid.width/2 - (Draw_CachePic(sb_round[0])->width)/2);
	round_center_y = (vid.height/2 - (Draw_CachePic(sb_round[0])->height)/2);
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

	Draw_ColoredString((vid.width - 9*8)/2, 40, "GAME OVER", 255, 0, 0, 255, 1);

	sprintf (str,"You survived %3i rounds", cl.stats[STAT_ROUNDS]);
	Draw_String ((vid.width - strlen (str)*8)/2, 52, str);

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
		Draw_Pic (x, y, sb_moneyback);
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
				Draw_ColoredString (point_change[i].x, point_change[i].y, va ("-%i", point_change[i].points), 255, 0, 0, 255, 1);
			else
				Draw_ColoredString (point_change[i].x, point_change[i].y, va ("+%i", point_change[i].points), 255, 255, 0, 255, 1);
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
    float color = 255.0 + modifier;
    
    Draw_TransPic(0,0,Draw_CachePic(fx_blood_lu));
    //Draw_ColorPic (0, 0, fx_blood_lu, 82, 6, 6, alpha);
    /*Draw_ColorPic (0, vid.height - fx_blood_ru->height, fx_blood_ld, 82, 6, 6, alpha);
    Draw_ColorPic (vid.width - fx_blood_ru->width, 0, fx_blood_ru, 82, 6, 6, alpha);
    Draw_ColorPic (vid.width - fx_blood_ru->width, vid.height - fx_blood_ru->height, fx_blood_rd, 82, 6, 6, alpha);*/
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
			Draw_ColoredString(4, vid.height/2 + 16, value, 255, 255, 255, alpha, 1);
		}
		if (!strcmp("date", key)) // search for date key
		{
			Draw_ColoredString(4, vid.height/2 + 26, value, 255, 255, 255, alpha, 1);
		}
		if (!strcmp("person", key)) // search for person key
		{
			Draw_ColoredString(4, vid.height/2 + 36, value, 255, 255, 255, alpha, 1);
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

	Draw_ColoredString(vid.width/2 - strlen("MAX AMMO!")*2, maxammoy, "MAX AMMO!", 255, 255, 255, maxammoopac, 1);

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
		if (!value)
			value = 255;

		Draw_ColoredString(vid.width/2 - (strlen("Round")*8/2), 80, "Round", 255, value, value, 255, 2);
		
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
		Draw_ColoredString(vid.width/2 - (strlen("Round")*8/2), 80, "Round", 255, 0, 0, value, 2);

		HUD_WorldText(value2);
		Draw_ColoredString(4, vid.height/2 + 6, "'Nazi Zombies'", 255, 255, 255, value2, 1);
		
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
		Draw_ColoredString(4, vid.height/2 + 6, "'Nazi Zombies'", 255, 255, 255, 255, 1);

		value2 += cl.time * 0.4;

		if (value2 >= 255) {
			value2 = 255;
			textstate = 3;
		}
	}
	// Fade worldtext out, finally.
	else if (textstate == 3) {
		HUD_WorldText(value2);
		Draw_ColoredString(4, vid.height/2 + 6, "'Nazi Zombies'", 255, 255, 255, value2, 1);

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

		Draw_ColorPic ((vid.width - Draw_CachePic(sb_round[0])->width) /2, (vid.height - Draw_CachePic(sb_round[0])->height) /2, Draw_CachePic(sb_round[0]), 107, 1, 0, alphabling);

		alphabling = alphabling + 15;

		if (alphabling < 0)
			alphabling = 0;
		else if (alphabling > 255)
			alphabling = 255;
	}
	else if (cl.stats[STAT_ROUNDCHANGE] == 2)//this is the rounds icon moving from middle
	{
		Draw_ColorPic ((int)round_center_x, (int)round_center_y, Draw_CachePic(sb_round[0]), 107, 1, 0, 255);
		round_center_x = round_center_x - (320/110);
		round_center_y = round_center_y + 1.4;
		if (round_center_x <= 5)
			round_center_x = 5;
		if (round_center_y >= vid.height - Draw_CachePic(sb_round[0])->height)
			round_center_y = vid.height - Draw_CachePic(sb_round[0])->height;
	}
	else if (cl.stats[STAT_ROUNDCHANGE] == 3)//shift to white
	{
		if (!color_shift_init)
		{
			color_shift[0] = 107;
			color_shift[1] = 1;
			color_shift[2] = 0;
			for (i = 0; i < 3; i++)
			{
				color_shift_end[i] = 255;
				color_shift_steps[i] = (color_shift_end[i] - color_shift[i])/60;
			}
			color_shift_init = 1;
		}
		for (i = 0; i < 3; i++)
		{
			if (color_shift[i] < color_shift_end[i])
				color_shift[i] = color_shift[i] + color_shift_steps[i];

			if (color_shift[i] >= color_shift_end[i])
				color_shift[i] = color_shift_end[i];
		}
		if (cl.stats[STAT_ROUNDS] > 0 && cl.stats[STAT_ROUNDS] < 11)
		{

			for (i = 0; i < cl.stats[STAT_ROUNDS]; i++)
			{
				if (i == 4)
				{
					Draw_ColorPic (5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_ColorPic (5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_ColorPic (5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
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
					Draw_ColorPic (5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, 255, 255, blinking);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_ColorPic (5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, 255, 255, blinking);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_ColorPic (5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), 255, 255, 255, blinking);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), 255, 255, 255, blinking);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), 255, 255, 255, blinking);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), 255, 255, 255, blinking);
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
					Draw_ColorPic (5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, 255, 255, blinking);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_ColorPic (5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, 255, 255, blinking);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_ColorPic (5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), 255, 255, 255, blinking);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), 255, 255, 255, blinking);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), 255, 255, 255, blinking);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), 255, 255, 255, blinking);
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
					Draw_ColorPic (5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, 255, 255, blinking);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_ColorPic (5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 255, 255, 255, blinking);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_ColorPic (5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), 255, 255, 255, blinking);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), 255, 255, 255, blinking);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), 255, 255, 255, blinking);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), 255, 255, 255, blinking);
			x_offset = x_offset + Draw_CachePic(sb_round_num[num[0]])->width - 8;
		}
	}
	else if (cl.stats[STAT_ROUNDCHANGE] == 7)//blink white while fading back
	{
		if (!color_shift_init)
		{
			color_shift_end[0] = 107;
			color_shift_end[1] = 1;
			color_shift_end[2] = 0;
			for (i = 0; i < 3; i++)
			{
				color_shift[i] = 255;
				color_shift_steps[i] = (color_shift[i] - color_shift_end[i])/60;
			}
			color_shift_init = 1;
		}
		for (i = 0; i < 3; i++)
		{
			if (color_shift[i] > color_shift_end[i])
				color_shift[i] = color_shift[i] - color_shift_steps[i];

			if (color_shift[i] < color_shift_end[i])
				color_shift[i] = color_shift_end[i];
		}
		if (cl.stats[STAT_ROUNDS] > 0 && cl.stats[STAT_ROUNDS] < 11)
		{
			for (i = 0; i < cl.stats[STAT_ROUNDS]; i++)
			{
				if (i == 4)
				{
					Draw_ColorPic (5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_ColorPic (5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_ColorPic (5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), (int)color_shift[0], (int)color_shift[1], (int)color_shift[2], 255);
			x_offset = x_offset + Draw_CachePic(sb_round_num[num[0]])->width - 8;
		}
	}
	else
	{
		color_shift[0] = 107;
		color_shift[1] = 1;
		color_shift[2] = 0;
		color_shift_init = 0;
		alphabling = 0;
		if (cl.stats[STAT_ROUNDS] > 0 && cl.stats[STAT_ROUNDS] < 11)
		{
			for (i = 0; i < cl.stats[STAT_ROUNDS]; i++)
			{
				if (i == 4)
				{
					Draw_ColorPic (5, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 107, 1, 0, 255);
					savex = x_offset + 10;
					x_offset = x_offset + 10;
					continue;
				}
				if (i == 9)
				{
					Draw_ColorPic (5 + savex, vid.height - Draw_CachePic(sb_round[4])->height - 4, Draw_CachePic(sb_round[4]), 107, 1, 0, 255);
					continue;
				}
				if (i > 4)
					icon_num = i - 5;
				else
					icon_num = i;

				Draw_ColorPic (5 + x_offset, vid.height - Draw_CachePic(sb_round[icon_num])->height - 4, Draw_CachePic(sb_round[icon_num]), 107, 1, 0, 255);

				x_offset = x_offset + Draw_CachePic(sb_round[icon_num])->width + 3;
			}
		}
		else
		{
			if (cl.stats[STAT_ROUNDS] >= 100)
			{
				num[2] = (int)(cl.stats[STAT_ROUNDS]/100);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[2]])->height - 4, Draw_CachePic(sb_round_num[num[2]]), 107, 1, 0, 255);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[2]])->width - 8;
			}
			else
				num[2] = 0;
			if (cl.stats[STAT_ROUNDS] >= 10)
			{
				num[1] = (int)((cl.stats[STAT_ROUNDS] - num[2]*100)/10);
				Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[1]])->height - 4, Draw_CachePic(sb_round_num[num[1]]), 107, 1, 0, 255);
				x_offset = x_offset + Draw_CachePic(sb_round_num[num[1]])->width - 8;
			}
			else
				num[1] = 0;

			num[0] = cl.stats[STAT_ROUNDS] - num[2]*100 - num[1]*10;
			
			if(cl.stats[STAT_ROUNDS] == 0)
				return;
			
			Draw_ColorPic (2 + x_offset, vid.height - Draw_CachePic(sb_round_num[num[0]])->height - 4, Draw_CachePic(sb_round_num[num[0]]), 107, 1, 0, 255);
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
	int y;
	y = vid.height - Draw_CachePic(sb_round[1])->height - Draw_CachePic(jugpic)->height -2;

	for (i = 0; i < 9; i++)
	{
		if (perk_order[i])
		{
			if (perk_order[i] == P_JUG)
			{
				Draw_StretchPic (2, y, Draw_CachePic(jugpic), 20, 20);
				y = y - 22;
			}
			else if (perk_order[i] == P_DOUBLE)
			{
				Draw_StretchPic (2, y, Draw_CachePic(doublepic), 20, 20);
				y = y - 22;
			}
			else if (perk_order[i] == P_SPEED)
			{
				Draw_StretchPic (2, y, Draw_CachePic(speedpic), 20, 20);
				y = y - 22;
			}
			else if (perk_order[i] == P_REVIVE)
			{
				Draw_StretchPic (2, y, Draw_CachePic(revivepic), 20, 20);
				y = y - 22;
			}
			else if (perk_order[i] == P_FLOP)
			{
				Draw_StretchPic (2, y, Draw_CachePic(floppic), 20, 20);
				y = y - 22;
			}
			else if (perk_order[i] == P_STAMIN)
			{
				Draw_StretchPic (2, y, Draw_CachePic(staminpic), 20, 20);
				y = y - 22;
			}
			else if (perk_order[i] == P_DEAD)
			{
				Draw_StretchPic (2, y, Draw_CachePic(deadpic), 20, 20);
				y = y - 22;
			}
			else if (perk_order[i] == P_MULE)
			{
				Draw_StretchPic (2, y, Draw_CachePic(mulepic), 20, 20);
				y = y - 22;
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

	// horrible way to offset check :)))))))))))))))))) :DDDDDDDD XOXO

	if (cl.stats[STAT_X2])
		count++;

	if (cl.stats[STAT_INSTA])
		count++;

	// both are avail draw fixed order
	if (count == 2) {
		Draw_StretchPic((vid.width/2) - 27, 240 - 29, x2pic, 26, 26);
		Draw_StretchPic((vid.width/2) + 3, 240 - 29, instapic, 26, 26);
	} else {
		if (cl.stats[STAT_X2])
			Draw_StretchPic((vid.width/2) - 13, 240 - 29, x2pic, 26, 26);
		if(cl.stats[STAT_INSTA])
			Draw_StretchPic ((vid.width/2) - 13, 240 - 29, instapic, 28, 28);
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
		Draw_ColoredString((355-(reslen*8)) - strlen(magstring)*8, 218, magstring, 255, 0, 0, 255, 1);
	} else {
		Draw_ColoredString((355-(reslen*8)) - strlen(magstring)*8, 218, magstring, 255, 255, 255, 255, 1);
	}

	//
	// Reserve Ammo
	//
	magstring = va("/%i", cl.stats[STAT_AMMO]);
	if (GetLowAmmo(cl.stats[STAT_ACTIVEWEAPON], 0) >= cl.stats[STAT_AMMO]) {
		Draw_ColoredString(355 - strlen(magstring)*8, 218, magstring, 255, 0, 0, 255, 1);
	} else {
		Draw_ColoredString(355 - strlen(magstring)*8, 218, magstring, 255, 255, 255, 255, 1);
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
			Draw_ColoredString (x, 140, "Reload", 255, 255, 255, 255, 1);
		} else if (0 < cl.stats[STAT_CURRENTMAG]) {
			x = (vid.width - strlen("LOW AMMO")*8)/2;
			Draw_ColoredString (x, 140, "LOW AMMO", 255, 255, 0, 255, 1);
		} else {
			x = (vid.width - strlen("NO AMMO")*8)/2;
			Draw_ColoredString (x, 140, "NO AMMO", 255, 0, 0, 255, 1);
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
	Draw_StretchPic (356, 205, fragpic, 22, 22);
	if (cl.stats[STAT_GRENADES] & UI_FRAG)
	{
		if (cl.stats[STAT_PRIGRENADES] <= 0)
			Draw_ColoredString (356 + 12, 205 + 16, va ("%i",cl.stats[STAT_PRIGRENADES]), 255, 0, 0, 255, 1);
		else
			Draw_String (356 + 12, 205 + 16, va ("%i",cl.stats[STAT_PRIGRENADES]));
	}
	if (cl.stats[STAT_GRENADES] & UI_BETTY)
	{
		Draw_StretchPic (356 + 20, 205, bettypic, 22, 22);
		if (cl.stats[STAT_PRIGRENADES] <= 0)
			Draw_ColoredString (356 + 20 + 12, 205 + 16, va ("%i",cl.stats[STAT_SECGRENADES]), 255, 0, 0, 255, 1);
		else
			Draw_String (356 + 20 + 12, 205 + 16, va ("%i",cl.stats[STAT_SECGRENADES]));
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
	y_value = 205;

	strcpy(str, pr_strings+sv_player->v.Weapon_Name);
	l = strlen(str);

	x_value = 355 - l*8;
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


	// if (waypoint_mode.value)
	// {
	// 	Draw_String (vid.width - 112, 0, "WAYPOINTMODE");
	// 	Draw_String (vid.width - 240, 8, "Press fire to create waypoint");
	// 	Draw_String (vid.width - 232, 16, "Press use to select waypoint");
	// 	Draw_String (vid.width - 216, 24, "Press aim to link waypoint");
	// 	Draw_String (vid.width - 248, 32, "Press knife to remove waypoint");
	// 	Draw_String (vid.width - 272, 40, "Press switch to move waypoint here");
	// 	Draw_String (vid.width - 304, 48, "Press reload to make special waypoint");
	// 	return;
	// }


	if (cl.stats[STAT_HEALTH] <= 0)
	{
		HUD_EndScreen ();
		return;
	}
	HUD_Blood();
	HUD_Rounds();
#if 0
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
#endif
}