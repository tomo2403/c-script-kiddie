#ifndef RgbwSpotlight8Ch_h
#define RgbwSpotlight8Ch_h

#include "DmxDevice.h"
#include "DmxCommand.h"

class RgbwSpotlight8Ch : public DmxDevice {
public:
    explicit RgbwSpotlight8Ch(unsigned short address) : DmxDevice(address) {}

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
        Fade = 101,
        BlinkTimeout = 200,
        FadeTimeout = 201,

        Stop = 300,
        PrintTime = 301
    };
    bool blinkOn = false;
    bool isFading = false;

    DmxCommand commandList[18] = {
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
            {31000, Fade,         255},
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
                        PrintTimeToSerial(currentMillis);
                    case Blink:
                        StartBlink(currentMillis);
                        break;
                    case Fade:
                        StartFading(currentMillis);
                    case BlinkTimeout:
                        blinkTimeout = cmd.value;
                    case FadeTimeout:
                        fadingTimeout = cmd.value;
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
        } else if (isFading && (currentMillis - fadingLastCall) > fadingTimeout) {
            totalDimmingValue--;
            Set(TotalDimming, totalDimmingValue);
            isFading = fadingInterval[1] < totalDimmingValue;
        }
    }

    void StartBlink(unsigned int currentMillis) {
        blinkOn = true;
        blinkStart = currentMillis;
        totalDimmingValue = 255;
        Set(TotalDimming, totalDimmingValue);
    }

    void StartFading(unsigned int currentMillis) {
        isFading = true;
        fadingLastCall = currentMillis;
        totalDimmingValue = fadingInterval[0];
        Set(TotalDimming, totalDimmingValue);
    }

protected:
    unsigned short commandIndex = 0;
    unsigned char totalDimmingValue = 0;

    unsigned int blinkStart = 0;
    unsigned short blinkTimeout = 100;

    unsigned int fadingLastCall = 0;
    unsigned char fadingTimeout = 7;
    unsigned char fadingInterval[2] = {
            255, //From
            0 //To
    };
};

#endif