#include "Menu.cpp"
#include "../Header/IOManager.h"

IOManager::IOManager(Menu menus[]) : _menus(menus)
{ }

Menu IOManager::CurrentMenu()
{
    return _menus[_currentMenuId];
}

bool IOManager::Interact()
{
    std::string input = getInput();

    if (input == "quit" || input == "exit")
    {
        return false;
    }
    else
    {
        char key = input[0];
        int nav = CurrentMenu().GetNavigation(key);

        if (nav == -1)
        {
            std::cout << STYLE_BOLD << COLOR_RED << "Menü nicht verfügbar!"
                      << RESET_STYLE << STYLE_UNDERLINE << "\n\nGehe zu:" << RESET_STYLE << " ";
        }
        else
        {
            GoToMenu(nav);
        }
    }

    return true;
}

void IOManager::GoToMenu(int menuId)
{
    menuId = menuId == -1 ? _currentMenuId : menuId;

    printHeader();

    try
    {
        _menus[menuId].Print();
    }
    catch (...)
    {
        std::cout << STYLE_BOLD << COLOR_RED << "FATAL ERROR: " << menuId << " is not valid!" << RESET_STYLE
                  << std::endl;
    }
    _currentMenuId = menuId;
}

void IOManager::printHeader()
{
    std::system("clear");
    std::cout << COLOR_CYAN << STYLE_BOLD << STYLE_UNDERLINE << "===== MITARBEITERDATENBANK =====" << std::endl;
    std::cout << RESET_STYLE << std::endl;
}

std::string IOManager::getInput()
{
    std::cout << COLOR_BLUE;
    std::string input;
    std::cin >> input;
    std::cout << RESET_STYLE;
    return input;
}
