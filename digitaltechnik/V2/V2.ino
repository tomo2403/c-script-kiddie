#include "RgbwSpotlight8Ch.h"
#include "MiniMovingHead14Ch.h"

RgbwSpotlight8Ch spotlight1(1);
RgbwSpotlight8Ch spotlight2(37);

MiniMovingHead14Ch mover1(9);
MiniMovingHead14Ch mover2(37);

unsigned long previousMillisLED = 0;
unsigned long previousMillisPrint = 0;
const long intervalBpm = 1000;
const long intervalPrint = 3500;

void setup() {
    Serial.begin(9600);
    pinMode(2, OUTPUT);

    DmxSimple.usePin(3);
    DmxSimple.maxChannel(44);
}

void loop() {
    unsigned long currentMillisPrint = millis();
    if (currentMillisPrint - previousMillisPrint >= intervalPrint){
        previousMillisPrint = currentMillisPrint;
        digitalWrite(2, LOW);
        Serial.println(0);
    }

    unsigned long currentMillisLED = millis();
    if (currentMillisLED - previousMillisLED >= intervalLed){
        previousMillisLED = currentMillisLED;
        digitalWrite(2, HIGH);
        Serial.println(1);
    }
}