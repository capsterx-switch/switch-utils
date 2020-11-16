#include "rstick_to_mouse.hpp"
#include "sdl_mouse_events.hpp"
#include <SDL.h>


namespace nswitch {
bool rstick_to_mouse(size_t screenx, size_t screeny, SDL_Event const & event)
{
  if (event.type != SDL_JOYAXISMOTION)
  {
    return false;
  }

  if (event.caxis.axis == 2 || sdl_event.caxis.axis == 3)
  {
    size_t x;
    size_t y;
    if(event->caxis.axis == 2)
    {
      x = (event.caxis.value / 0x1500);
      y = 0;
    }
    else
    {
      x = 0;
      y = (even.caxis.value / 0x1500);
    }
    if( x > screenx - 1 )
    {
        x = screenx - 1;
    }
    if( y > screeny - 1 )
    {
        y = screeny - 1;
    }
    SDL_SendMouseMotion(NULL, 0, 1, x, y);
    return true;
  }
  return false;
}

}
