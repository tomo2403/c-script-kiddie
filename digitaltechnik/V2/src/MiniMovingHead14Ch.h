#ifndef MiniMovingHead14Ch_h
#define MiniMovingHead14Ch_h

#include "DmxDevice.h"

class MiniMovingHead14Ch : public DmxDevice {
public:
    explicit MiniMovingHead14Ch(unsigned short address)
            : DmxDevice(address) {}

    enum Functions {
        Pan,
        PanFine,
        Tilt,
        TiltFine,
        Speed,
        Effect,
        RedDimming,
        GreenDimming,
        BlueDimming,
        WhiteDimming,
        ColorAssortment,
        ColorSpeed,
        Automatic,
        Reset,

        Blink = 100,
        Fade = 101,
        BlinkTimeout = 200,
        FadeTimeout = 201,

        Stop = 300,
        PrintTime = 301
    };
    bool blinkOn = false;
    bool isFading = false;

    DmxCommand commandList[5] = {
            {1, BlueDimming, 255},
            {2, Effect, 134},
            {3, Effect, 255},
            {31000, Fade, 255},
            {32800, Stop, 0}
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
                    case Effect:
                        if (cmd.value > 8 && cmd.value < 134) {
                            totalDimmingValue = cmd.value;
                        } else if (cmd.value >= 240) {
                            totalDimmingValue = 134;
                        }
                        Set(Effect, totalDimmingValue);
                    default:
                        Set(static_cast<Functions>(cmd.function), cmd.value);
                        break;
                }
                commandIndex++;
            } else {
                Set(Effect, 0);
            }
        }
    };

    void CleanUp(unsigned int currentMillis) override {
        if (blinkOn && (currentMillis - blinkStart) > blinkTimeout) {
            Set(Effect, totalDimmingValue);
            blinkOn = false;
        }

        if (isFading && (currentMillis - fadingLastCall) > fadingTimeout) {
            totalDimmingValue--;
            fadingLastCall = currentMillis;
            Set(Effect, totalDimmingValue);
            isFading = fadingInterval[1] < totalDimmingValue;
        }
    }

    void StartBlink(unsigned int currentMillis) {
        blinkOn = true;
        blinkStart = currentMillis;
        totalDimmingValue = 134;
        Set(Effect, totalDimmingValue);
    }

    void StartFading(unsigned int currentMillis) {
        isFading = true;
        fadingLastCall = currentMillis;
        totalDimmingValue = fadingInterval[0];
        Set(Effect, totalDimmingValue);
    }

protected:
    unsigned short commandIndex = 0;
    unsigned char totalDimmingValue = 7;

    unsigned int blinkStart = 0;
    unsigned short blinkTimeout = 100;

    unsigned int fadingLastCall = 0;
    unsigned char fadingTimeout = 14;
    unsigned char fadingInterval[2] = {
            134, //From
            7 //To
    };
};

#endif