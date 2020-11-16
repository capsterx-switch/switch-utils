#pragma once
#include <cstring>

class SDL_Event;

namespace nswitch {
bool rstick_to_mouse(size_t screenx, size_t screeny, size_t currentx, size_t currenty, SDL_Event const & event)
}
