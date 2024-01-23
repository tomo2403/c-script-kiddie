#ifndef PRUEFUNG_MENUCONTENT_H
#define PRUEFUNG_MENUCONTENT_H

#include <iostream>
#include "KeyMap.h"

struct MenuContent
{
public:
    MenuContent(const std::vector<KeyMap> &keys, const std::function<void()> &codeToExecute)
            : keys(keys), codeToExecute(codeToExecute)
    { }

    std::vector<KeyMap> keys;
    std::function<void()> codeToExecute;
};

#endif //PRUEFUNG_MENUCONTENT_H
