#include <iostream>
#include <iomanip>
#include "../Header/ConsoleHelpers.h"
#include "../Header/Menu.h"
#include "../Header/IOManager.h"
#include "../Header/Utilities.h"

const int MAX_HEADER_WIDTH = 10;

IOManager::IOManager(Menu menus[], int availableMenusCount) : _menus(menus), _availableMenusCount(availableMenusCount), _currentMenuId(0)
{ }

Menu &IOManager::CurrentMenu() const
{
    return _menus[_currentMenuId];
}

bool IOManager::Interact()
{
    std::string input = Utilities::getInput();

    if (input.empty())
    {
        GoToMenu(CurrentMenu().GetParent());
    }
    else if (input == "exit")
    {
        return false;
    }
    else
    {
        char key = input[0];
        int nav = CurrentMenu().GetNavigation(key);

        if (nav == -1)
        {
            std::cout << STYLE_BOLD << COLOR_RED << "Menü nicht verfügbar!" << RESET_STYLE << STYLE_UNDERLINE << "\n\nGehe zu:"
                      << RESET_STYLE << " ";
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
    menuId = (menuId == -1) ? _currentMenuId : menuId;

    printHeader();

    if (isValidMenuId(menuId))
    {
        _currentMenuId = menuId;
        _menus[menuId].Print();
    }
    else
    {
        Utilities::printError("Ungültige Menu-ID");
    }
}

void IOManager::printHeader()
{
    clearScreen();
    std::cout << COLOR_CYAN << STYLE_BOLD << STYLE_UNDERLINE << std::setfill('=') << std::setw(MAX_HEADER_WIDTH) << "="
              << " MITARBEITERDATENBANK " << std::setfill('=') << std::setw(MAX_HEADER_WIDTH) << "=" << std::setfill(' ') << std::endl
              << RESET_STYLE << std::endl;
}

void IOManager::clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

bool IOManager::isValidMenuId(int menuId) const
{
    return (menuId >= 0 && menuId < _availableMenusCount);
}
