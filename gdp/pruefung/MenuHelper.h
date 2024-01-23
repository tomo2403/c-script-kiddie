#ifndef PRUEFUNG_MENUHELPER_H
#define PRUEFUNG_MENUHELPER_H

#include "Menu.h"
#include "exception"

std::vector<KeyMap> menu01Keys = {
        {'0', 0, "Zurück zum Hauptmenü"}
};

std::vector<std::string> menu01Lines = {
        "Wählen Sie ein Untermenü aus:",
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
            std::cerr << STYLE_BOLD << COLOR_RED "FATAL ERROR: " << menuId << " is not valid!" << RESET_STYLE << std::endl;
        }
        currentMenuId = menuId;
    }

private:
    int currentMenuId = 0;
    Menu menus[1] = {
            {Menu("Hauptmenü", menu01Keys, menu01Lines)}
    };
};

#endif //PRUEFUNG_MENUHELPER_H
