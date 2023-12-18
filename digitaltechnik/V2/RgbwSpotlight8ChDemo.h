#ifndef RgbwSpotlight8ChDemo_h
#define RgbwSpotlight8ChDemo_h

#include "RgbwSpotlight8Ch.h"

class RgbwSpotlight8ChDemo : public RgbwSpotlight8Ch {
public:
    RgbwSpotlight8ChDemo(unsigned short address) : RgbwSpotlight8Ch(address) {}

    void Set(Functions channel, unsigned char value) {
        DmxSimple.write(Channels + (channel - 1), value);
    }
};
#endif