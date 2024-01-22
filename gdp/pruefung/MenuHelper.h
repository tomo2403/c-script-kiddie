#ifndef PRUEFUNG_MENUHELPER_H
#define PRUEFUNG_MENUHELPER_H

#include "Menu.h"
#include "exception"

std::vector<KeyMap> menu01Keys = {
        {'0', 0, "Zurueck zum Hauptmenue"}
};

std::vector<std::string> menu01Lines = {
        "Waehlen Sie ein Untermenue aus:",
};

class MenuHelper
{
public:
    Menu CurrentMenu()
    {
        return menus[currentMenuId];
    }

    void GoToMenu(int menuId)
    {
        menuId = menuId == -1 ? currentMenuId : menuId;

        std::system("clear");
        std::cout << "SOFTWARE NAME" << std::endl;
        std::cout << std::endl;

        try
        {
            menus[menuId].Print();
        }
        catch (...)
        {
            std::cerr << "\\033[1;31mFATAL ERROR: " << menuId << " is not valid! \\033[0m" << std::endl;
        }
        currentMenuId = menuId;
    }

private:
    int currentMenuId = 0;
    Menu menus[1] = {
            {Menu("Hauptmenue", menu01Keys, menu01Lines)}
    };
};

#endif //PRUEFUNG_MENUHELPER_H
