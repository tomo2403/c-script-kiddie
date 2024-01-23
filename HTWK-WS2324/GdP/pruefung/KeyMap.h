#ifndef PRUEFUNG_KEYMAP_H
#define PRUEFUNG_KEYMAP_H

#include <utility>

struct KeyMap
{
public:
    KeyMap(unsigned char key, unsigned char menuId, std::string action)
            : key(key), menuId(menuId), action(std::move(action))
    { }

    unsigned char key;
    unsigned char menuId;
    std::string action;
};

#endif //PRUEFUNG_KEYMAP_H
