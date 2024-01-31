#include <utility>
#include <iostream>
#include <functional>
#include "../Header/Menu.hpp"
#include "../Header/ConsoleHelpers.hpp"

Menu::Menu(std::string  name, unsigned char parent, const std::vector<KeyMap>& keys, const std::function<void()>& codeToExecute,
           bool hideBackKey) : _name(std::move(name)), _keys(keys), _codeToExecute(codeToExecute), _parent(parent)
{
    if (!hideBackKey)
        _keys.push_back({' ', _parent, "Zurück"});
}

void Menu::Print() const
{
    std::cout << STYLE_BOLD << COLOR_MAGENTA << _name << std::endl << std::endl << RESET_STYLE;

    _codeToExecute();

    std::cout << COLOR_YELLOW << "\n\nNavigation:\n";
    for (const auto& map : _keys)
    {
        std::cout << "[" << map.key << "]\t" << map.action << std::endl;
    }
    std::cout << RESET_STYLE << std::endl << STYLE_UNDERLINE << "Gehe zu:" << RESET_STYLE << " ";
}

int Menu::GetNavigation(unsigned char key) const
{
    for (const auto& map : _keys)
    {
        if (map.key == key)
        {
            return map.menuId;
        }
    }
    return -1;
}

int Menu::GetParent() const
{
    return _parent;
}