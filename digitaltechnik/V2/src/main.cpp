#define DEMO 1         //Demomodus AUS bei 0
#define BPM_IN_MS 484  //60.000ms geteilt durch BPM

#include <Arduino.h>
#include "RgbwSpotlight8Ch.h"
#include "MiniMovingHead14Ch.h"

#if DEMO == 0
RgbwSpotlight8Ch spotlights[2] = {
        {RgbwSpotlight8Ch(2)},
        {RgbwSpotlight8Ch(4)}
};
MiniMovingHead14Ch movingHeads[2] = {
        {MiniMovingHead14Ch(3)},
        {MiniMovingHead14Ch(5)}
};

#else
#include "RgbwSpotlight8ChDemo.h"
#include "MiniMovingHead14ChDemo.h"

RgbwSpotlight8ChDemo spotlights[2] = {
        {RgbwSpotlight8ChDemo(2)},
        {RgbwSpotlight8ChDemo(4)}
};
MiniMovingHead14ChDemo movingHeads[2] = {
        {MiniMovingHead14ChDemo(3)},
        {MiniMovingHead14ChDemo(5)}
};
#endif

unsigned long previousMillis = 0;
unsigned long loopStartMillis = 0;

unsigned int beatIntervals[2][2] = {
        {1000,5000},
        {10000,15000},
};

void BeatDetector(unsigned long currentMillis){
    if ((currentMillis - previousMillis) >= BPM_IN_MS){
        previousMillis = currentMillis;
        //Serial.println(currentMillis);
        for (auto & interval : beatIntervals){
            if (interval[0] < currentMillis && currentMillis < interval[1]) {
                //Serial.println(currentMillis);
                Serial.print(interval[0]); Serial.print(" > "); Serial.println(currentMillis);
                Serial.print(interval[1]); Serial.print(" < "); Serial.println(currentMillis);

                for(auto & spotlight : spotlights){
                    spotlight.StartBlink(currentMillis, 255);
                    spotlight.StartBlink(currentMillis, 255);
                }
                break;
            }
        }
    }
}

void setup() {
#if DEMO == 0
    DmxSimple.usePin(3);
    DmxSimple.maxChannel(44);
#else
    for(auto & spotlight : spotlights){
        pinMode(spotlight.Address, OUTPUT);
    }
    for(auto & movingHead : movingHeads){
        pinMode(movingHead.Address, OUTPUT);
    }
#endif

    Serial.begin(9600);
    Serial.println(3);
    delay(800);
    Serial.println(2);
    delay(800);
    Serial.println(1);
    delay(800);
    Serial.println("GO");

    loopStartMillis = millis();
    //Serial.println(loopStartMillis);
}

void loop() {
    unsigned long currentMillis = millis() - loopStartMillis;
    BeatDetector(currentMillis);

    for(auto & spotlight : spotlights){
        spotlight.CleanUp(currentMillis);
        //spotlight.RunTick(currentMillis);
    }
}