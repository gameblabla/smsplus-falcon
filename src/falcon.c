
/*
    Copyright (c) 2002 Gregory Montoir

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <string.h>
#include "defines.h"
#include "falcsys.h"
#include "shared.h"
#include "config.h"
#include "saves.h"

#define SMS_SCREEN_WIDTH   256
#define SMS_SCREEN_HEIGHT  192
#define GG_SCREEN_WIDTH    160
#define GG_SCREEN_HEIGHT   144

static unsigned short substract;
static void sdl_video_init()
{
	char *err;
	unsigned short screen_width, screen_height;
	screen_width  = (IS_GG) ? GG_SCREEN_WIDTH  : SMS_SCREEN_WIDTH;
	screen_height = (IS_GG) ? GG_SCREEN_HEIGHT : SMS_SCREEN_HEIGHT;
	substract = (IS_GG) ? 7776 : 0;
	
	err = FalconInit(TRIPLE_BUFFER | EXIT_ON_SPACE_KEY
	#ifdef CTSIXTY
	 | CT60_MODE | EMULATOR_MODE
	 #endif
	 , NULL, IS_GG);

	memset(&bitmap, 0, sizeof(t_bitmap));
	bitmap.width  = screen_width;
	bitmap.height = screen_height;
	bitmap.depth  = 16;
	bitmap.pitch  = screen_width*2;
}

static void sdl_controls_update_input()
{
	input.pad[0] = 0;
	input.system = 0;
	
	if (IKBD_IsKeyPressed(IKBD_KEY_UP)) input.pad[0] |= INPUT_UP;
	else if (IKBD_IsKeyPressed(IKBD_KEY_DOWN)) input.pad[0] |= INPUT_DOWN;
	if (IKBD_IsKeyPressed(IKBD_KEY_LEFT)) input.pad[0] |= INPUT_LEFT;
	else if (IKBD_IsKeyPressed(IKBD_KEY_RIGHT)) input.pad[0] |= INPUT_RIGHT;
	if (IKBD_IsKeyPressed(IKBD_KEY_LSHIFT)) input.pad[0] |= INPUT_BUTTON1;
	if (IKBD_IsKeyPressed(IKBD_KEY_ALT)) input.pad[0] |= INPUT_BUTTON2;
	if (IKBD_IsKeyPressed(IKBD_KEY_RETURN))  input.system |= (IS_GG) ? INPUT_START : INPUT_PAUSE;
}

static int sdl_video_update(void *screen)
{
	bitmap.data   = (unsigned char *)screen - substract;
	sdl_controls_update_input();
	
    sms_frame(0);
    
	return (FL_COPY);
}

int sdl_main_init()
{
	system_init(cfg.sound_rate);
	sdl_video_init();
	return 1;
}


void sdl_main_loop()
{
	FalconLoop(sdl_video_update);
}

void sdl_main_close()
{
	system_shutdown();
	FalconExit();
}
