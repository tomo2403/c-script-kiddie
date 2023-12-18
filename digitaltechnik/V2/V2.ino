#define DEMO 0 //Demomodus AUS bei 0
#define BPM_IN_MS 484 //60.000ms geteilt durch BPM

#if DEMO == 0
#include "RgbwSpotlight8Ch.h"
#include "MiniMovingHead14Ch.h"

RgbwSpotlight8Ch spotlight1(1);
RgbwSpotlight8Ch spotlight2(37);
MiniMovingHead14Ch mover1(9);
MiniMovingHead14Ch mover2(37);

#else
#include "RgbwSpotlight8ChDemo.h"
#include "MiniMovingHead14ChDemo.h"

RgbwSpotlight8ChDemo spotlight1(2);
RgbwSpotlight8ChDemo spotlight2(4);
MiniMovingHead14ChDemo mover1(3);
MiniMovingHead14ChDemo mover2(5);
#endif

unsigned long previousMillis = 0;

void setup() {
    Serial.begin(9600);

    DmxSimple.usePin(3);
    DmxSimple.maxChannel(44);

    Serial.println(3);
    delay(800);
    Serial.println(2);
    delay(800);
    Serial.println(1);
    delay(800);
    Serial.println("GO");
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= BPM_IN_MS){
        previousMillis = currentMillis;

        #if DEMO != 0
        Serial.println(currentMillisBpm);
        #endif


    }
}