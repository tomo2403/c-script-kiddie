#include <utility>
#include "../Header/Menu.h"
#include "../Header/ConsoleHelpers.h"

Menu::Menu(std::string name, const std::vector<KeyMap> &keys, const std::function<void()> &codeToExecute)
        : _name(std::move(name)), keys(keys), codeToExecute(codeToExecute)
{ }

void Menu::Print()
{
    std::cout << STYLE_BOLD << COLOR_MAGENTA << _name << std::endl << std::endl << RESET_STYLE;

    codeToExecute();

    std::cout << COLOR_YELLOW << "\n\nNavigation:\n";
    for (auto &map: keys)
    {
        std::cout << "[" << map.key << "]\t" << map.action << std::endl;
    }
    std::cout << RESET_STYLE << std::endl << STYLE_UNDERLINE << "Gehe zu:" << RESET_STYLE << " ";
}

int Menu::GetNavigation(unsigned char key)
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
