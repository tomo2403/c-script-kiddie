#ifndef DmxCommand_h
#define DmxCommand_h

/// @brief Beschreibt einen Befehl, der über DMX ausgeführt werden soll.
struct DmxCommand {
    /// @brief Die Gerätegruppe, welche verwendet werden soll.
    uint8_t deviceGroup;
    /// @brief Der Zeitpunkt der geplanten Ausführung.
    unsigned short executionTime;
    /// @brief Der Kanal oder die Funktion, welche bedient wird.
    short function;
    /// @brief Der Wert, welcher die Funktion verändert.
    uint32_t value;
};
#endif