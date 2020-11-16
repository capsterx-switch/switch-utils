#include <switch/joymap.hpp>
#include <switch/keymap.hpp>
#include <switch/string.hpp>
#include <SDL.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

namespace {
const std::vector<std::pair<std::string, int>> Switch_Key_Mapping = {
  {"A", static_cast<int>(nswitch::Switch_Joy::A)},
  {"B", static_cast<int>(nswitch::Switch_Joy::B)},
  {"X", static_cast<int>(nswitch::Switch_Joy::X)},
  {"Y", static_cast<int>(nswitch::Switch_Joy::Y)},
  {"LSTICK", static_cast<int>(nswitch::Switch_Joy::LSTICK)},
  {"RSTICK", static_cast<int>(nswitch::Switch_Joy::RSTICK)},
  {"L", static_cast<int>(nswitch::Switch_Joy::L)},
  {"R", static_cast<int>(nswitch::Switch_Joy::R)},
  {"ZL", static_cast<int>(nswitch::Switch_Joy::ZL)},
  {"ZR", static_cast<int>(nswitch::Switch_Joy::ZR)},
  {"PLUS", static_cast<int>(nswitch::Switch_Joy::PLUS)},
  {"MINUS", static_cast<int>(nswitch::Switch_Joy::MINUS)},
  {"DLEFT", static_cast<int>(nswitch::Switch_Joy::DLEFT)},
  {"DUP", static_cast<int>(nswitch::Switch_Joy::DUP)},
  {"DRIGHT", static_cast<int>(nswitch::Switch_Joy::DRIGHT)},
  {"DDOWN", static_cast<int>(nswitch::Switch_Joy::DDOWN)}
};

auto SDLKeyStringTable = std::vector<std::pair<std::string, SDL_Keycode>>{
	{"BACKSPACE", SDLK_BACKSPACE},
	{"TAB",       SDLK_TAB},
	{"ENTER",     SDLK_RETURN},
	{"PAUSE",     SDLK_PAUSE},
	{"ESC",       SDLK_ESCAPE},
	{"SPACE",     SDLK_SPACE},
	{"DEL",       SDLK_DELETE},
	{"KP0",       SDLK_KP_0},
	{"KP1",       SDLK_KP_1},
	{"KP2",       SDLK_KP_2},
	{"KP3",       SDLK_KP_3},
	{"KP4",       SDLK_KP_4},
	{"KP5",       SDLK_KP_5},
	{"KP6",       SDLK_KP_6},
	{"KP7",       SDLK_KP_7},
	{"KP8",       SDLK_KP_8},
	{"KP9",       SDLK_KP_9},
	{"KP0",       SDLK_KP_0},
	{"KP.",       SDLK_KP_PERIOD},
	{"KP/",       SDLK_KP_DIVIDE},
	{"KP*",       SDLK_KP_MULTIPLY},
	{"KP-",       SDLK_KP_MINUS},
	{"KP+",       SDLK_KP_PLUS},
	{"KP_ENTER",  SDLK_KP_ENTER},
	{"UP",        SDLK_UP},
	{"DOWN",      SDLK_DOWN},
	{"RIGHT",     SDLK_RIGHT},
	{"LEFT",      SDLK_LEFT},
	{"INSERT",    SDLK_INSERT},
	{"HOME",      SDLK_HOME},
	{"END",       SDLK_END},
	{"PAGEUP",    SDLK_PAGEUP},
	{"PAGEDOWN",  SDLK_PAGEDOWN},
	{"F1",        SDLK_F1},
	{"F2",        SDLK_F2},
	{"F3",        SDLK_F3},
	{"F4",        SDLK_F4},
	{"F5",        SDLK_F5},
	{"F6",        SDLK_F6},
	{"F7",        SDLK_F7},
	{"F8",        SDLK_F8},
	{"F9",        SDLK_F9},
	{"F10",       SDLK_F10},
	{"F11",       SDLK_F11},
	{"F12",       SDLK_F12},
	{"F13",       SDLK_F13},
	{"F14",       SDLK_F14},
	{"F15",       SDLK_F15}
};
}

