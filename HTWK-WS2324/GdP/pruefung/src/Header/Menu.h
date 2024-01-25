#ifndef PRUEFUNG_MENU_H
#define PRUEFUNG_MENU_H

#include "KeyMap.h"

class Menu
{
public:
    Menu(std::string name, const std::vector<KeyMap> &keys, const std::function<void()> &codeToExecute);

    void Print();
    int GetNavigation(unsigned char key);

private:
    std::string _name;
    std::vector<KeyMap> keys;
    std::function<void()> codeToExecute;
};

#endif //PRUEFUNG_MENU_H
