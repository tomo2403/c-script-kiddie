#ifndef MiniMovingHead14Ch_h
#define MiniMovingHead14Ch_h

#include "DmxDevice.h"

class MiniMovingHead14Ch : public DmxDevice {
public:
    explicit MiniMovingHead14Ch(unsigned short address)
            : DmxDevice(address) {}
    enum Functions {
        Delay = 0,
        Pan = 1,
        PanFine = 2,
        Tilt = 3,
        TiltFine = 4,
        Speed = 5,
        Effect = 6,
        RedDimming = 7,
        GreenDimming = 8,
        BlueDimming = 9,
        WhiteDimming = 10,
        ColorAssortment = 11,
        ColorSpeed = 12,
        AutoMovement = 13,
        Reset = 14
    };

    unsigned int commandIndex = 0;
    DmxCommand commandList[1] = {
            {3000, Pan, 100}
    };

    void RunTick(unsigned long currentMillis) override {
        DmxCommand cmd = commandList[commandIndex];
        if (cmd.executionTime < currentMillis) {
            switch (cmd.function) {
                default:
                    Set(static_cast<Functions>(cmd.function), cmd.value);
                    break;
            }
            commandIndex++;
        }
    };

    virtual void Set(Functions channel, unsigned char value) {
        DmxSimple.write(Address + channel - 1, value);
    }
    void CleanUp(unsigned long currentMillis) override {

    }

};
#endif