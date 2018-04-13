
#ifndef __CONFIG_H__
#define __CONFIG_H__



typedef struct {
  int up,down,left,right;
  int b1,b2;
  int start;
} paddle;

typedef enum {
  AUDIO_SDL,
  AUDIO_WIN32API
} audiocore;

typedef struct {
  int current_screenshot;
  audiocore audio_core;
  int sound_rate;
  int throttle;
  int state_slot; 
  int frame_skip;
  int start_fullscreen;
  int use_sram;
  char game_name[0x100];
  int joystick_number;
  int joystick_button[3];
  paddle pad[2];
} config;

extern config cfg;



#endif
