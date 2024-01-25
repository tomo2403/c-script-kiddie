#include <iostream>
#include "Implementation/IOManager.cpp"
#include "Implementation/Mitarbeiterdatenbank.cpp"

int main()
{
    Menu availableMenus[] = {
            {Menu("Hauptmenü",
                  {{'0', 0, "Ansicht Bereinigen"},
                   {'1', 1, "Hilfe"},
                   {'2', 2, "Mitarbeiterliste"}},
                  {[]()
                   {
                       std::cout << "Prüfungsleistung" << std::endl;
                   }})},
            {Menu("Hilfe",
                  {{'0', 0, "Zurück zum Hauptmenü"}},
                  {[]()
                   {
                       std::cout << "Jedes Menü enthält eine Liste von Befehlen. " << std::endl
                                 << "Diese Befehle können über das eingeben des Schlüssels ausgewählt werden. "
                                 << std::endl
                                 << R"(Um das Programm zu beenden, geben Sie "quit" oder "exit" ein.)" << std::endl;
                   }})},
            {Menu("Mitarbeiterliste",
                  {{'0', 0, "Zurück zum Hauptmenü"}},
                  {[]()
                   {
                       std::map<int, Mitarbeiter> mitarbeiterMap = MitarbeiterDatenbank::alleMitarbeiter();
                       int maxIdWidth = 0, maxNameWidth = 0, maxVornameWidth = 0, maxPLZWidth = 0, maxGehaltWidth = 0, maxTotalWidth = 0;
                       for (auto &entry: mitarbeiterMap)
                       {
                           Mitarbeiter &mitarbeiter = entry.second;
                           maxIdWidth = 2 + std::max(maxIdWidth, static_cast<int>(std::to_string(entry.first).length()));
                           maxNameWidth = 2 + std::max(maxNameWidth, static_cast<int>(mitarbeiter.name().length()));
                           maxVornameWidth = 2 + std::max(maxVornameWidth, static_cast<int>(mitarbeiter.vorname().length()));
                           maxPLZWidth = 2 + std::max(maxPLZWidth, static_cast<int>(mitarbeiter.postleitzahl().length()));
                           maxGehaltWidth = 2 + std::max(maxGehaltWidth,
                                                         static_cast<int>(std::to_string(static_cast<int>(mitarbeiter.gehalt())).length()));
                       }

                       maxIdWidth = std::max(10, maxIdWidth);
                       maxNameWidth = std::max(20, maxNameWidth);
                       maxVornameWidth = std::max(20, maxVornameWidth);
                       maxPLZWidth = std::max(15, maxPLZWidth);
                       maxGehaltWidth = std::max(15, maxGehaltWidth);
                       maxTotalWidth = maxIdWidth + maxNameWidth + maxVornameWidth + maxPLZWidth + maxGehaltWidth;

                       // Tabellenüberschrift
                       std::cout << std::setw(maxIdWidth) << "ID" << std::setw(maxNameWidth) << "Name"
                                 << std::setw(maxVornameWidth) << "Vorname" << std::setw(maxPLZWidth) << "PLZ"
                                 << std::setw(maxGehaltWidth) << "Gehalt" << std::endl;
                       std::cout << std::setfill('-') << std::setw(maxTotalWidth) << "-" << std::setfill(' ') << std::endl;

                       // Mitarbeiterdaten ausgeben
                       for (auto &entry: mitarbeiterMap)
                       {
                           Mitarbeiter &mitarbeiter = entry.second;
                           std::cout << std::setw(maxIdWidth) << entry.first << std::setw(maxNameWidth) << mitarbeiter.name()
                                     << std::setw(maxVornameWidth) << mitarbeiter.vorname()
                                     << std::setw(maxPLZWidth) << mitarbeiter.postleitzahl()
                                     << std::setw(maxGehaltWidth) << mitarbeiter.gehalt() << std::setw(0) << std::endl;
                       }
                   }})}
    };

    MitarbeiterDatenbank::Init("mitarbeiter.csv", ';', 0);

    //Test Daten
    MitarbeiterDatenbank::neuerMitarbeiter("Mustermann", "Max", "12345", 50000.0);
    MitarbeiterDatenbank::neuerMitarbeiter("Musterfrau", "Maria", "54321", 60000.0);
    MitarbeiterDatenbank::neuerMitarbeiter("Doe", "John", "98765", 55000.0);
    MitarbeiterDatenbank::neuerMitarbeiter("Schmidt", "Anna", "67890", 52000.0);
    MitarbeiterDatenbank::neuerMitarbeiter("Mueller", "Peter", "23456", 48000.0);

    IOManager ioManager(availableMenus);
    ioManager.GoToMenu(0);
    while (ioManager.Interact());

    return 0;
}