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

    DmxCommand commandList[49] = {
            {1,     BlueDimming,  200},
            {2,     GreenDimming, 200},
            {3,     Pan,          128},
            {4,     Tilt,         128},
            {4700,  Speed,        251},
            {4701,  Effect,       255},
            {4702,  Tilt,         255},
            {4703,  Effect,       190},
            {16000, Speed,        0},
            {16001, Effect,       0},
            {16002, Effect,       255},

            {16003, Pan,          255},
            {16004, Tilt,         255},
            {16005, BlueDimming,  0},
            {16005, GreenDimming, 0},
            {16005, RedDimming,   255},

            {18000, Speed,        100},
            {18000, Pan,          0},
            {18000, Tilt,         0},
            {18001, GreenDimming, 100},

            {21000, Pan,          200},
            {21000, Tilt,         180},
            {21001, RedDimming,   0},
            {21001, WhiteDimming, 100},

            {24000, Pan,          0},
            {24000, Tilt,         0},
            {24001, BlueDimming,  100},

            {26000, Pan,          80},
            {26000, Tilt,         190},
            {26001, BlueDimming,  0},
            {26001, GreenDimming, 0},
            {26001, RedDimming,   0},
            {26001, WhiteDimming, 255},

            {27000, Pan,          40},
            {27000, Tilt,         150},
            {27001, WhiteDimming, 0},
            {27001, BlueDimming,  255},

            {28000, Pan,          80},
            {28000, Tilt,         190},
            {28001, RedDimming,   250},

            {29000, Pan,          255},
            {29000, Tilt,         0},
            {29001, BlueDimming,  0},
            {29001, GreenDimming, 255},

            {30500, Speed,        190},
            {30501, Pan,          128},
            {30501, Tilt,         128},

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