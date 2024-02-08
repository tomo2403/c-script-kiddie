#pragma once

#include "Menu.hpp"
#include "Mitarbeiterdatenbank.hpp"

/*!
 * @brief Die Klasse MenuBuilder stellt statische Methoden zur Verfügung, um verschiedene Menüs zu erstellen.
 */
class MenuBuilder{
public:
	/*!
	 * @brief Erstellt das Hauptmenü.
	 * @return Ein Objekt der Klasse Menu, welche das Hauptmenü repräsentiert.
	 *
	 * Stellt alle Grundfunktionen des Programms dar.
	 */
	static Menu buildMainMenu();

	/*!
	 * @brief Erstellt das Hilfemenü.
	 * @return Ein Objekt der Klasse Menu, welche das Hilfemenü repräsentiert.
	 *
	 * Stellt eine Hilfestellung zur Bedienung des Programms dar.
	 */
	static Menu buildHelpMenu();

	/*!
	 * @brief Erstellt das Menü zur Anzeige der Mitarbeiterliste.
	 * @param db Ein Zeiger auf die Mitarbeiterdatenbank.
	 * @return Ein Objekt der Klasse Menu, welche das Mitarbeiterverzeichnis repräsentiert.
	 *
	 * Stellt eine Liste aller verfügbaren Mitarbeiter dar und bietet Möglichkeiten zur Bearbeitung.
	 */
	static Menu buildMitarbeiterliste(MitarbeiterDatenbank* db);

	/*!
	 * @brief Erstellt das Menü zum Speichern der Datenbank.
	 * @param db Ein Zeiger auf die Mitarbeiterdatenbank.
	 * @return Ein Objekt der Klasse Menu, welche das Exportieren-Menü repräsentiert.
	 *
	 * Stellt den Prozess der Speicherung dar und führt diese durch.
	 */
	static Menu buildSaveMenu(MitarbeiterDatenbank* db);

	/*!
	 * @brief Erstellt das Menü zum Laden der Datenbank.
	 * @param db Ein Zeiger auf die Mitarbeiterdatenbank.
	 * @return Ein Objekt der Klasse Menu, welche das Importieren-Menü repräsentiert.
	 *
	 * Stellt den Prozess des Ladens dar und führt diese durch.
	 */
	static Menu buildLoadMenu(MitarbeiterDatenbank* db);

	/*!
	 * @brief Erstellt das Menü zur Anzeige der Detailansicht eines Mitarbeiters.
	 * @param db Ein Zeiger auf die Mitarbeiterdatenbank.
	 * @return Ein Objekt der Klasse Menu, welche die Mitarbeiter-Detailansicht repräsentiert.
	 *
	 * Stellt einen Mitarbeiter mit allen Eigenschaften dar und bietet Möglichkeiten zur Bearbeitung.
	 */
	static Menu buildMitarbeiterDetail(MitarbeiterDatenbank* db);

	/*!
	 * @brief Erstellt das Menü zur Suche von Mitarbeitern.
	 * @param db Ein Zeiger auf die Mitarbeiterdatenbank.
	 * @return Ein Objekt der Klasse Menu, welche das Mitarbeiter-Suchmenü repräsentiert.
	 *
	 * Stellt die Suche von Mitarbeitern da und führt diese durch.
	 */
	static Menu buildSearchMenu(MitarbeiterDatenbank* db);

	/*!
	 * @brief Erstellt das Menü zum Hinzufügen eines neuen Mitarbeiters.
	 * @param db Ein Zeiger auf die Mitarbeiterdatenbank.
	 * @return Ein Objekt der Klasse Menu, welche das Mitarbeiter-Hinzufügen-Menü repräsentiert.
	 *
	 * Stellt den Prozess des Hinzufügen von einem Mitarbeiter dar und führt diesen durch.
	 */
	static Menu buildAddMenu(MitarbeiterDatenbank* db);

	/*!
	 * @brief Erstellt das Menü zur Änderung des Gehalts eines Mitarbeiters.
	 * @param db Ein Zeiger auf die Mitarbeiterdatenbank.
	 * @return Ein Objekt der Klasse Menu, welche das Gehalt-Ändern-Menü repräsentiert.
	 *
	 * Gibt dem Benutzer die Möglichkeit, einen Mitarbeiter zu bearbeiten und die Änderungen zu speichern.
	 */
	static Menu buildModifyMenu(MitarbeiterDatenbank* db);

	/*!
	 * @brief Erstellt das Menü zum Entfernen eines Mitarbeiters.
	 * @param db Ein Zeiger auf die Mitarbeiterdatenbank.
	 * @return Ein Objekt der Klasse Menu, welche das Mitarbeiter-Entfernen-Menü repräsentiert.
	 *
	 * Gibt dem Benutzer die Möglichkeit, einen Mitarbeiter zu entfernen und die Änderungen zu speichern.
	 */
	static Menu buildRemoveMenu(MitarbeiterDatenbank* db);
};
