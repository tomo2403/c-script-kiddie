#ifndef PRUEFUNG_MENU_H
#define PRUEFUNG_MENU_H

#include <utility>

#include "KeyMap.h"
#include "ConsoleHelpers.h"

class Menu
{
public:
    Menu(std::string name, std::vector<KeyMap> keys, std::vector<std::string> displayLines)
            : name(std::move(name)), keys(std::move(keys)), displayLines(std::move(displayLines))
    { }

    std::string name;
    std::vector<KeyMap> keys;

    void Print()
    {
        for (const auto &displayLine: displayLines)
        {
            std::cout << displayLine << std::endl;
        }

        for (auto &map: keys)
        {
            std::cout << "[" << map.key << "]\t" << map.action << std::endl;
        }
        std::cout << std::endl << STYLE_UNDERLINE << "Gehe zu:" << RESET_STYLE << " ";
    }

    int GetNavigation(unsigned char key)
    {
        for (auto &map: keys)
        {
            if (map.key == key)
            {
                return map.menuId;
            }
        }
        return -1;
    }

protected:
    std::vector<std::string> displayLines;
};

#endif //PRUEFUNG_MENU_H
