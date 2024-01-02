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
        FadeTimeout = 201,

        Stop = 300,
        PrintTime = 301
    };
    bool blinkOn = false;
    bool isFading = false;

    /// @brief List der Befehle des Geräts.
    DmxCommand commandList[24] = {
            {100,   BlueDimming,  255},
            {200,   TotalDimming, 100},
            {400,   Blink,        255},
            {800,   Blink,        255},
            {1100,  Blink,        255},
            {1580,  Blink,        255},
            {1950,  Blink,        255},
            {2350,  Blink,        255},
            {2700,  Blink,        255},
            {2990,  BlinkTimeout, 255},
            {3000,  Blink,        255},
            {3400,  BlinkTimeout, 100},
            {3550,  Blink,        255},
            {3900,  Blink,        255},
            {4200,  Blink,        255},
            {4700,  TotalDimming, 0},
            {4701,  RedDimming,   100},
            {16000, RedDimming,   255},
            {16001, BlueDimming,  0},
            {22000, GreenDimming, 255},
            {22001, RedDimming,   0},
            {26000, WhiteDimming, 200},
            {31000, Fade,         255},
            {32800, Stop,         0}
    };

    void RunTick(unsigned int currentMillis) override {
        DmxCommand cmd = commandList[commandIndex];
        if (cmd.executionTime < currentMillis) {
            if (cmd.function != Stop) {
                if (cmd.function < 200) {
                    cmd.value = static_cast<unsigned char>(cmd.value);
                }

                switch (cmd.function) {
                    case PrintTime:
                        PrintTimeToSerial(currentMillis);
                    case Blink:
                        StartBlink(currentMillis, cmd.value);
                        break;
                    case Fade:
                        StartFading(currentMillis);
                    case BlinkTimeout:
                        blinkTimeout = cmd.value;
                    case FadeTimeout:
                        fadingTimeout = cmd.value;
                    case TotalDimming:
                        totalDimmingValue = cmd.value;
                        Set(TotalDimming, totalDimmingValue);
                    default:
                        Set(static_cast<Functions>(cmd.function), cmd.value);
                        break;
                }
                commandIndex++;
            } else {
                Set(TotalDimming, 0);
            }
        }
    };

    void CleanUp(unsigned int currentMillis) override {
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
    void StartBlink(unsigned int currentMillis, unsigned char value) {
        blinkOn = true;
        blinkStart = currentMillis;
        Set(TotalDimming, value);
    }

    /// @brief Bereitet das dimmen des Lichts vor.
    /// @param currentMillis Der aktuelle Zeitstempel.
    void StartFading(unsigned int currentMillis) {
        isFading = true;
        fadingLastCall = currentMillis;
        totalDimmingValue = fadingInterval[0];
        Set(TotalDimming, totalDimmingValue);
    }

protected:
    /// @brief Die aktuelle Zeile in der Befehlsliste.
    unsigned short commandIndex = 0;
    /// @brief Die aktuelle Gesamthelligkeit.
    unsigned char totalDimmingValue = 0;

    /// @brief Zeitpunkt des Starts des blinkens.
    unsigned int blinkStart = 0;
    /// @brief Dauer des blinkenden Lichts.
    unsigned short blinkTimeout = 100;

    /// @brief Letzter Zeitpunkt des dimmens.
    unsigned int fadingLastCall;
    /// @brief Zeit zwichen dem Dimmen zweier Werte.
    unsigned char fadingTimeout = 7;
    /// @brief Intervall des dimmens.
    unsigned char fadingInterval[2] = {
            255,    //Anfang
            0       //Ende
    };
};

#endif