#pragma once

#include "SDL.h"

struct Switch_Key_Map;
struct Switch_Key_Map * switch_keymap_create();
int switch_keymap_load_from_file(struct Switch_Key_Map *, char const *);
int switch_keymap_event(struct Switch_Key_Map *, SDL_Event const *);
void switch_keymap_destroy(struct Switch_Key_Map *);
