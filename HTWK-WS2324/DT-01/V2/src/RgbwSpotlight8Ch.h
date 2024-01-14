#ifndef RgbwSpotlight8Ch_h
#define RgbwSpotlight8Ch_h

#include "DmxDevice.h"
#include "DmxCommand.h"

/// @brief Beschreibt einen DMX-Scheinwerfer mit acht Kanälen.
class RgbwSpotlight8Ch : public DmxDevice {
public:
    explicit RgbwSpotlight8Ch(unsigned short address) : DmxDevice(address) {}

    /// @brief Alle Funktionen, welche das Gerät unterstützt.
    enum Functions {
        TotalDimming,
        RedDimming,
        GreenDimming,
        BlueDimming,
        WhiteDimming,
        TotalStrobe,
        FuncSelection,
        FuncSpeed,

        Blink = 100,
        Fade = 101,
        BlinkTimeout = 200,

        Stop = 300,
        PrintTime = 301
    };
    bool blinkOn = false;
    bool isFading = false;

    void RunTick(uint16_t currentMillis, DmxCommand cmd) override {
        if (cmd.function != Stop) {
            switch (cmd.function) {
                case PrintTime:
                    PrintTimeToSerial(currentMillis);
                case Blink:
                    StartBlink(currentMillis, cmd.value);
                    break;
                case Fade:
                    fadingTimeout = cmd.value;
                    StartFading(currentMillis);
                case BlinkTimeout:
                    blinkTimeout = cmd.value;
                case TotalDimming:
                    totalDimmingValue = cmd.value;
                    Set(TotalDimming, totalDimmingValue);
                default:
                    Set(static_cast<Functions>(cmd.function), cmd.value);
                    break;
            }
        } else {
            Set(TotalDimming, 0);
        }
    };

    void CleanUp(uint16_t currentMillis) override {
        // Blinken beenden
        if (blinkOn && (currentMillis - blinkStart) > blinkTimeout) {
            Set(TotalDimming, totalDimmingValue);
            blinkOn = false;
        }

        // Dimmen fortsetzen falls aktiv
        if (isFading && (currentMillis - fadingLastCall) > fadingTimeout) {
            totalDimmingValue--;
            fadingLastCall = currentMillis;
            Set(TotalDimming, totalDimmingValue);
            isFading = fadingInterval[1] < totalDimmingValue;
        }
    }

    /// @brief Bereitet das Blinken des Lichts vor.
    /// @param currentMillis Der aktuelle Zeitstempel.
    /// @param value Die Stärke des blinkenden Lichts.
    void StartBlink(uint16_t currentMillis, uint8_t value) {
        blinkOn = true;
        blinkStart = currentMillis;
        Set(TotalDimming, value);
    }

    /// @brief Bereitet das dimmen des Lichts vor.
    /// @param currentMillis Der aktuelle Zeitstempel.
    void StartFading(uint16_t currentMillis) {
        isFading = true;
        fadingLastCall = currentMillis;
        totalDimmingValue = fadingInterval[0];
        Set(TotalDimming, totalDimmingValue);
    }

protected:
    /// @brief Die aktuelle Gesamthelligkeit.
    uint8_t totalDimmingValue = 0;

    /// @brief Zeitpunkt des Starts des blinkens.
    uint16_t blinkStart = 0;
    /// @brief Dauer des blinkenden Lichts.
    unsigned short blinkTimeout = 100;

    /// @brief Letzter Zeitpunkt des dimmens.
    uint16_t fadingLastCall = 0;
    /// @brief Zeit zwischen dem Dimmen zweier Werte.
    uint8_t fadingTimeout = 10;
    /// @brief Intervall des dimmens.
    uint8_t fadingInterval[2] = {
            255,    //Anfang
            0       //Ende
    };
};

#endif