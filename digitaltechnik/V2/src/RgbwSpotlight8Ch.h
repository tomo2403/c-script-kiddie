#ifndef RgbwSpotlight8Ch_h
#define RgbwSpotlight8Ch_h

#include "DmxDevice.h"
#include "DmxCommand.h"

class RgbwSpotlight8Ch : public DmxDevice {
public:
    explicit RgbwSpotlight8Ch(unsigned short address)
            : DmxDevice(address) {}
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
    bool blinkOn = false;
    unsigned short blinkTimeout = 100;
    unsigned long blinkStart = 0;

    unsigned int commandIndex = 0;
    DmxCommand commandList[4] = {
            {1000, Blink, 255},
            {2000, Blink, 255},
            {3000, Blink, 255},
            {4000, Blink, 255}
    };

    virtual void RunTick(unsigned long currentMillis) {
        DmxCommand cmd = commandList[commandIndex];
        if (cmd.executionTime < currentMillis) {
            switch (cmd.function) {
                case Blink:
                    blinkOn = true;
                    blinkStart = currentMillis;
                    Set(TotalDimming, cmd.value);
                    break;
                default:
                    Set(static_cast<Functions>(cmd.function), cmd.value);
                    break;
            }
            commandIndex++;
        }
    };

    virtual void Set(Functions channel, unsigned char value) {
        //DmxSimple.write(static_cast<int>(Address + channel - 1), value);
    };

    virtual void CleanUp(unsigned long currentMillis) {
        if (blinkOn && (currentMillis - blinkStart) > blinkTimeout) {
            Set(TotalDimming, 0);
            blinkOn = false;
        }
    }
};
#endif