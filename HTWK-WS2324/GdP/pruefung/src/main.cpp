#include <iostream>
#include "Implementation/IOManager.cpp"
#include "Implementation/Mitarbeiterdatenbank.cpp"

int main()
{
    Menu availableMenus[] = {
            {Menu("Hauptmenü",
                  {{'0', 0, "Zurück zum Hauptmenü"},
                   {'1', 1, "Mitarbeiterliste"}},
                  {([]()
                  {
                      std::cout << "Prüfungsleistung" << std::endl;
                  })})},
            {Menu("Mitarbeiterliste",
                  {{'0', 0, "Zurück zum Hauptmenü"}},
                  {([]()
                  {
                      std::cout << "Liste aller Mitarbeiter" << std::endl;
                  })})}};

    IOManager ioManager(availableMenus);
    ioManager.GoToMenu(0);
    while (ioManager.Interact());

    return 0;
}