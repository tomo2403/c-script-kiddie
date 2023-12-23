#ifndef RgbwSpotlight8Ch_h
#define RgbwSpotlight8Ch_h

#include "DmxDevice.h"
#include "DmxCommand.h"

class RgbwSpotlight8Ch : public DmxDevice {
public:
    explicit RgbwSpotlight8Ch(unsigned short address)
            : DmxDevice(address) {}

    enum Functions {
        TotalDimming,
        RedDimming,
        GreenDimming,
        BlueDimming,
        WhiteDimming,
        TotalStrobe,
        FuncSelection,
        FuncSpeed,

        Blink = 100,
        Stop = 200,
        PrintTime = 201,
        BlinkTimeout = 202,
    };
    unsigned char totalDimmingValue = 0;

    bool blinkOn = false;
    unsigned short blinkTimeout = 100;
    unsigned int blinkStart = 0;

    unsigned short commandIndex = 0;
    DmxCommand commandList[17] = {
            {100,   BlueDimming,  255},
            {200,   TotalDimming, 100},
            {400,   Blink,        255},
            {800,   Blink,        255},
            {1100,  Blink,        255},
            {1580,  Blink,        255},
            {1950,  Blink,        255},
            {2350,  Blink,        255},
            {2700,  Blink,        255},
            {2990,  BlinkTimeout, 300},
            {3000,  Blink,        255},
            {3400,  BlinkTimeout, 100},
            {3550,  Blink,        255},
            {3900,  Blink,        255},
            {4200,  Blink,        255},
            {4700,  TotalDimming, 0},
            {32800, Stop,         0}
    };

    void RunTick(unsigned int currentMillis) override {
        DmxCommand cmd = commandList[commandIndex];
        if (cmd.executionTime < currentMillis) {
            if (cmd.function != Stop) {
                if (cmd.function < 200) {
                    cmd.value = static_cast<unsigned char>(cmd.value);
                }

                switch (cmd.function) {
                    case PrintTime:
                        Serial.print("Time elapsed: ");
                        Serial.print(currentMillis);
                        Serial.println("ms");
                    case Blink:
                        StartBlink(currentMillis);
                        break;
                    case BlinkTimeout:
                        blinkTimeout = cmd.value;
                    case TotalDimming:
                        totalDimmingValue = cmd.value;
                        Set(TotalDimming, totalDimmingValue);
                    default:
                        Set(static_cast<Functions>(cmd.function), cmd.value);
                        break;
                }
                commandIndex++;
            } else {
                Set(TotalDimming, 0);
            }
        }
    };

    void CleanUp(unsigned int currentMillis) override {
        if (blinkOn && (currentMillis - blinkStart) > blinkTimeout) {
            Set(TotalDimming, totalDimmingValue);
            blinkOn = false;
        }
    }

    void StartBlink(unsigned int currentMillis) {
        blinkOn = true;
        blinkStart = currentMillis;
        Set(TotalDimming, 255);
    }
};

#endif