#include <switch/joymap.hpp>
#include <switch/keymap.hpp>
#include <switch/touch_to_mouse.hpp>
#include <switch/rstick_to_mouse.hpp>
#include <switch/string.hpp>
#include <SDL.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "SDL_mouse_internals.h"
#include <switch/keyboard.hpp>

#define KMOD_SWITCH_KEYBOARD (KMOD_RESERVED + 1)

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
  {"DDOWN", static_cast<int>(nswitch::Switch_Joy::DDOWN)},
  {"LSTICK_LEFT", static_cast<int>(nswitch::Switch_Joy::LSTICK_LEFT)},
  {"LSTICK_UP", static_cast<int>(nswitch::Switch_Joy::LSTICK_UP)},
  {"LSTICK_RIGHT", static_cast<int>(nswitch::Switch_Joy::LSTICK_RIGHT)},
  {"LSTICK_DOWN", static_cast<int>(nswitch::Switch_Joy::LSTICK_DOWN)},
  {"RSTICK_LEFT", static_cast<int>(nswitch::Switch_Joy::RSTICK_LEFT)},
  {"RSTICK_UP", static_cast<int>(nswitch::Switch_Joy::RSTICK_UP)},
  {"RSTICK_RIGHT", static_cast<int>(nswitch::Switch_Joy::RSTICK_RIGHT)},
  {"RSTICK_DOWN", static_cast<int>(nswitch::Switch_Joy::RSTICK_DOWN)},
  {"SL_LEFT", static_cast<int>(nswitch::Switch_Joy::SL_LEFT)},
  {"SR_LEFT", static_cast<int>(nswitch::Switch_Joy::SR_LEFT)},
  {"SL_RIGHT", static_cast<int>(nswitch::Switch_Joy::SL_RIGHT)},
  {"SR_RIGHT", static_cast<int>(nswitch::Switch_Joy::SR_RIGHT)}
};

auto SDLKeyStringTable = std::map<std::string, SDL_Keycode>{
        {"APPLICATION", SDLK_APPLICATION},
        {"BACKSPACE", SDLK_BACKSPACE},
        {"CAPSLOCK", SDLK_CAPSLOCK},
        {"DELETE", SDLK_DELETE},
        {"END", SDLK_END},
        {"ESCAPE", SDLK_ESCAPE},
        {"FIND", SDLK_FIND},
        {"HELP", SDLK_HELP},
        {"HOME", SDLK_HOME},
        {"INSERT", SDLK_INSERT},
        {"KP1", SDLK_KP_1},
        {"KP2", SDLK_KP_2},
        {"KP3", SDLK_KP_3},
        {"KP4", SDLK_KP_4},
        {"KP5", SDLK_KP_5},
        {"KP6", SDLK_KP_6},
        {"KP7", SDLK_KP_7},
        {"KP8", SDLK_KP_8},
        {"KP9", SDLK_KP_9},
        {"KPA", SDLK_KP_A},
        {"KP&", SDLK_KP_AMPERSAND},
        {"KP@", SDLK_KP_AT},
        {"KPB", SDLK_KP_B},
        {"KPBACKSPACE", SDLK_KP_BACKSPACE},
        {"KP:", SDLK_KP_COLON},
        {"KPD", SDLK_KP_D},
        {"KP/", SDLK_KP_DIVIDE},
        {"KPENTER", SDLK_KP_ENTER},
        {"KP=", SDLK_KP_EQUALS},
        {"KP-", SDLK_KP_MINUS},
        {"KP*", SDLK_KP_MULTIPLY},
        {"KP%", SDLK_KP_PERCENT},
        {"KP.", SDLK_KP_PERIOD},
        {"KP+", SDLK_KP_PLUS},
        {"SPACE", SDLK_KP_SPACE},
        {"TAB", SDLK_KP_TAB},
        {"LEFT ALT", SDLK_LALT},
        {"LEFT CTRL", SDLK_LCTRL},
        {"LEFT", SDLK_LEFT},
        {"LEFT GUI", SDLK_LGUI},
        {"LEFT SHIFT", SDLK_LSHIFT},
        {"PAGEDOWN", SDLK_PAGEDOWN},
        {"PAGEUP", SDLK_PAGEUP},
        {"PRINTSCREEN", SDLK_PRINTSCREEN},
        {"RIGHT ALT", SDLK_RALT},
        {"RIGHT CTRL", SDLK_RCTRL},
        {"RETURN", SDLK_RETURN},
        {"RETURN", SDLK_RETURN2},
        {"RIGHT GUI", SDL_SCANCODE_RGUI},
        {"RIGHT", SDLK_RIGHT},
        {"RIGHT SHIFT", SDLK_RSHIFT},
        {"SCROLLLOCK", SDLK_SCROLLLOCK},
        {"SELECT", SDLK_SELECT},
        {"SPACE", SDLK_SPACE},
        {"TAB", SDLK_TAB},
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
	{"F15",       SDLK_F15},
};
}

