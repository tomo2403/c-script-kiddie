#include <iomanip>
#include <iostream>
#include "../Header/ConsoleHelpers.h"
#include "../Header/Menu.h"
#include "../Header/IOManager.h"
#include "../Header//Utilities.h"

IOManager::IOManager(Menu menus[], int availableMenusCount) : _menus(menus), _availableMenusCount(availableMenusCount)
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
        if (menuId >= 0 && menuId < _availableMenusCount)
        {
            _menus[menuId].Print();
            _currentMenuId = menuId;
        }
        else
        {
            throw std::out_of_range("Menu ID is out of range");
        }
    }
    catch (const std::out_of_range &ex)
    {
        Utilities::printError(ex.what());
    }
}

void IOManager::printHeader()
{
    std::system("clear");
    std::cout << COLOR_CYAN << STYLE_BOLD << STYLE_UNDERLINE << std::setfill('=') << std::setw(10) << "=" << " MITARBEITERDATENBANK "
              << std::setfill('=') << std::setw(10) << "=" << std::setfill(' ') << std::endl << RESET_STYLE << std::endl;
}

std::string IOManager::getInput()
{
    std::cout << COLOR_BLUE;
    std::string input;
    std::cin >> input;
    std::cout << RESET_STYLE;
    return input;
}
