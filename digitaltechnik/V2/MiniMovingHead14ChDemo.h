#ifndef MiniMovingHead14ChDemo_h
#define MiniMovingHead14ChDemo_h

#include "MiniMovingHead14Ch.h"

class MiniMovingHead14ChDemo : public MiniMovingHead14Ch {
public:
    MiniMovingHead14ChDemo(unsigned short address) : MiniMovingHead14Ch(address) {}

    void Set(Functions channel, unsigned char value) {
        DmxSimple.write(Channels + (channel - 1), value);
    }
};
#endif