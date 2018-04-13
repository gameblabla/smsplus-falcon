
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

#ifdef _TINSPIRE
#include <os.h>
#endif
	

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "sdlsms.h"
#include "saves.h"
#include "shared.h"
#include "config.h"



config cfg = {
  0, /* normal rendering */
  0, /* current screenshot file (*-000.bmp) */
  0, /* no sound core */
  0, /* default sound rate */
  1, /* throttle enabled */
  0, /* state_slot to use */
  1, /* 1 for no frame skip */
  0, /* start windowed (not fullscreen) */
  0, /* do not use sram (save, load) before starting/exiting */
  0,
  -1, /* no joystick */
  0/* default joystick mapping */
};



static int parse_args(void)
{
	/* default virtual console emulation settings */
	sms.use_fm = 0;
	cfg.use_sram = 0;
	sms.save = 0;
	cfg.throttle = 0;
	cfg.sound_rate = 0;
	sms.country = TYPE_OVERSEAS;
	/*strcpy(cfg.game_name, argv[1]);*/
  
	return 1;
}



int main(int argc, char* argv[])
{
	parse_args();

	if (argc == 2)
		load_rom(argv[1]);
	else
		load_rom("test.gg");
		
	sdl_main_init();

	sdl_main_loop();
	sdl_main_close();

	return 0;
}
