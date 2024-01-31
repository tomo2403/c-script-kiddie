#include <iostream>
#include "Header/IOManager.hpp"
#include "Header/Mitarbeiterdatenbank.hpp"
#include "Header/Utilities.hpp"
#include "Header/ConsoleHelpers.hpp"

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
    //Ansichten vorbereiten
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

    //Ein- & Ausgabe vorbereiten
    IOManager ioManager(availableMenus, availableMenusCount);
    ioManager.GoToMenu(0);

    //Auf Benutzerinteraktion reagieren
    while (ioManager.Interact());

    return 0;
}

Menu buildMainMenu()
{
    return {"Hauptmenü", 0,
            {{'o', 4, "Mitarbeiterverzeichnis öffnen"},
             {'e', 2, "Datenbank exportieren"},
             {'i', 3, "Datenbank importieren"},
             {'h', 1, "Hilfe anzeigen"}},
            {[]()
             {
                 std::cout << STYLE_UNDERLINE "HTWK Leipzig, Wintersemester 2023/24" << RESET_UNDERLINE << std::endl
                           << "[C963] Grundlagen der Programmierung\n" << std::endl
                           << STYLE_BOLD << "Prüfungsleistung von Tom Mohr" << RESET_BOLD << std::endl;
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
                           << "Diese Befehle können über das Eingeben des Schlüssels ausgewählt werden. " << std::endl
                           << std::endl
                           << R"(Zum Importieren von Demodaten, Programm mit "-d" oder "--demo" starten.)" << std::endl
                           << "Um ein Menü zu schließen, Eingabetaste verwenden." << std::endl
                           << R"(Um das Programm zu beenden, "exit" eingeben.)" << std::endl;
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
                 Utilities::printMitarbeiterTable(mitarbeiterMap);
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
            {{'s', 6, "Neue suche"},
             {'d', 5, "Mitarbeiter öffnen"}},
            {[]()
             {
                 Utilities::printWarning("Groß- und Kleinschreibung wird berücksichtigt!\n");

                 std::string name, vorname;
                 std::cout << "Name enthält: ";
                 name = Utilities::getInput();
                 std::cout << "Vorname enthält: ";
                 vorname = Utilities::getInput();

                 std::vector<int> mitarbeiter = MitarbeiterDatenbank::findeMitarbeiter(name, vorname);

                 std::cout << std::endl << STYLE_UNDERLINE << "Treffer IDs:" << RESET_UNDERLINE << std::endl;
                 for (int i: mitarbeiter)
                 {
                     std::cout << i << std::endl;
                 }
             }}
    };
}

Menu buildAddMenu()
{
    return {"Mitarbeiter hinzufügen", 4,
            {},
            {[]()
             {
                 double gehalt;
                 std::string name, vorname, plz, gehaltStr;
                 Utilities::inputMitarbeiter(name, vorname, plz, gehaltStr, gehalt);

                 std::cout << RESET_STYLE << std::endl << std::endl;
                 std::cout << STYLE_UNDERLINE << "Eingaben überprüfen:" << RESET_UNDERLINE << std::endl;
                 Utilities::printMitarbeiter({name, vorname, plz, gehalt});

                 std::cin.ignore();
                 if (Utilities::askQuestion("Mitarbeiter hinzufügen?", true))
                 {
                     MitarbeiterDatenbank::neuerMitarbeiter(name, vorname, plz, gehalt);
                     Utilities::printSuccess("\nMitarbeiter hinzugefügt!");
                 }
                 else
                 {
                     Utilities::printWarning("Vorgang abgebrochen!");
                 }
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

                     std::string factorStr;
                     std::getline(std::cin, factorStr);

                     if (factorStr.empty())
                     {
                         Utilities::printWarning("Vorgang abgebrochen!");
                     }
                     else
                     {
                         Utilities::handleSalaryChange(mCurrent, factorStr);
                     }
                 }
                 catch (std::out_of_range &)
                 {
                     Utilities::printError("Kein Mitarbeiter ausgewählt!");
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
                 }
             }}
    };
}