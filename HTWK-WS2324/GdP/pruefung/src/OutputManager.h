#ifndef PRUEFUNG_OUTPUTMANAGER_H
#define PRUEFUNG_OUTPUTMANAGER_H

#include <utility>
#include "Menu.h"
#include "exception"

class OutputManager
{
public:
    explicit OutputManager(Menu menus[]) : _menus(menus)
    { }

    Menu CurrentMenu()
    {
        return _menus[_currentMenuId];
    }

    void GoToMenu(int menuId)
    {
        menuId = menuId == -1 ? _currentMenuId : menuId;

        printHeader();

        try
        {
            _menus[menuId].Print();
        }
        catch (...)
        {
            std::cout << STYLE_BOLD << COLOR_RED "FATAL ERROR: " << menuId << " is not valid!" << RESET_STYLE
                      << std::endl;
        }
        _currentMenuId = menuId;
    }

private:
    int _currentMenuId = 0;
    Menu *_menus;

    static void printHeader()
    {
        std::system("clear");
        std::cout << COLOR_CYAN << STYLE_BOLD << STYLE_UNDERLINE << "===== MITARBEITERDATENBANK =====" << std::endl;
        std::cout << RESET_STYLE << std::endl;
    }
};

#endif //PRUEFUNG_OUTPUTMANAGER_H
