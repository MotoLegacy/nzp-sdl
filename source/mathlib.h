/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2007-2008 Kristian Duske

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
// mathlib.h

//Dan East:
#include "FixedPointMath.h"

#ifdef USE_PQ_OPT
typedef int fpvec3[3];
#endif

typedef fixedpoint_t vec3_FPM_t[3];
typedef fixedpoint8_24_t vec3_8_24FPM_t[3];
typedef fixedpoint_t vec5_FPM_t[5];

//End Dan

typedef float vec_t;
typedef vec_t vec3_t[3];
typedef vec_t vec5_t[5];

typedef	int	fixed4_t;
typedef	int	fixed8_t;
typedef	int	fixed16_t;

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#define M_PI_DIV_180 (M_PI / 180.0) //johnfitz

struct mplane_s;

extern vec3_t vec3_origin;
extern	int nanmask;

#define	IS_NAN(x) (((*(int *)&x)&nanmask)==nanmask)

#define DoublePrecisionDotProduct(x,y) ((double)(x)[0]*(y)[0]+(double)(x)[1]*(y)[1]+(double)(x)[2]*(y)[2])

#define VectorInterpolate(v1, _frac, v2, v)		\
do {											\
	_mathlib_temp_float1 = _frac;				\
												\
	(v)[0] = (v1)[0] + _mathlib_temp_float1 * ((v2)[0] - (v1)[0]);\
	(v)[1] = (v1)[1] + _mathlib_temp_float1 * ((v2)[1] - (v1)[1]);\
	(v)[2] = (v1)[2] + _mathlib_temp_float1 * ((v2)[2] - (v1)[2]);\
} while(0)


#define CLAMP(min, x, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x)) //johnfitz

// Prototypes added by PM.
void RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point, float degrees );
extern int _mathlib_temp_int1, _mathlib_temp_int2, _mathlib_temp_int3;
extern float _mathlib_temp_float1, _mathlib_temp_float2, _mathlib_temp_float3;
extern vec3_t _mathlib_temp_vec1, _mathlib_temp_vec2, _mathlib_temp_vec3;

#define Q_rint(x) ((x) > 0 ? (int)((x) + 0.5) : (int)((x) - 0.5)) //johnfitz -- from joequake

#define DotProduct(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#define VectorSubtract(a,b,c) {c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2];}
#define VectorAdd(a,b,c) {c[0]=a[0]+b[0];c[1]=a[1]+b[1];c[2]=a[2]+b[2];}
#define VectorCopy(a,b) {b[0]=a[0];b[1]=a[1];b[2]=a[2];}
#define VectorNegate(a, b)	((b)[0] = -(a)[0], (b)[1] = -(a)[1], (b)[2] = -(a)[2])

void vectoangles (vec3_t vec, vec3_t ang);
float VecLength2(vec3_t v1, vec3_t v2);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
static inline float InvSqrt( float number ) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;			// evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}
#pragma GCC diagnostic pop

static inline void VectorNormalizeNoRet (vec3_t v)
{
	float	length, ilength;

	ilength = InvSqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

        v[0] *= ilength;
        v[1] *= ilength;
        v[2] *= ilength;
}


//johnfitz -- courtesy of lordhavoc
#define VectorNormalizeFast(_v)\
{\
	float _y, _number;\
	_number = DotProduct(_v, _v);\
	if (_number != 0.0)\
	{\
		*((int *)&_y) = 0x5f3759df - ((* (int *) &_number) >> 1);\
		_y = _y * (1.5f - (_number * 0.5f * _y * _y));\
		VectorScale(_v, _y, _v);\
	}\
}

// kristian - missing math functions
/*#if !defined(max)
inline int max (int x, int y);
#endif
#if !defined(min)
inline int min (int x, int y);
#endif*/
// kristian

void TurnVector (vec3_t out, const vec3_t forward, const vec3_t side, float angle); //johnfitz
void VectorAngles (const vec3_t forward, vec3_t angles); //johnfitz

void VectorMA (vec3_t veca, float scale, vec3_t vecb, vec3_t vecc);

vec_t _DotProduct (vec3_t v1, vec3_t v2);
void _VectorSubtract (vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorAdd (vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorCopy (vec3_t in, vec3_t out);

int VectorCompare (vec3_t v1, vec3_t v2);
vec_t Length (vec3_t v);
void CrossProduct (vec3_t v1, vec3_t v2, vec3_t cross);
float VectorNormalize (vec3_t v);		// returns vector length
void VectorInverse (vec3_t v);
void VectorScale (vec3_t in, vec_t scale, vec3_t out);
int Q_log2(int val);

void R_ConcatRotations (float in1[3][3], float in2[3][3], float out[3][3]);
void R_ConcatTransforms (float in1[3][4], float in2[3][4], float out[3][4]);

void FloorDivMod (double numer, double denom, int *quotient,
		int *rem);
fixed16_t Invert24To16(fixed16_t val);
int GreatestCommonDivisor (int i1, int i2);

void AngleVectors (vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct mplane_s *plane);
float	anglemod(float a);



#define BOX_ON_PLANE_SIDE(emins, emaxs, p)	\
	(((p)->type < 3)?						\
	(										\
		((p)->dist <= (emins)[(p)->type])?	\
			1								\
		:									\
		(									\
			((p)->dist >= (emaxs)[(p)->type])?\
				2							\
			:								\
				3							\
		)									\
	)										\
	:										\
		BoxOnPlaneSide( (emins), (emaxs), (p)))
