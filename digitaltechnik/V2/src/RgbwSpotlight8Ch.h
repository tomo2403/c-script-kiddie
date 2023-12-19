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

    void RunTick(unsigned long currentMillis) override {
        DmxCommand cmd = commandList[commandIndex];
        if (cmd.executionTime < currentMillis) {
            switch (cmd.function) {
                case Blink:
                    StartBlink(currentMillis, cmd.value);
                    break;
                default:
                    Set(static_cast<Functions>(cmd.function), cmd.value);
                    break;
            }
            commandIndex++;
        }
    };

    virtual void Set(Functions channel, unsigned char value) {
        DmxSimple.write(static_cast<int>(Address + channel - 1), value);
    };

    void CleanUp(unsigned long currentMillis) override {
        if (blinkOn && (currentMillis - blinkStart) > blinkTimeout) {
            Set(TotalDimming, 0);
            blinkOn = false;
        }
    }

    void StartBlink(unsigned long currentMillis, unsigned char value){
        blinkOn = true;
        blinkStart = currentMillis;
        Set(TotalDimming, value);
    }
};
#endif