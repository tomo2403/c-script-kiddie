#include <iostream>
#include "MenuHelper.h"
#include "ConsoleHelpers.h"

int main()
{
    bool isClosing = false;

    MenuHelper navigation;
    navigation.GoToMenu(0);

    char key;
    while (!isClosing)
    {
        std::cout << COLOR_BLUE;
        std::string input;
        std::cin >> input;
        std::cout << RESET_STYLE;

        if (input == "quit" || input == "exit")
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
                std::cout << STYLE_BOLD << COLOR_RED "Menü nicht verfügbar!"
                            << RESET_STYLE << STYLE_UNDERLINE << "\n\nGehe zu:" << RESET_STYLE << " ";
                break;
            default:
                navigation.GoToMenu(nav);
                break;
        }
    }
}