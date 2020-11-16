#include "switch/keyboard.hpp"
#include <switch.h>

namespace nswitch {
std::string get_keyboard_input(std::string const & default_str)
{
    SwkbdConfig kbd;
    unsigned int str_len = 256;
    if (R_SUCCEEDED(swkbdCreate(&kbd, 0)))
    {
        swkbdConfigMakePresetDefault(&kbd);
        swkbdConfigSetInitialText(&kbd, default_str.c_str());
        swkbdConfigSetStringLenMax(&kbd, str_len);
        //swkbdConfigSetHeaderText(&kbd, "Header Text");
        //swkbdConfigSetSubText(&kbd, "SubText");
        //swkbdConfigSetGuideText(&kbd, "Guide Text");
        char keyboard_chars[str_len];
        Result res = swkbdShow(&kbd, keyboard_chars, str_len);
        swkbdClose(&kbd);
        if (R_SUCCEEDED(res))
        {
            //std::cout << (std::string("kbd out: ") + keyboard_chars);
            std::string str = keyboard_chars;
            return str;
        }
    }
    return default_str;
}
}
