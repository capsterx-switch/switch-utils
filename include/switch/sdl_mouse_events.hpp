#pragma once
typedef Uint32 SDL_MouseID;
extern "C" {
int SDL_SendMouseMotion	(SDL_Window *window, SDL_MouseID mouseID,
		int 	relative,
		int 	x,
		int 	y 
		);
int SDL_SendMouseButton	(SDL_Window * 	window,
		SDL_MouseID 	mouseID,
		Uint8 	state,
		Uint8 	button 
		);
}
