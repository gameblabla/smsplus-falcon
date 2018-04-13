
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
#include <stdio.h>
#include "shared.h"
#include "config.h"

/* Load a game file */
int load_rom(char *filename)
{
	int size;
	FILE *fd = NULL;
	
	fd = fopen(filename, "rb");
	if(!fd) return (0);

	/* Seek to end of file, and get size */
	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	/* Don't load games smaller than 32k */
	if(size < 0x8000) 
	{
		if(fd) fclose(fd);
		return (0);
	}

	/* Take care of image header, if present */
	if((size / 512) & 1) {
		size -= 512;
		fseek(fd, 512, SEEK_SET);
	}

	cart.pages = (size / 0x4000);
	cart.rom = malloc(size);
	if(!cart.rom) return (0);
	fread(cart.rom, size, 1, fd);

	if(fd) fclose(fd);

	/* Figure out game image type */
	#ifdef GG_BUILD
		cart.type = TYPE_GG;
	#else
		cart.type = TYPE_SMS;
	#endif
	
	if (strstr (filename,".gg"))
	{
		cart.type = TYPE_GG;
	}
	else
	{
		cart.type = TYPE_SMS;
	}

	return (1);
}


/* Load SRAM data */
void load_sram(char* game_name)
{
    char name[0x100];
    FILE *fd;
    strcpy(name, game_name);
    strcpy(strrchr(name, '.'), ".sav");
    fd = fopen(name, "rb");
    if(fd) {
        sms.save = 1;
        fread(sms.sram, 0x8000, 1, fd);
        fclose(fd);
    }
}


/* Save SRAM data */
void save_sram(char* game_name)
{
    if(sms.save) {
        char name[0x100];
        FILE *fd = NULL;
        strcpy(name, game_name);
        strcpy(strrchr(name, '.'), ".sav");
        fd = fopen(name, "wb");
        if(fd) {
            fwrite(sms.sram, 0x8000, 1, fd);
            fclose(fd);
        }
    }
}


/* Load system state */
int load_state(char* game_name, int state_slot)
{
    char name[0x100];
    FILE *fd = NULL;
    strcpy(name, game_name);
    sprintf(strrchr(name, '.'), ".st%d", state_slot);
    fd = fopen(name, "rb");
    if(!fd) return (0);
    system_load_state(fd);
    fclose(fd);
    return (1);
}


/* Save system state */
int save_state(char* game_name, int state_slot)
{
    char name[0x100];
    FILE *fd = NULL;
    strcpy(name, game_name);
    sprintf(strrchr(name, '.'), ".st%d", state_slot);
    fd = fopen(name, "wb");
    if(!fd) return (0);
    system_save_state(fd);
    fclose(fd);
    return(1);
}


/* This is called in system_reset() */
void system_load_sram(void) 
{
  load_sram(cfg.game_name);
}
