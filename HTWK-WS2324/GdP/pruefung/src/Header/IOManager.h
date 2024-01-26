#ifndef PRUEFUNG_IOMANAGER_H
#define PRUEFUNG_IOMANAGER_H

#include "Menu.h"

class IOManager
{
public:
    explicit IOManager(Menu menus[], int availableMenusCount);

    Menu CurrentMenu();

    bool Interact();
    void GoToMenu(int menuId);

private:
    int _currentMenuId = 0;
    const int _availableMenusCount;
    Menu *_menus;

    static void printHeader();
    static std::string getInput();
};

#endif //PRUEFUNG_IOMANAGER_H
