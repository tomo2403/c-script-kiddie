#include <iostream>
#include <cstring>
#include "IOManager.hpp"
#include "Mitarbeiterdatenbank.hpp"
#include "MenuBuilder.hpp"

int main(int argc, char *argv[])
{
	//Datenbank initialisieren
	MitarbeiterDatenbank _db("mitarbeiter.csv", ';', 0);
	
    //Ansichten vorbereiten
    const int availableMenusCount = 10;
    Menu availableMenus[availableMenusCount] = {
            {MenuBuilder::buildMainMenu()},
            {MenuBuilder::buildHelpMenu()},
            {MenuBuilder::buildSaveMenu(&_db)},
            {MenuBuilder::buildLoadMenu(&_db)},
            {MenuBuilder::buildMitarbeiterliste(&_db)},
            {MenuBuilder::buildMitarbeiterDetail(&_db)},
            {MenuBuilder::buildSearchMenu(&_db)},
            {MenuBuilder::buildAddMenu(&_db)},
            {MenuBuilder::buildModifyMenu(&_db)},
            {MenuBuilder::buildRemoveMenu(&_db)}
    };

    for (int i = 0; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "-d") == 0 || std::strcmp(argv[i], "--demo") == 0)
        {
            //Test Daten
            _db.neuerMitarbeiter("Mustermann", "Max", "12345", 50000.0);
			_db.neuerMitarbeiter("Musterfrau", "Maria", "54321", 60000.0);
			_db.neuerMitarbeiter("Doe", "John", "98765", 55000.0);
			_db.neuerMitarbeiter("Schmidt", "Anna", "67890", 52000.0);
			_db.neuerMitarbeiter("Mueller", "Peter", "23456", 48000.0);
        }
    }

    //Ein- & Ausgabe vorbereiten
    IOManager ioManager(availableMenus, availableMenusCount, 0);

    //Auf Benutzerinteraktion reagieren
    while (ioManager.Interact());

    return 0;
}
