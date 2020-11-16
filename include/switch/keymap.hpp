#pragma once
#include <iosfwd>

class SDL_Event;

namespace nswitch {
class Switch_Key_Map
{
public:
   Switch_Key_Map();
   ~Switch_Key_Map();
   void load_file(std::ifstream &);
   bool event(SDL_Event const &);
private:
   class Key_Map_Impl;   
   std::unique_ptr<Key_Map_Impl> impl_;
};
}
