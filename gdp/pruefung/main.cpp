#include <iostream>
#include "Mitarbeiterdatenbank.h"
#include "MenuHelper.h"

int main()
{
    bool isClosing = false;
    bool errorOnLastRun = false;

    MenuHelper navigation;
    navigation.GoToMenu(0);

    char key;
    while (!isClosing)
    {
        std::string input;
        std::cin >> input;

        if (errorOnLastRun)
        {
            errorOnLastRun = false;
            navigation.GoToMenu(-1);
            continue;
        }
        else if (input == "quit")
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
                errorOnLastRun = true;
                break;
            default:
                navigation.GoToMenu(nav);
                break;
        }
    }
}