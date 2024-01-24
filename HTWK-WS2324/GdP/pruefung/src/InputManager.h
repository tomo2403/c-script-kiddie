#ifndef PRUEFUNG_INPUTMANAGER_H
#define PRUEFUNG_INPUTMANAGER_H

#include <iostream>
#include "OutputManager.h"
#include "ConsoleHelpers.h"

class InputManager
{
public:
    explicit InputManager(OutputManager &menuManager) : _output(menuManager)
    { }

    bool Interact()
    {
        std::string input = getInput();

        if (input == "quit" || input == "exit")
        {
            return false;
        }
        else
        {
            char key = input[0];
            int nav = _output.CurrentMenu().GetNavigation(key);

            if (nav == -1)
            {
                std::cout << STYLE_BOLD << COLOR_RED "Menü nicht verfügbar!"
                          << RESET_STYLE << STYLE_UNDERLINE << "\n\nGehe zu:" << RESET_STYLE << " ";
            }
            else
            {
                _output.GoToMenu(nav);
            }
        }

        return true;
    }

private:
    OutputManager &_output;

    static std::string getInput()
    {
        std::cout << COLOR_BLUE;
        std::string input;
        std::cin >> input;
        std::cout << RESET_STYLE;
        return input;
    }
};

#endif //PRUEFUNG_INPUTMANAGER_H
