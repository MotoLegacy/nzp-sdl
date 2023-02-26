

// rockboxdef.h -- Rockbox specifics
#ifndef __ROCKBOXDEF__
#define __ROCKBOXDEF__

#define open(_FILE, _MODE, _OPT) 		rb->open(_FILE, _MODE, _OPT)
#define write(_HANDLE, _DATA, _LEN)		rb->write(_HANDLE, _DATA, _LEN)
#define close( _HANDLE) 				rb->close(_HANDLE)

#define ROCKBOX 		1		

#endif