#include <iostream>
#include <string>
#include "../Header/IOManager.hpp"
#include "../Header/Mitarbeiterdatenbank.hpp"
#include "../Header/Utilities.hpp"
#include "../Header/ConsoleHelpers.hpp"
#include "../Header/MenuBuilder.hpp"

Menu MenuBuilder::buildMainMenu()
{
	//Hauptmenü
	return {"Hauptmenü", 0,
			{{'o', 4, "Mitarbeiterverzeichnis öffnen"},
			 {'e', 2, "Datenbank exportieren"},
			 {'i', 3, "Datenbank importieren"},
			 {'h', 1, "Hilfe anzeigen"}},
			{[]()
			 {
				 std::cout << STYLE_UNDERLINE "HTWK Leipzig, Wintersemester 2023/24" << RESET_UNDERLINE << std::endl
																					 << "[C963] Grundlagen der Programmierung\n" << std::endl
																					 << STYLE_BOLD << "Prüfungsleistung" << RESET_BOLD << std::endl;
			 }}, true
	};
}

Menu MenuBuilder::buildHelpMenu()
{
	//Hilfemenü
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

Menu MenuBuilder::buildMitarbeiterliste(MitarbeiterDatenbank* db)
{
	//Ansicht für Mitarbeiterliste
	return {"Mitarbeiterverzeichnis", 0,
			{{'s', 6, "Suche"},
			 {'a', 7, "Hinzufügen"},
			 {'d', 5, "Detailansicht"}},
			{[db]()
			 {
				 std::map<int, Mitarbeiter> mitarbeiterMap = db->alleMitarbeiter();
				 Utilities::printMitarbeiterTable(mitarbeiterMap);
			 }}
	};
}

Menu MenuBuilder::buildSaveMenu(MitarbeiterDatenbank* db)
{
	//Speichern der Datenbank
	return {"Exportieren", 0,
			{},
			{[db]()
			 {
				 db->serialisieren();
				 std::cout << "Gespeichert!" << std::endl;
			 }}
	};
}

Menu MenuBuilder::buildLoadMenu(MitarbeiterDatenbank* db)
{
	//Laden der Datenbank
	return {"Importieren", 0,
			{},
			{[db]()
			 {
				 db->deserialisieren();
				 std::cout << "Geladen!" << std::endl;
			 }}
	};
}

Menu MenuBuilder::buildMitarbeiterDetail(MitarbeiterDatenbank* db)
{
	//Ansicht für einzelne Mitarbeiter
	return {"Mitarbeiter Detailansicht", 4,
			{{'m', 8, "Gehalt erhöhen"},
			 {'r', 9, "Entfernen"}},
			{[db]()
			 {
				 int mitarbeiterId;

				 if (Utilities::tryGetMitarbeiterId(mitarbeiterId))
				 {
					 Utilities::printMitarbeiter(mitarbeiterId, db);
				 }
				 else
				 {
					 Utilities::printWarning("Vorgang abgebrochen!");
					 db->selectedId = 0;
				 }
			 }}
	};
}

Menu MenuBuilder::buildSearchMenu(MitarbeiterDatenbank* db)
{
	//Ansicht zum Suchen von Mitarbeitern
	return {"Mitarbeiter suchen", 4,
			{{'s', 6, "Neue suche"},
			 {'d', 5, "Mitarbeiter öffnen"}},
			{[db]()
			 {
				 Utilities::printWarning("Groß- und Kleinschreibung wird berücksichtigt!\n");

				 std::string name, vorname;
				 std::cout << "Name enthält: ";
				 name = Utilities::getInput();
				 std::cout << "Vorname enthält: ";
				 vorname = Utilities::getInput();

				 std::vector<int> mitarbeiter = db->findeMitarbeiter(name, vorname);

				 std::cout << std::endl << STYLE_UNDERLINE << "Treffer IDs:" << RESET_UNDERLINE << std::endl;
				 for (int i: mitarbeiter)
				 {
					 std::cout << i << std::endl;
				 }
			 }}
	};
}

Menu MenuBuilder::buildAddMenu(MitarbeiterDatenbank* db)
{
	//Ansicht zum Hinzufügen von einem Mitarbeiter
	return {"Mitarbeiter hinzufügen", 4,
			{},
			{[db]()
			 {
				 double gehalt;
				 std::string name, vorname, plz, gehaltStr;
				 Utilities::inputMitarbeiter(name, vorname, plz, gehaltStr, gehalt);

				 std::cout << RESET_STYLE << std::endl << std::endl;
				 std::cout << STYLE_UNDERLINE << "Eingaben überprüfen:" << RESET_UNDERLINE << std::endl;
				 Utilities::printMitarbeiter({name, vorname, plz, gehalt}, db);

				 std::cin.ignore();
				 if (Utilities::askQuestion("Mitarbeiter hinzufügen?", true))
				 {
					 db->neuerMitarbeiter(name, vorname, plz, gehalt);
					 Utilities::printSuccess("\nMitarbeiter hinzugefügt!");
				 }
				 else
				 {
					 Utilities::printWarning("Vorgang abgebrochen!");
				 }
			 }}
	};
}

Menu MenuBuilder::buildModifyMenu(MitarbeiterDatenbank* db)
{
	//Ansicht zum Anpassen des Gehalts des aktuellen Mitarbeiters
	return {"Gehalt erhöhen", 4,
			{},
			{[db]()
			 {
				 try
				 {
					 Mitarbeiter &mCurrent = db->getMitarbeiter(db->selectedId);
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
						 Utilities::handleSalaryChange(mCurrent, factorStr, db);
					 }
				 }
				 catch (std::out_of_range &)
				 {
					 Utilities::printError("Kein Mitarbeiter ausgewählt!");
				 }
			 }}
	};
}

Menu MenuBuilder::buildRemoveMenu(MitarbeiterDatenbank* db)
{
	//Ansicht zum Entfernen des aktuellen Mitarbeiters
	return {"Mitarbeiter entfernen", 4,
			{},
			{[db]()
			 {
				 try
				 {
					 Mitarbeiter &mCurrent = db->getMitarbeiter(db->selectedId);
					 std::cout << "Mitarbeiter: " << mCurrent.name() << ", " << mCurrent.vorname() << std::endl << "Wohnt in: "
							   << mCurrent.postleitzahl() << std::endl << std::endl;

					 if (Utilities::askQuestion("Mitarbeiter wirklich löschen?", false))
					 {
						 db->loescheMitarbeiter(db->selectedId);
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
