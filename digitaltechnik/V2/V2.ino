#include "RgbwSpotlight8Ch.h"
#include "MiniMovingHead14Ch.h"

RgbwSpotlight8Ch spotlight1(1);
RgbwSpotlight8Ch spotlight2(37);

MiniMovingHead14Ch mover1(9);
MiniMovingHead14Ch mover2(37);

void setup() {
    DmxSimple.usePin(3);
    DmxSimple.maxChannel(44);
}

void loop() {

}