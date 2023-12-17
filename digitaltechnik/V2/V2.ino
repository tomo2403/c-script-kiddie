#include "RgbwSpotlight8Ch.h"
#include "MiniMovingHead14Ch.h"

RgbwSpotlight8Ch spotlight1(1);
RgbwSpotlight8Ch spotlight2(37);

MiniMovingHead14Ch mover1(9);
MiniMovingHead14Ch mover2(37);

unsigned long previousMillisBpm = 0;
const long intervalBpm = 484;
bool isOn = true;

void setup() {
    Serial.begin(9600);
    pinMode(2, OUTPUT);

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
    unsigned long currentMillisBpm = millis();
    if (currentMillisBpm - previousMillisBpm >= intervalBpm){
        previousMillisBpm = currentMillisBpm;
        isOn = !isOn;
        digitalWrite(2, isOn);
        Serial.println(currentMillisBpm);
    }
}