namespace nswitch {
class Switch_Key_Map::Key_Map_Impl
{
public:
  Key_Map_Impl(int screenx, int screeny)
    : screenx_(screenx)
    , screeny_(screeny)
  {
     auto mouse = SDL_GetMouse();
     printf("** INPUT: %d/%d\n", mouse->last_x, mouse->last_y);
     mouse->last_x = 0;
     mouse->last_y = 0;
     //int x; 
     //int y;
     //auto mouse = SDL_GetMouse();
     //SDL_GetWindowSize(mouse->focus, &x, &y);
     //SDL_SendMouseMotion(NULL, 0, SDL_FALSE, x, y);
     //mouse->last_x = x;
     //mouse->last_y = y;
     //mouse->x = x;
     //mouse->y = y;
  }
  
  Key_Map_Impl()
  {
  }

  bool true_false_setting(std::string const & str, std::vector<std::string> const & args, bool & value)
  {
    std::string arg1=args[0];
    std::string arg2=args[1];;
    trim(arg1);
    trim(arg2);
    if (arg1 == str)
    {
      if (arg2 == "TRUE")
      {
        value=true;
      }
      else if (arg2 == "FALSE")
      {
        value=false;
      }
      else
      {
        printf("Bad value for %s - %s\n", str.c_str(), args[1].c_str());
      }
      return true;
    }
    return false;
  }

  void set_arrows(std::string const & prefix)
  {
    parse_line(prefix + "UP=UP");
    parse_line(prefix + "DOWN=DOWN");
    parse_line(prefix + "RIGHT=RIGHT");
    parse_line(prefix + "LEFT=LEFT");
  }


  void parse_line(std::string const & line)
  {
    if (line.size() == 0)
    {
      return;
    }
    if (line[0] == '#')
    {
      return;
    }
    auto args = split(line, '=');
    if (args.size() != 2)
    {
      printf("Bad line: %s\n", line.c_str());
      return;
    }
    
    if (true_false_setting("DOUBLE_TOUCK_KEYBOARD", args, configs_[index_].double_touch_keyboard_))
    {
      return;
    }

    if (true_false_setting("RSTICK_MOUSE", args, configs_[index_].rstick_mouse_))
    {
      return;
    }
    bool touch_mouse=false;
    if (true_false_setting("TOUCH_MOUSE", args, touch_mouse))
    {
      if (touch_mouse)
      {
        SDL_GetMouse()->touch_mouse_events = SDL_TRUE;
      }
      return;
    }
    if (true_false_setting("TOUCH_MOUSE_ABS", args, configs_[index_].touch_mouse_))
    {
      return;
    }
    bool dpad_arrows=false;
    if (true_false_setting("DPAD_ARROWS", args, dpad_arrows))
    {
      if (dpad_arrows)
      {
        set_arrows("D");
      }
      return;
    }
    bool lstick_arrows=false;
    if (true_false_setting("LSTICK_ARROWS", args, dpad_arrows))
    {
      if (lstick_arrows)
      {
        set_arrows("LSTICK");
      }
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
        //printf("Checking '%s' - '%s'\n", key_map.first.c_str(), str.c_str());
        if (key_map.first == str)
        {
          valid = true;
          switch_key |= (1 << key_map.second);
          break;
        }
      }
      if (!valid)
      {
        //printf("Invalid key: %s\n", str.c_str());
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
      if (str == "KEYBOARD")
      {
        k.mod = static_cast<SDL_Keymod>(KMOD_SWITCH_KEYBOARD);
	break;
      }
      else if (str == "ALT")
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
            auto c = static_cast<unsigned char>(str[0]);
            k.sym = static_cast<SDL_Keycode>(c);
	    break;
        }
	auto itr = SDLKeyStringTable.find(str);
	if (itr == SDLKeyStringTable.end())
        {
          printf("Unknown key %s\n", str.c_str());
          return;
        }
	k.sym = itr->second;
      }
    }
    printf("Mapping %lu to %d.%d\n", switch_key, k.mod, k.sym);
    key_map()[switch_key] = k;
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

