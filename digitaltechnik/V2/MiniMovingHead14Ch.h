#ifndef MiniMovingHead14Ch_h
#define MiniMovingHead14Ch_h

#include "DmxDevice.h"

class MiniMovingHead14Ch : public DmxDevice {
public:
    MiniMovingHead14Ch(unsigned short address) : DmxDevice(14, address) {}
    enum Functions {
        Pam = 1,
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

    void Set(Functions channel, unsigned char value) {
        DmxSimple.write(Channels + (channel - 1), value);
    }
};
#endif