#pragma once
#include <stdint.h>

typedef uint32_t SDL_MouseID;
struct SDL_Window;

extern "C" {
int SDL_SendMouseMotion	(SDL_Window *window, SDL_MouseID mouseID,
		int 	relative,
		int 	x,
		int 	y 
		);
int SDL_SendMouseButton	(SDL_Window * 	window,
		SDL_MouseID 	mouseID,
		uint8_t 	state,
		uint8_t 	button 
		);
}
