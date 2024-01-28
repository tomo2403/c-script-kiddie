#include <iostream>
#include <iomanip>
#include "Header/IOManager.h"
#include "Header/Mitarbeiterdatenbank.h"
#include "Header/Utilities.h"
#include "Header/ConsoleHelpers.h"

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
    return {"Hauptmenü", 0,
            {{'d', 4, "Mitarbeiterverzeichnis öffnen"},
             {'e', 2, "Datenbank exportieren"},
             {'i', 3, "Datenbank importieren"},
             {'c', 0, "Ansicht Bereinigen"},
             {'h', 1, "Hilfe anzeigen"}},
            {[]()
             {
                 std::cout << "Prüfungsleistung" << std::endl;
             }}, true
    };
}

Menu buildHelpMenu()
{
    return {"Hilfe", 0,
            {},
            {[]()
             {
                 std::cout << "Jedes Menü enthält eine Liste von Befehlen. " << std::endl
                           << "Diese Befehle können über das eingeben des Schlüssels ausgewählt werden. "
                           << std::endl
                           << R"(Um das Programm zu beenden, geben Sie "quit" oder "exit" ein.)" << std::endl;
             }}
    };
}

Menu buildMitarbeiterliste()
{
    return {"Mitarbeiterverzeichnis", 0,
            {{'s', 6, "Suche"},
             {'a', 7, "Hinzufügen"},
             {'d', 5, "Detailansicht"}},
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
             }}
    };
}

Menu buildSaveMenu()
{
    return {"Exportieren", 0,
            {},
            {[]()
             {
                 MitarbeiterDatenbank::serialisieren();
                 std::cout << "Gespeichert!" << std::endl;
             }}
    };
}

Menu buildLoadMenu()
{
    return {"Importieren", 0,
            {},
            {[]()
             {
                 MitarbeiterDatenbank::deserialisieren();
                 std::cout << "Geladen!" << std::endl;
             }}
    };
}

Menu buildMitarbeiterDetail()
{
    return {"Mitarbeiter Detailansicht", 4,
            {{'m', 8, "Gehalt erhöhen"},
             {'r', 9, "Entfernen"}},
            {[]()
             {
                 int mitarbeiterId;

                 if (Utilities::tryGetMitarbeiterId(mitarbeiterId))
                 {
                     Utilities::printMitarbeiter(mitarbeiterId);
                 }
                 else
                 {
                     Utilities::printWarning("Vorgang abgebrochen!");
                     MitarbeiterDatenbank::selectedId = 0;
                 }
             }}
    };
}

Menu buildSearchMenu()
{
    return {"Mitarbeiter suchen", 4,
            {{'s', 6, "Neue suche"}},
            {[]()
             {

             }}
    };
}

Menu buildAddMenu()
{
    return {"Mitarbeiter hinzufügen", 4,
            {},
            {[]()
             {
                 std::string name, vorname, plz, gehaltStr;
                 Utilities::inputMitarbeiter(name, vorname, plz, gehaltStr);
             }}
    };
}

Menu buildModifyMenu()
{
    return {"Gehalt erhöhen", 4,
            {},
            {[]()
             {
                 try
                 {
                     Mitarbeiter &mCurrent = MitarbeiterDatenbank::getMitarbeiter(MitarbeiterDatenbank::selectedId);
                     std::cout << "Mitarbeiter: " << mCurrent.name() << ", " << mCurrent.vorname() << std::endl << "Aktuelles Gehalt: "
                               << mCurrent.gehalt() << "€" << std::endl << std::endl << "Faktor: " << COLOR_BLUE;

                     std::string gehaltStr;
                     std::cin.ignore();
                     std::getline(std::cin, gehaltStr);

                     if (gehaltStr.empty())
                     {
                         Utilities::printWarning("Vorgang abgebrochen!");
                     }
                     else
                     {
                         double gehalt;
                         if (Utilities::tryParse(gehaltStr, gehalt))
                         {
                             std::cout << COLOR_YELLOW << mCurrent.gehalt() << "€" << COLOR_WHITE << "  -->  " << COLOR_GREEN
                                       << mCurrent.gehalt() * gehalt << "€" << std::endl << RESET_STYLE << std::endl;
                             if (Utilities::askQuestion("Änderungen speichern?", true))
                             {
                                 mCurrent.gehalt(gehalt);
                                 Utilities::printSuccess("\nÄnderungen gespeichert!");
                             }
                         }
                         else
                         {
                             Utilities::printError("Ungültige Eingabe!");
                         }
                     }
                 }
                 catch (std::out_of_range &)
                 {
                     Utilities::printError("Kein Mitarbeiter ausgewählt!");
                     return;
                 }
             }}
    };
}

Menu buildRemoveMenu()
{
    return {"Mitarbeiter entfernen", 4,
            {},
            {[]()
             {
                 try
                 {
                     Mitarbeiter &mCurrent = MitarbeiterDatenbank::getMitarbeiter(MitarbeiterDatenbank::selectedId);
                     std::cout << "Mitarbeiter: " << mCurrent.name() << ", " << mCurrent.vorname() << std::endl << "Wohnt in: "
                               << mCurrent.postleitzahl() << std::endl << std::endl;

                     std::cin.ignore();
                     if (Utilities::askQuestion("Mitarbeiter wirklich löschen?", false))
                     {
                         MitarbeiterDatenbank::loescheMitarbeiter(MitarbeiterDatenbank::selectedId);
                         Utilities::printSuccess("\nMitarbeiter gelöscht!");
                     }
                     else
                     {
                         Utilities::printWarning("Vorgang abgebrochen!");
                     }
                 }
                 catch (std::out_of_range &)
                 {
                     Utilities::printError("Kein Mitarbeiter ausgewählt!");
                     return;
                 }
             }}
    };
}