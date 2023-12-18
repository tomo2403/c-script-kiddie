#ifndef RgbwSpotlight8Ch_h
#define RgbwSpotlight8Ch_h

#include "DmxDevice.h"

class RgbwSpotlight8Ch : public DmxDevice {
public:
  RgbwSpotlight8Ch(unsigned short address)
    : DmxDevice(8, address) {}
  enum Functions {
    Delay = 0,
    TotalDimming = 1,
    RedDimming = 2,
    GreenDimming = 3,
    BlueDimming = 4,
    WhiteDimming = 5,
    TotalStrobe = 6,
    FuncSelection = 7,
    FuncSpeed = 8
  };

  void Set(Functions channel, unsigned char value) {
    DmxSimple.write(Channels + (channel - 1), value);
  }
};
#endif