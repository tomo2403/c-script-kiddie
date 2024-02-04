#pragma once

#include "Menu.hpp"

/*!
 * \brief Verwaltet Ein- & Ausgabeströme.
 *
 * Beinhaltet Funktion und Variablen, um die Menüführung zu steuern und auf Benutzereingaben reagieren zu können.
 */
class IOManager
{
public:
	/*!
	 * \brief Konstruktor für die IOManager-Klasse.
	 * \param menus Ein Array mit allen Menüs, die der IOManager bedienen soll.
	 * \param availableMenusCount Die Anzahl der verfügbaren Menüs.
	 * \param currentMenu Die ID des aktuellen Menüs.
	 */
	explicit IOManager(Menu menus[], int availableMenusCount, int currentMenu);

	/*!
	 * \brief Ermittelt des aktuelle Menü-Objekt.
	 * \return Die Referenz des Menü-Objekts.
	 *
	 * Verwendet die ID des aktuellen Menüs und gibt das Menü mit dem passenden Index zurück.
	 */
	[[nodiscard]] const Menu &CurrentMenu() const;

	/*!
	 * \brief Fordert den Benutzer auf, zu einem Menü zu navigieren.
	 * \return True, wenn eine weitere Interaktion gewünscht ist, sonst false.
	 *
	 * Fragt den Benutzer nach einer Eingabe und versucht anschließend, diese einem Menü zuzuordnen.
	 */
	bool Interact();

	/*!
	 * \brief Wechselt zum angegebenen Menü.
	 * \param menuId Die Id des Zielmenüs.
	 *
	 * Ruf das Menu mit der passenden ID auf und stellt dessen Inhalt in der Konsole dar.
	 */
	void GoToMenu(int menuId);

private:
	int _currentMenuId = 0; ///< Die ID des aktuellen Menüs.
	const int _availableMenusCount; ///< Die Gesamtanzahl der verfügbaren Menüs.
	Menu *_menus; ///< Verfügbare Menüs.

	/*!
	 * \brief Druckt den Header auf der Konsole.
	 */
	static void printHeader();

	/*!
	 * \brief Löscht den Bildschirm (plattformunabhängig).
	 *
	 * Ermittelt das aktuelle Betriebssystem und führt den passenden Befehl aus, um die Konsole zu bereinigen.
	 */
	static void clearScreen();

	/*!
	 * \brief Überprüft, ob die Menü-ID gültig ist.
	 * \param menuId Die zu überprüfende Menü-ID.
	 * \return True, wenn die Menü-ID gültig ist, sonst false.
	 *
	 * Prüft, ob \a menuId ein Index von _menus ist, was impliziert ob ein Menu dazu vorhanden ist.
	 */
	[[nodiscard]] bool isValidMenuId(int menuId) const;
};