  void set_rstick(bool enabled)
  {
    configs_[index_].rstick_mouse_ = enabled;
  }

  void virtual_keyboard()
  {
    std::string txt = get_keyboard_input("");
    SDL_Event e;
    for (char ch : txt)
    {
      e.type = SDL_KEYDOWN;
      ch = std::tolower(ch);
      e.key.keysym.sym = static_cast<SDL_Keycode>(ch);
      SDL_PushEvent(&e);
      e.type = SDL_KEYUP;
      SDL_PushEvent(&e);
    }
    e.type = SDL_TEXTINPUT;
    strncpy(e.text.text, txt.c_str(), txt.size() > sizeof(e.text.text) ? sizeof(e.text.text) : txt.size());
    SDL_PushEvent(&e);
    
  }
 
  bool event(SDL_Event const & event)
  { 
    if (double_touch_keyboard() && event.type == SDL_FINGERDOWN)
    {
      int numFingers = 0;
      SDL_Finger* finger0 = SDL_GetTouchFinger(event.tfinger.touchId, 0);
      if (finger0) {
      	numFingers = SDL_GetNumTouchFingers(event.tfinger.touchId);
      }
      if (numFingers == 2)
      {
        virtual_keyboard();
      }
      return true;
    }
    if (touch_mouse() && touch_to_mouse(screenx_, screeny_, event, mouse_movement_))
    {
      return true;
    }
    else if (rstick_mouse() && rstick_to_mouse(event))
    {
      return true;
    } 
    else if (!(event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP))
    {
      //printf("Not joy button :(\n");
      return false;
    }
    //printf("Joy button: %d - %lu\n", event.jbutton.button, current_keys_);
    if (event.type == SDL_JOYBUTTONDOWN)
    {
      return key_press(event.jbutton.button);
    }
    else
    {
      return key_release(event.jbutton.button);
    }
    return false;
  }
  
  void mouse_movement(bool mouse_movement)
  {
    mouse_movement_ = mouse_movement;
  }

  void screen(size_t x, size_t y)
  {
    screenx_ = x;
    screeny_ = y;
  }
  
  void index(int index)
  {
    index_ = index;
  }

private:
  bool send_event(int type)
  {
    auto itr = key_map().find(current_keys_);
    if (itr == key_map().end())
    {
      printf("no key for: %lu\n", current_keys_);
      return false;
    }
    SDL_Event event;
    event.type = type;
    event.key.keysym = itr->second;
    if (event.key.keysym.mod == KMOD_SWITCH_KEYBOARD)
    {
      if (type == SDL_KEYDOWN)
      {
        virtual_keyboard();
      }
      return true;
    }
    if (type == SDL_KEYDOWN)
    {
      SDL_SetModState(static_cast<SDL_Keymod>(event.key.keysym.mod));
    }
    //printf("Sending event %d - %d\n", event.key.keysym.sym, event.key.keysym.mod);
    printf("Sending event: %d\n", event.key.keysym.sym);
    SDL_PushEvent(&event);
    if (type == SDL_KEYUP)
    {
      SDL_SetModState(KMOD_NONE);
    }
    return true;
  }

