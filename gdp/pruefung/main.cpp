#include <iostream>
#include "Mitarbeiterdatenbank.h"
#include "MenuHelper.h"

int main()
{
    bool isClosing = false;

    MenuHelper navigation;
    navigation.GoToMenu(0);
    navigation.GoToMenu(21345);

    char key;
    while (!isClosing)
    {
        std::string input;
        std::cin >> input;

        if (input == "quit")
        {
            isClosing = true;
            continue;
        }
        else
        {
            key = input[0];
        }

        int nav = navigation.CurrentMenu().GetNavigation(key);

        switch (nav)
        {
            case -1:
                std::cout << "Menu nicht verfügbar!" << std::endl;
                break;
            default:
                navigation.GoToMenu(nav);
                break;
        }
    }
}