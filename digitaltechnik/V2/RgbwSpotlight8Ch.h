#ifndef RgbwSpotlight8Ch_h
#define RgbwSpotlight8Ch_h

#include "DmxDevice.h"
#include "DmxCommand.h"
#include "Arduino.h"

class RgbwSpotlight8Ch : public DmxDevice {
public:
    explicit RgbwSpotlight8Ch(unsigned short address)
            : DmxDevice(8, address) {}
    enum Functions {
        Delay = 0,
        TotalDimming = 1,
        RedDimming = 2,
        GreenDimming = 3,
        BlueDimming = 4,
        WhiteDimming = 5,
        TotalStrobe = 6,
        FuncSelection = 7,
        FuncSpeed = 8,

        Blink = 100,
    };

    virtual void Set(Functions channel, unsigned char value){
        switch (channel) {
            case 100:
                blinkOn = true;
                blinkStart = millis();
                DmxSimple.write(Address + TotalDimming - 1, value);
                break;
            default:
                DmxSimple.write(Address + channel - 1, value);
                break;
        }
    };

    bool blinkOn = false;
    unsigned long blinkStart = 0;

    virtual void CleanUp() {
        if (blinkOn && (millis() - blinkStart) > 100) {
            Set(TotalDimming, 0);
            blinkOn = false;
        }
    }
};
#endif