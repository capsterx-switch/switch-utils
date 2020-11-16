#include "switch/rstick_to_mouse.hpp"
#include "switch/sdl_mouse_events.hpp"
#include "switch/joymap.hpp"
#include <SDL.h>


namespace nswitch {
bool rstick_to_mouse(SDL_Event const & event)
{
  if (event.type == SDL_JOYAXISMOTION)
  {
    if (event.caxis.axis == 2 || event.caxis.axis == 3)
    {
      int x;
      int y;
      SDL_GetMouseState(&x, &y);
      if(event.caxis.axis == 2)
      {
        x += (event.caxis.value / 0x1500);
      }
      else
      {
        y += (event.caxis.value / 0x1500);
      }
      SDL_SendMouseMotion(NULL, 0, 0, x, y);
      return true;
    }
  }
  else if (event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP)
  {
    if (event.jbutton.button == (int)Switch_Joy::RSTICK)
    {
      SDL_SendMouseButton(NULL, 0, event.type == SDL_JOYBUTTONDOWN ? SDL_PRESSED : SDL_RELEASED, SDL_BUTTON_LEFT);
      return true;
    }
  }
  return false;
}

}
