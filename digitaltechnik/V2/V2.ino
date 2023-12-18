#define DEMO 1         //Demomodus AUS bei 0
#define BPM_IN_MS 484  //60.000ms geteilt durch BPM

#include "RgbwSpotlight8Ch.h"
#include "MiniMovingHead14Ch.h"
#include "DmxCommand.h"

#if DEMO == 0
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
unsigned long loopStartMillis = 0;
unsigned long currentMillis = 0;

unsigned short spotCommandLine = 0;
DmxCommand spotCommands[] = {
  {1000, spotlight1.TotalDimming, 255},
  {1100, spotlight1.TotalDimming, 0},
  {2000, spotlight1.TotalDimming, 255},
  {2100, spotlight1.TotalDimming, 0},
  {3000, spotlight1.TotalDimming, 255},
  {3100, spotlight1.TotalDimming, 0},
  {4000, spotlight1.TotalDimming, 255},
  {4100, spotlight1.TotalDimming, 0}
};

void setup() {
#if DEMO == 0
  DmxSimple.usePin(3);
  DmxSimple.maxChannel(44);
#else
  pinMode(spotlight1.Address, OUTPUT);
  pinMode(spotlight2.Address, OUTPUT);
  pinMode(mover1.Address, OUTPUT);
  pinMode(mover2.Address, OUTPUT);
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
}

void loop() {
  currentMillis = millis() - loopStartMillis;
  // if (currentMillis - previousMillis >= BPM_IN_MS) {
  //   previousMillis = currentMillis;

#if DEMO != 0
    Serial.println(currentMillis);
#endif
  // }

  if (spotCommands[spotCommandLine].executionTime <= currentMillis){
    DmxCommand cmd = spotCommands[spotCommandLine];
    spotlight1.Set(cmd.function, cmd.value);
    spotCommandLine++;
    spotCommands..DMX_SIZE
  }
}