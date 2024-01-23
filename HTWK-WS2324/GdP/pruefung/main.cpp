#include <iostream>
#include "InputManager.h"
#include "OutputManager.h"

int main()
{
    Menu availableMenus[] = {
            {Menu(MenuContent(
                    {
                            KeyMap('0', 0, "Zurück zum Hauptmenü"),
                            KeyMap('1', 1, "Mitarbeiterliste")
                    },
                    {([]()
                    {
                        std::cout << "Prüfungsleistung" << std::endl;
                    })}
            ), "Hauptmenü")},
            {Menu(MenuContent(
                    {
                            KeyMap('0', 0, "Zurück zum Hauptmenü")
                    },
                    {([]()
                    {
                        std::cout << "Liste aller Mitarbeiter" << std::endl;
                    })}
            ), "Mitarbeiterliste")}
    };

    OutputManager output(availableMenus);
    InputManager input(output);

    output.GoToMenu(0);
    while (input.Interact());

    return 0;
}