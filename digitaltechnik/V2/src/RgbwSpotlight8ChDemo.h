#ifndef RgbwSpotlight8ChDemo_h
#define RgbwSpotlight8ChDemo_h

#include "RgbwSpotlight8Ch.h"

/// @brief Beschreibt die Emulation eines DMX-Scheinwerfer mit acht Kanälen.
class RgbwSpotlight8ChDemo : public RgbwSpotlight8Ch {
public:
    explicit RgbwSpotlight8ChDemo(unsigned short address) : RgbwSpotlight8Ch(address) {
        pinMode(Address, OUTPUT);
    }

    /// @brief Überschreibt den DMX-Ausgang mit lokalen Pins.
    /// @param channel Die Funktion oder der Kanal.
    /// @param value Der Wert der Funktion
    void Set(int channel, unsigned char value) override {
        switch (channel) {
            case 0:
                if (value <= 100) {
                    digitalWrite(Address, LOW);
                } else {
                    digitalWrite(Address, HIGH);
                }
                break;
            default:
                break;
        }
    }

    /// @brief Überschreibt den Reinigungsprozess um Pins benutzen zu können.
    /// @param currentMillis Der aktuelle Zeitstempel.
    void CleanUp(unsigned int currentMillis) override {
        if (blinkOn && (currentMillis - blinkStart) > 100) {
            digitalWrite(Address, LOW);
            blinkOn = false;
        }
    }
};

#endif