#ifndef PRUEFUNG_MENU_H
#define PRUEFUNG_MENU_H

#include <utility>
#include "MenuContent.h"
#include "KeyMap.h"
#include "ConsoleHelpers.h"

class Menu
{
public:
    explicit Menu(MenuContent content, std::string name) : _content(std::move(content)), _name(std::move(name))
    { }

    void Print()
    {
        std::cout << STYLE_BOLD << COLOR_MAGENTA << _name << std::endl << std::endl << RESET_STYLE;

        _content.codeToExecute();

        std::cout << COLOR_YELLOW << "\n\nNavigation:\n";
        for (auto &map: _content.keys)
        {
            std::cout << "[" << map.key << "]\t" << map.action << std::endl;
        }
        std::cout << RESET_STYLE << std::endl << STYLE_UNDERLINE << "Gehe zu:" << RESET_STYLE << " ";
    }

    int GetNavigation(unsigned char key)
    {
        for (auto &map: _content.keys)
        {
            if (map.key == key)
            {
                return map.menuId;
            }
        }
        return -1;
    }

private:
    std::string _name;
    MenuContent _content;
};

#endif //PRUEFUNG_MENU_H
