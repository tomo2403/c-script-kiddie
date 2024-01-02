#ifndef DmxDevice_h
#define DmxDevice_h

#include "DmxSimple.h"
#include "DmxCommand.h"
#include <Arduino.h>

/// @brief Basisklasse für alle DMX-Geräte
class DmxDevice {
public:
    explicit DmxDevice(unsigned short address) : Address(address) {}

    /// @brief Die Adresse des Geräts
    unsigned short Address;

    /// @brief Erzeugt ein DMX-Signal an einem Kanal des Geräts.
    /// @param channel Der Kanal des Geräts, beginnend bei Kanal 0.
    /// @param value Der Wert des Signals im Bereich von 0 bis 255.
    virtual void Set(int channel, unsigned char value) {
        DmxSimpleClass::write(static_cast<int>(Address + channel), value);
    };

    /// @brief Verarbeitet Befehle zu ihren Zeitpunkten.
    /// @param currentMillis Der aktuelle Zeitstempel.
    virtual void RunTick(unsigned int currentMillis) = 0;

    /// @brief Bereinigt Spuren vergangener Befehle oder führt diese fort, sofern sie mehrere Aufrufe benötigen.
    /// @param currentMillis Der aktuelle Zeitstempel.
    virtual void CleanUp(unsigned int currentMillis) = 0;

    /// @brief Werzeug für das debuggen von Befehlen.
    /// @param currentMillis Der aktuelle Zeitstempel.
    static void PrintTimeToSerial(unsigned int currentMillis) {
        Serial.print("Time elapsed: ");
        Serial.print(currentMillis);
        Serial.println("ms");
    }
};

#endif