#pragma once

#include <string>

/// \brief Struktur zum zuordnen von Befehlen zu Menüs
struct KeyMap
{
	char key; ///< Der Schlüssel des Befehls
	int menuId; ///< Die ID des Menüs der Navigation
	std::string action; ///< Die Beschreibung des Befehls
};
