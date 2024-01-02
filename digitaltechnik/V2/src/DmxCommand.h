#ifndef DmxCommand_h
#define DmxCommand_h

/// @brief Beschreibt einen Befehl, der über DMX ausgeführt werden soll.
struct DmxCommand {
    /// @brief Der Zeitpunkt der geplanten Ausführung.
    unsigned int executionTime;
    /// @brief Der Kanal oder die Funktion, welche bedient wird.
    int function;
    /// @brief Der Wert, welcher die Funktion verändert.
    unsigned char value;
};
#endif