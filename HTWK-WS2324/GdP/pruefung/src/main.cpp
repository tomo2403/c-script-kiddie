#include <iostream>
#include <iomanip>
#include "Implementation/IOManager.cpp"
#include "Implementation/Mitarbeiterdatenbank.cpp"
#include "Implementation/Utilities.cpp"

Menu buildMainMenu();

Menu buildHelpMenu();

Menu buildSaveMenu();

Menu buildLoadMenu();

Menu buildMitarbeiterliste();

Menu buildMitarbeiterDetail();

Menu buildSearchMenu();

Menu buildAddMenu();

Menu buildModifyMenu();

Menu buildRemoveMenu();

int main(int argc, char *argv[])
{
    const int availableMenusCount = 10;
    Menu availableMenus[availableMenusCount] = {
            {buildMainMenu()},
            {buildHelpMenu()},
            {buildSaveMenu()},
            {buildLoadMenu()},
            {buildMitarbeiterliste()},
            {buildMitarbeiterDetail()},
            {buildSearchMenu()},
            {buildAddMenu()},
            {buildModifyMenu()},
            {buildRemoveMenu()}
    };

    MitarbeiterDatenbank::Init("mitarbeiter.csv", ';', 0);

    for (int i = 0; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "-d") == 0 || std::strcmp(argv[i], "--demo") == 0)
        {
            //Test Daten
            MitarbeiterDatenbank::neuerMitarbeiter("Mustermann", "Max", "12345", 50000.0);
            MitarbeiterDatenbank::neuerMitarbeiter("Musterfrau", "Maria", "54321", 60000.0);
            MitarbeiterDatenbank::neuerMitarbeiter("Doe", "John", "98765", 55000.0);
            MitarbeiterDatenbank::neuerMitarbeiter("Schmidt", "Anna", "67890", 52000.0);
            MitarbeiterDatenbank::neuerMitarbeiter("Mueller", "Peter", "23456", 48000.0);
        }
    }

    IOManager ioManager(availableMenus, availableMenusCount);
    ioManager.GoToMenu(0);
    while (ioManager.Interact());

    return 0;
}

Menu buildMainMenu()
{
    return {"Hauptmenü",
            {{'d', 4, "Mitarbeiterverzeichnis öffnen"},
             {'e', 2, "Datenbank exportieren"},
             {'i', 3, "Datenbank importieren"},
             {'c', 0, "Ansicht Bereinigen"},
             {'h', 1, "Hilfe anzeigen"}},
            {[]()
             {
                 std::cout << "Prüfungsleistung" << std::endl;
             }}};
}

Menu buildHelpMenu()
{
    return {"Hilfe",
            {{'b', 0, "Zurück"}},
            {[]()
             {
                 std::cout << "Jedes Menü enthält eine Liste von Befehlen. " << std::endl
                           << "Diese Befehle können über das eingeben des Schlüssels ausgewählt werden. "
                           << std::endl
                           << R"(Um das Programm zu beenden, geben Sie "quit" oder "exit" ein.)" << std::endl;
             }}};
}

Menu buildMitarbeiterliste()
{
    return {"Mitarbeiterverzeichnis",
            {{'s', 6, "Suche"},
             {'a', 7, "Hinzufügen"},
             {'d', 5, "Detailansicht"},
             {'b', 0, "Zurück"}},
            {[]()
             {
                 std::map<int, Mitarbeiter> mitarbeiterMap = MitarbeiterDatenbank::alleMitarbeiter();
                 int maxIdWidth = 0, maxNameWidth = 0, maxVornameWidth = 0, maxPLZWidth = 0, maxGehaltWidth = 0, maxTotalWidth = 0;
                 Utilities::measureTableContents(mitarbeiterMap, maxIdWidth, maxNameWidth, maxVornameWidth, maxPLZWidth, maxGehaltWidth,
                                                 maxTotalWidth);

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
             }}};
}

Menu buildSaveMenu()
{
    return {"Exportieren",
            {{'b', 0, "Zurück"}},
            {[]()
             {
                 MitarbeiterDatenbank::serialisieren();
                 std::cout << "Gespeichert!" << std::endl;
             }}};
}

Menu buildLoadMenu()
{
    return {"Importieren",
            {{'b', 0, "Zurück"}},
            {[]()
             {
                 MitarbeiterDatenbank::deserialisieren();
                 std::cout << "Geladen!" << std::endl;
             }}};
}

Menu buildMitarbeiterDetail()
{
    return {"Mitarbeiter Detailansicht",
            {{'m', 8, "Bearbeiten"},
             {'r', 9, "Entfernen"},
             {'b', 4, "Zurück"}},
            {[]()
             {

             }}};
}

Menu buildSearchMenu()
{
    return {"Mitarbeiter suchen",
            {{'s', 6, "Neue suche"},
             {'b', 4, "Zurück"}},
            {[]()
             {

             }}};
}

Menu buildAddMenu()
{
    return {"Mitarbeiter hinzufügen",
            {{'b', 4, "Zurück"}},
            {[]()
             {

             }}};
}

Menu buildModifyMenu(){
    return {"Mitarbeiter bearbeiten",
            {{'b', 5, "Zurück"}},
            {[]()
             {

             }}};
}

Menu buildRemoveMenu(){
    return {"Mitarbeiter entfernen",
            {{'b', 5, "Zurück"}},
            {[]()
             {

             }}};
}