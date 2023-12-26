#ifndef RgbwSpotlight8ChDemo_h
#define RgbwSpotlight8ChDemo_h

#include "RgbwSpotlight8Ch.h"

class RgbwSpotlight8ChDemo : public RgbwSpotlight8Ch {
public:
    explicit RgbwSpotlight8ChDemo(unsigned short address)
            : RgbwSpotlight8Ch(address) {
        pinMode(Address, OUTPUT);
    }

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

    void CleanUp(unsigned int currentMillis) override {
        if (blinkOn && (currentMillis - blinkStart) > 100) {
            digitalWrite(Address, LOW);
            blinkOn = false;
        }
    }
};

#endif