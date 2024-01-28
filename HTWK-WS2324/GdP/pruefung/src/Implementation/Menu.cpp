#include <utility>
#include <iostream>
#include "../Header/Menu.h"
#include "../Header/ConsoleHelpers.h"

Menu::Menu(std::string name, unsigned char parent, const std::vector<KeyMap> &keys, const std::function<void()> &codeToExecute,
           bool hideBackKey)
        : _name(std::move(name)), _keys(keys), _codeToExecute(codeToExecute), _parent(parent)
{
    if (!hideBackKey)
        _keys.insert(_keys.end(), {' ', _parent, "Zurück"});
}

void Menu::Print()
{
    std::cout << STYLE_BOLD << COLOR_MAGENTA << _name << std::endl << std::endl << RESET_STYLE;

    _codeToExecute();

    std::cout << COLOR_YELLOW << "\n\nNavigation:\n";
    for (auto &map: _keys)
    {
        std::cout << "[" << map.key << "]\t" << map.action << std::endl;
    }
    std::cout << RESET_STYLE << std::endl << STYLE_UNDERLINE << "Gehe zu:" << RESET_STYLE << " ";
}

int Menu::GetNavigation(unsigned char key)
{
    for (auto &map: _keys)
    {
        if (map.key == key)
        {
            return map.menuId;
        }
    }
    return -1;
}

int Menu::GetParent()
{
    return _parent;
}