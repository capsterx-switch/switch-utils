#include "touch_to_mouse.hpp"
#include "sdl_mouse_events.hpp"
#include <SDL.h>


bool touch_to_mouse (size_t x, size_t y, SDL_Event & event)
{
  if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP)
  {
     SDL_Finger* finger0 = SDL_GetTouchFinger(event.tfinger.touchId, 0);
     int numFingers = 0;
     if (finger0) {
     	numFingers = SDL_GetNumTouchFingers(event.tfinger.touchId);
     }
     if (numFingers == 1) {
       int x = x * event.tfinger.x;
       int y = y * event.tfinger.y;
       SDL_SendMouseMotion(NULL, 0, 0, x, y);
       if(event.type == SDL_FINGERDOWN)
       {
         SDL_SendMouseButton(NULL, 0, SDL_PRESSED, SDL_BUTTON_LEFT);
       }
     }
     if (event.type == SDL_FINGERUP)
     {
       SDL_SendMouseButton(NULL, 0, SDL_RELEASED, SDL_BUTTON_LEFT);
     }
     return true;
  } 
  return false;
}