namespace nswitch {
class Switch_Key_Map::Key_Map_Impl
{
public:
  void parse_line(const char * line_)
  {
    printf("got line %s\n", line_);
    std::string line(line_);
    auto args = split(line, '=');
    if (args.size() != 2)
    {
      printf("Bad line: %s\n", line_);
      return;
    }
  
    auto switch_keys = split(args[0], '-');
    size_t switch_key=0;
    for (auto str : switch_keys)
    {
      trim(str);
      bool valid=false;
      for (auto && key_map : Switch_Key_Mapping)
      {
        printf("Checking '%s' - '%s'\n", key_map.first.c_str(), str.c_str());
        if (key_map.first == str)
        {
          valid = true;
          switch_key |= (1 << key_map.second);
          break;
        }
      }
      if (!valid)
      {
        printf("Invalid key: %s\n", str.c_str());
        return;
      }
    }
  
    auto keyboard_key = split(args[1], '-');
    
    SDL_Keysym k;
    k.sym      = SDLK_UNKNOWN;
    k.mod      = KMOD_NONE;
  
    for (auto str : keyboard_key)
    {
      trim(str);
      if (str == "ALT")
      {
        k.mod = static_cast<SDL_Keymod>(k.mod | KMOD_ALT);
      }
      else if (str == "CTRL")
      {
        k.mod = static_cast<SDL_Keymod>(k.mod | KMOD_CTRL);
      }
      else if (str == "SHIFT")
      {
        k.mod = static_cast<SDL_Keymod>(k.mod | KMOD_SHIFT);
      }
      else
      {
  	if (str.length() == 0) {
            std::cout << "Keybinder: parse error in line: " << line << std::endl;
            return;
  	} else if (str.length() == 1) {
            // translate 1-letter keys straight to SDL_Keycode
            auto c = static_cast<unsigned char>(str[0]);
            if (std::isgraph(c) && c != '%' && c != '{' && c != '|' && c != '}' && c != '~') {
              c = std::tolower(c);	// need lowercase
              k.sym = static_cast<SDL_Keycode>(c);
            } else {
              std::cout << "Keybinder: unsupported key: " << str << std::endl;
              return;
            }
        } else {
          for (auto && pair : SDLKeyStringTable)
          {
            if (str == pair.first)
            {
              k.sym = pair.second;
              break;
            }
          }
        }
        if (k.sym == SDLK_UNKNOWN)
        {
          printf("Unknown key %s\n", str.c_str());
          return;
        }
      }
    }
    printf("Mapping %lu to %d.%d\n", switch_key, k.mod, k.sym);
    key_map_[switch_key] = k;
  }

  bool key_press(size_t key)
  {
    current_keys_ |= (1 << key);
    return send_event(SDL_KEYDOWN);
  }
  
  bool key_release(size_t key)
  {
    auto ret = send_event(SDL_KEYUP);
    current_keys_ &= ~(1 << key);
    return ret;
  }

private:
  bool send_event(int type)
  {
    auto itr = key_map_.find(current_keys_);
    if (itr == key_map_.end())
    {
      return false;
    }
    SDL_Event event;
    event.type = type;
    event.key.keysym = itr->second;
    if (type == SDL_KEYDOWN)
    {
      SDL_SetModState(static_cast<SDL_Keymod>(event.key.keysym.mod));
    }
    printf("Sending event %d - %d\n", event.key.keysym.sym, event.key.keysym.mod);
    SDL_PushEvent(&event);
    if (type == SDL_KEYUP)
    {
      SDL_SetModState(KMOD_NONE);
    }
    return true;
  }

  std::map<size_t, SDL_Keysym> key_map_;
  size_t current_keys_;
};

Switch_Key_Map::Switch_Key_Map()
{
  impl_ = std::make_unique<Key_Map_Impl>();
}

Switch_Key_Map::~Switch_Key_Map()
{
}
   
void 
Switch_Key_Map::
load_file(std::ifstream & keyfile)
{
  printf("Parsing file...\n");
  char temp[1024]; // 1024 should be long enough
  while (!keyfile.eof()) {
    printf("Read line\n");
    keyfile.getline(temp, 1024);
    printf("line: %s\n", temp);
    if (keyfile.gcount() >= 1023) {
      std::cout << "Keybinder: parse error: line too long. Skipping rest of file." << std::endl;
      break;
    }
    printf("Try parse\n");
    impl_->parse_line(temp);
  }
}

bool 
Switch_Key_Map::
event(SDL_Event const & event)
{
  if (!(event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP))
  {
    return false;
  }
  if (event.type == SDL_JOYBUTTONDOWN)
  {
    impl_->key_press(event.jbutton.button);
    return true;
  }
  else
  {
    impl_->key_release(event.jbutton.button);
    return true;
  }
}

}

extern "C" {
struct Switch_Key_Map
{
  Switch_Key_Map()
    : k(std::make_unique<nswitch::Switch_Key_Map>())
  {
  }

  std::unique_ptr<nswitch::Switch_Key_Map> k;
};

Switch_Key_Map * switch_keymap_create()
{
  printf("Creating keypmap\n");
  auto km = new Switch_Key_Map;
  return km;
}

int switch_keymap_load_from_file(Switch_Key_Map * km, char const * file)
{
  std::ifstream myfile;
  try {
    printf("Opening file %s\n", file);
    myfile.open(file);
    if (!myfile.is_open())
    {
      return -1;
    }
    km->k->load_file(myfile);
  } catch (std::exception const &) {
    printf("Got exception\n");
    return -1;
  }
  return true;
}

int switch_keymap_event(Switch_Key_Map * km, SDL_Event const * event)
{
  return km->k->event(*event);
}

void switch_keymap_destroy(Switch_Key_Map * km)
{
  delete km;
}

}
