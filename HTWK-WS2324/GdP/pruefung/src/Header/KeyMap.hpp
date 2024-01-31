#pragma once

/// \brief Struktur zum zuordnen von Befehlen zu Menüs
struct KeyMap
{
    unsigned char key; ///< Der Schlüssel des Befehls
    unsigned char menuId; ///< Die ID des Menüs der Navigation
    std::string action; ///< Die Beschreibung des Befehls
};