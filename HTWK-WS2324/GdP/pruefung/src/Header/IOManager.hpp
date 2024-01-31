#pragma once
#include "Menu.hpp"

/// \brief Verwaltet Ein- & Ausgabeströme
class IOManager
{
public:
    /// \brief Konstruktor für die IOManager-Klasse.
    /// \param menus Ein Array mit allen Menüs, die der IOManager bedienen soll.
    /// \param availableMenusCount Die Anzahl der verfügbaren Menüs.
    explicit IOManager(Menu menus[], int availableMenusCount);

    /// \brief Ermittelt den Pointer des aktuellen Menü-Objekts.
    /// \return Der Pointer des Menü-Objekts.
    [[nodiscard]] Menu &CurrentMenu() const;

    /// \brief Fordert den Benutzer auf, zu einem Menü zu navigieren.
    /// \return True, wenn eine weitere Interaktion gewünscht ist, sonst false.
    bool Interact();

    /// \brief Wechselt zum angegebenen Menü.
    /// \param menuId Die Id des Zielmenüs.
    void GoToMenu(int menuId);

private:
    int _currentMenuId = 0; ///< Die ID des aktuellen Menüs.
    const int _availableMenusCount; ///< Die Gesamtanzahl der verfügbaren Menüs.
    Menu *_menus; ///< Verfügbare Menüs.

    /// \brief Druckt den Header auf der Konsole.
    static void printHeader();

    /// \brief Löscht den Bildschirm (plattformunabhängig).
    static void clearScreen();

    /// \brief Überprüft, ob die Menü-ID gültig ist.
    /// \param menuId Die zu überprüfende Menü-ID.
    /// \return True, wenn die Menü-ID gültig ist, sonst false.
    [[nodiscard]] bool isValidMenuId(int menuId) const;
};