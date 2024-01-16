#ifndef MiniMovingHead14Ch_h
#define MiniMovingHead14Ch_h

#include "DmxDevice.h"

class MiniMovingHead14Ch : public DmxDevice
{
public:
    explicit MiniMovingHead14Ch(unsigned short address) : DmxDevice(address)
    { }

    enum Functions
    {
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
        RGB = 102,
        BlinkTimeout = 200,

        Stop = 300,
        PrintTime = 301
    };
    bool blinkOn = false;
    bool isFading = false;

    void RunTick(uint16_t currentMillis, DmxCommand cmd) override
    {
        if (cmd.function != Stop)
        {
            switch (cmd.function)
            {
                case PrintTime:
                    PrintTimeToSerial(currentMillis);
                case Blink:
                    StartBlink(currentMillis);
                    break;
                case Fade:
                    fadingTimeout = cmd.value;
                    StartFading(currentMillis);
                case BlinkTimeout:
                    blinkTimeout = cmd.value;
                case Effect:
                    if (cmd.value > 8 && cmd.value < 134)
                    {
                        totalDimmingValue = cmd.value;
                    } else if (cmd.value >= 240)
                    {
                        totalDimmingValue = 134;
                    }
                    Set(Effect, totalDimmingValue);
                case RGB:
                    ConvertDecimalToRgb(cmd.value, red, green, blue);
                    Set(RedDimming, red);
                    Set(GreenDimming, green);
                    Set(BlueDimming, blue);
                    break;
                default:
                    Set(static_cast<Functions>(cmd.function), cmd.value);
                    break;
            }
        } else
        {
            Set(Effect, 0);
        }
    };

    void CleanUp(uint16_t currentMillis) override
    {
        if (blinkOn && (currentMillis - blinkStart) > blinkTimeout)
        {
            Set(Effect, totalDimmingValue);
            blinkOn = false;
        }

        if (isFading && (currentMillis - fadingLastCall) > fadingTimeout)
        {
            totalDimmingValue--;
            fadingLastCall = currentMillis;
            Set(Effect, totalDimmingValue);
            isFading = fadingInterval[1] < totalDimmingValue;
        }
    }

    void StartBlink(uint16_t currentMillis)
    {
        blinkOn = true;
        blinkStart = currentMillis;
        totalDimmingValue = 134;
        Set(Effect, totalDimmingValue);
    }

    void StartFading(uint16_t currentMillis)
    {
        isFading = true;
        fadingLastCall = currentMillis;
        totalDimmingValue = fadingInterval[0];
        Set(Effect, totalDimmingValue);
    }

protected:
    uint8_t totalDimmingValue = 7;

    uint16_t blinkStart = 0;
    unsigned short blinkTimeout = 100;

    uint16_t fadingLastCall = 0;
    uint8_t fadingTimeout = 14;
    uint8_t fadingInterval[2] = {
            134, //From
            7 //To
    };
};

#endif