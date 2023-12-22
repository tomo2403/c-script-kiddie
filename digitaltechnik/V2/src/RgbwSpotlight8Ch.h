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
        Flash = 101
    };
    unsigned char totalDimmingValue = 0;

    bool blinkOn = false;
    unsigned short blinkTimeout = 100;
    unsigned int blinkStart = 0;

    unsigned short commandIndex = 0;
    DmxCommand commandList[10] = {
            {1,    BlueDimming,  255},
            {10,   TotalDimming, 100},
            {450,  TotalDimming, 255},
            {550,  TotalDimming, 100},
            {850,  TotalDimming, 255},
            {950,  TotalDimming, 100},
            {1050, TotalDimming, 255},
            {1150, TotalDimming, 100},
            {1300, TotalDimming, 255},
            {1400, TotalDimming, 100}
    };

    void RunTick(unsigned int currentMillis) override {
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

    void CleanUp(unsigned int currentMillis) override {
        if (blinkOn && (currentMillis - blinkStart) > blinkTimeout) {
            Set(TotalDimming, 0);
            blinkOn = false;
        }
    }

    void StartBlink(unsigned int currentMillis, unsigned char value) {
        blinkOn = true;
        blinkStart = currentMillis;
        Set(TotalDimming, value);
    }

    void StartFlash(unsigned int currentMillis, unsigned char value) {

    }
};

#endif