  using Switch_To_SDL = std::map<size_t, SDL_Keysym>;

  Switch_To_SDL & key_map()
  {
    return configs_[index_].key_map_;
  }
    
  /*size_t current_keys() const
  {
    return configs_[index_].current_keys_;
  }*/

  bool rstick_mouse() const
  {
    return configs_[index_].rstick_mouse_;
  }

  bool touch_mouse() const
  {
    return configs_[index_].touch_mouse_;
  }

  bool double_touch_keyboard() const
  {
    return configs_[index_].double_touch_keyboard_;
  }

  struct Key_Mapping_Config
  {
    std::map<size_t, SDL_Keysym> key_map_;
    bool rstick_mouse_=false;
    bool touch_mouse_=false;
    bool double_touch_keyboard_=false;
  };


  size_t index_=0;
  int screenx_=-1;
  int screeny_=-1;
  size_t current_keys_=0U;
  bool mouse_movement_=true;
  std::array<Key_Mapping_Config, 10> configs_;
};

Switch_Key_Map::Switch_Key_Map()
{
  impl_ = std::make_unique<Key_Map_Impl>();
}
   
Switch_Key_Map::Switch_Key_Map(int screenx, int screeny)
{
  impl_ = std::make_unique<Key_Map_Impl>(screenx, screeny);
}

Switch_Key_Map::~Switch_Key_Map()
{
}
   
void 
Switch_Key_Map::
load_file(std::ifstream & keyfile)
{
  //printf("Parsing file...\n");
  char temp[1024]; // 1024 should be long enough
  while (!keyfile.eof()) {
    //printf("Read line\n");
    keyfile.getline(temp, 1024);
    //printf("line: %s\n", temp);
    if (keyfile.gcount() >= 1023) {
      std::cout << "Keybinder: parse error: line too long. Skipping rest of file." << std::endl;
      break;
    }
    //printf("Try parse\n");
    impl_->parse_line(temp);
  }
}

bool 
Switch_Key_Map::
event(SDL_Event const & event)
{
  return impl_->event(event);
}
   
void 
Switch_Key_Map::
screen(int x, int y)
{
  impl_->screen(x,y);
}

void 
Switch_Key_Map::
mouse_movement(bool b)
{
  impl_->mouse_movement(b);
}

void 
Switch_Key_Map::
index(size_t i)
{
  impl_->index(i);
}

}

extern "C" {
struct Switch_Key_Map
{
  Switch_Key_Map()
    : k(std::make_unique<nswitch::Switch_Key_Map>())
  {
  }
  
  Switch_Key_Map(int screenx, int screeny)
    : k(std::make_unique<nswitch::Switch_Key_Map>(screenx, screeny))
  {
  }

  auto operator->()
  {
    return k.get();
  }

  std::unique_ptr<nswitch::Switch_Key_Map> k;
};

Switch_Key_Map * switch_keymap_create()
{
  //printf("Creating keypmap\n");
  auto km = new Switch_Key_Map;
  return km;
}

int switch_keymap_load_from_file(Switch_Key_Map * km, char const * file)
{
  std::ifstream myfile;
  try {
    //printf("Opening file %s\n", file);
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

void switch_keymap_set_mouse_movement(Switch_Key_Map * km, int x)
{
  (*km)->mouse_movement(x);
}

void switch_keymap_set_index(Switch_Key_Map * km, int x)
{
  (*km)->index(x);
}

void switch_keymap_set_screen(Switch_Key_Map * km, int x, int y)
{
  (*km)->screen(x, y);
}

int switch_keymap_event(Switch_Key_Map * km, SDL_Event const * event)
{
  return (*km)->event(*event);
}

void switch_keymap_destroy(Switch_Key_Map * km)
{
  delete km;
}



}
