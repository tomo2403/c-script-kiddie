#ifndef PRUEFUNG_MENU_H
#define PRUEFUNG_MENU_H

#include "KeyMap.h"

class Menu
{
public:
    Menu(std::string name, unsigned char parent, const std::vector<KeyMap> &keys, const std::function<void()> &codeToExecute, bool hideBackKey = false);

    void Print();
    int GetNavigation(unsigned char key);
    int GetParent() const;

private:
    std::string _name;
    unsigned char _parent;
    std::vector<KeyMap> _keys;
    std::function<void()> _codeToExecute;
};

#endif //PRUEFUNG_MENU_H
