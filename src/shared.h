
#ifndef _SHARED_H_
#define _SHARED_H_

#define VERSION     "0.9.3"

/* Data types */
typedef unsigned long int dword;
typedef unsigned short int word;
typedef unsigned char byte;


/* To keep the MAME code happy */
#define HAS_YM3812  1
typedef signed short int FMSAMPLE;


/* Nasty hacks so the PSX version will compile */
#if PSX
#include "psx/syscall.h"    /* for NULL, malloc(), etc. */
#define fread               /* No real filesystem :) */
#define fwrite
#define sin                 /* No equivelant */
#define pow
#define log10
#else
#include <string.h>
#include <math.h>
#endif

#if DOS
#include <stdio.h>
#endif

#ifdef _MSC_VER
#include <stdio.h>
#include <string.h>
#ifndef __inline__
#define __inline__ __inline
#endif
#define strcasecmp stricmp
#endif

#ifdef __LCC__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __inline__
#define __inline__ inline
#endif
#ifndef strcasecmp
#define strcasecmp stricmp
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "z80.h"
#include "sms.h"
#include "vdp.h"
#include "render.h"
#include "system.h"

#endif /* _SHARED_H_ */

