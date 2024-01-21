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

        try
        {
            std::cout << "\033[2J\033[H";
            std::cout << "SOFTWARE NAME" << std::endl;
            std::cout << std::endl;

            menus[menuId].Print();
        }
        catch (std::out_of_range &ex)
        {

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
