#include <utility>

#ifndef PRUEFUNG_KEYMAP_H
#define PRUEFUNG_KEYMAP_H

struct KeyMap
{
    unsigned char key;
    unsigned char menuId;
    std::string action;
};

#endif //PRUEFUNG_KEYMAP_H
