#pragma once
class SDL_Event;

namespace nswitch {
bool touch_to_mouse(size_t x, size_t y, SDL_Event & event);
}
