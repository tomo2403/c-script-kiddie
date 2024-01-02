#define DEMO 0         //Demomodus AUS bei 0
#define BPM_IN_MS 484  //Quotient aus 60.000ms und BPM

#include <Arduino.h>
#include "RgbwSpotlight8Ch.h"
#include "MiniMovingHead14Ch.h"

//Geräte aus Klassen mit DMX Adresse instanzieren
#if DEMO == 0
/// @brief Enthält alle Spotlichter.
RgbwSpotlight8Ch spotlights[2] = {
        {RgbwSpotlight8Ch(1)},
        {RgbwSpotlight8Ch(37)}
};
/// @brief Enthält alle Movingheads.
MiniMovingHead14Ch movingHeads[2] = {
        {MiniMovingHead14Ch(9)},
        {MiniMovingHead14Ch(23)}
};

//Geräte aus Klassen mit Pin-Nummern instanzieren
#else

#include "RgbwSpotlight8ChDemo.h"
#include "MiniMovingHead14ChDemo.h"

/// @brief Enthält alle Spotlichter als LED.
RgbwSpotlight8ChDemo spotlights[2] = {
        {RgbwSpotlight8ChDemo(2)},
        {RgbwSpotlight8ChDemo(4)}
};
/// @brief Enthält alle Movingheads als LED.
MiniMovingHead14ChDemo movingHeads[2] = {
        {MiniMovingHead14ChDemo(3)},
        {MiniMovingHead14ChDemo(5)}
};
#endif

/// @brief Zeitstempel des letzten erkannten Beats.
unsigned int previousMillis = 0;

/// @brief Zeitstempel des Starts der Lichtshow.
unsigned int loopStartMillis = 0;

/// @brief Zeitintervalls, in denen erkannte Beats verarbeitet werden sollen.
unsigned int beatIntervals[1][2] = {
        {4770, 31000},
};

/// @brief Prüft bei jedem Aufruf, ob inder bereits verstrichenen Zeit ein Beat auftrat.
/// @param currentMillis Der Zeitpunkt des Aufrufs in.
void BeatDetector(unsigned int currentMillis) {
    if ((currentMillis - previousMillis) >= BPM_IN_MS) {
        previousMillis = currentMillis;

        for (auto const &interval: beatIntervals) {
            if (interval[0] <= currentMillis && currentMillis <= interval[1]) {
                //Event eines Beats
                for (auto &spotlight: spotlights) {
                    spotlight.StartBlink(currentMillis, 255);
                }
                break;
            }
        }
    }
}

/// @brief Bereitet den Programmablauf vor.
void setup() {
    // DMX Interface vorbereiten.
#if DEMO == 0
    DmxSimpleClass::usePin(3);
    DmxSimpleClass::maxChannel(44);
#endif

    // Start des Programms in der Ausgabe ankündigen.
    Serial.begin(115200);
    Serial.println(3);
    delay(800);
    Serial.println(2);
    delay(800);
    Serial.println(1);
    delay(800);
    Serial.println("GO");
    delay(100);

    loopStartMillis = millis();
}

/// @brief Speichert den aktuellen Zeitpunkt und gibt ihn an die Geräte zum Ausführen von Befehlen weiter.
void loop() {
    unsigned int currentMillis = millis() - loopStartMillis;
    BeatDetector(currentMillis);

    for (auto &spotlight: spotlights) {
        spotlight.CleanUp(currentMillis);
        spotlight.RunTick(currentMillis);
    }
    for (auto &movingHead: movingHeads) {
        movingHead.CleanUp(currentMillis);
        movingHead.RunTick(currentMillis);
    }
}