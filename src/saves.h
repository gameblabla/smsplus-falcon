
#ifndef __SAVES_H__
#define __SAVES_H__



extern int load_rom(char*);
extern void load_sram(char*);
extern void save_sram(char*);
extern int save_state(char*,int);
extern int load_state(char*,int);



#endif