#pragma once
#include <vector>
#include <functional>
#include "KeyMap.hpp"

/// \brief Repräsentiert ein Menü
class Menu
{
public:
    /// \brief Erstellt ein neues Menü-Objekt
    /// \param name Der Name des Menüs.
    /// \param parent Die ID des übergeordneten Menüs.
    /// \param keys Die Befehle des Menüs.
    /// \param codeToExecute Funktion, die zwischen Kopf und Fuß des Menüs ausgeführt werden soll.
    /// \param hideBackKey True, wenn der "Zurück"-Befehl versteckt werden soll, sonst false.
    Menu(std::string name, unsigned char parent, const std::vector<KeyMap> &keys, const std::function<void()> &codeToExecute,
         bool hideBackKey = false);

    /// \brief Stellt das Menü in der Konsole dar
    void Print() const;

    /// \brief Ermittelt das Menü eines Befehls
    /// \param key Der Schlüssel des Befehls
    /// \return Die ID des Menüs des Befehls
    [[nodiscard]] int GetNavigation(unsigned char key) const;

    /// \brief Gibt das übergeordnete Menü zurück
    /// \return Die ID des übergeordneten Menüs
    [[nodiscard]] int GetParent() const;

private:
    std::string _name; ///< Der Name des Menüs
    unsigned char _parent; ///< Die ID des übergeordneten Menüs
    std::vector<KeyMap> _keys; ///< Die Befehle des Menüs.
    std::function<void()> _codeToExecute; ///< Funktion, die zwischen Kopf und Fuß des Menüs ausgeführt werden soll.
};