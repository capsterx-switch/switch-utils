#include "switch/touch_to_mouse.hpp"
#include "switch/sdl_mouse_events.hpp"
#include <SDL.h>

namespace nswitch {
bool touch_to_mouse (int screenx, int screeny, SDL_Event & event)
{
  if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP)
  {
     SDL_Finger* finger0 = SDL_GetTouchFinger(event.tfinger.touchId, 0);
     int numFingers = 0;
     if (finger0) {
     	numFingers = SDL_GetNumTouchFingers(event.tfinger.touchId);
     }
     if (numFingers == 1) {
       int x = screenx * event.tfinger.x;
       int y = screeny * event.tfinger.y;
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
}

extern "C" {
  int switch_touch_to_mouse(int screenx, int screeny, SDL_Event * event)
  {
    return nswitch::touch_to_mouse(screenx, screeny, *event);
  }
}
