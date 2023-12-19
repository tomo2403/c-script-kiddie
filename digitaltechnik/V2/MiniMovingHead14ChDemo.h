#ifndef MiniMovingHead14ChDemo_h
#define MiniMovingHead14ChDemo_h

#include "MiniMovingHead14Ch.h"

class MiniMovingHead14ChDemo : public MiniMovingHead14Ch {
public:
  explicit MiniMovingHead14ChDemo(unsigned short address)
    : MiniMovingHead14Ch(address) {}

  void Set(Functions channel, unsigned char value) override {
    switch (channel) {
      case 6:
        if (value <= 7)
          digitalWrite(Address, LOW);
        else if (value <= 134)
          digitalWrite(Address, HIGH);
        break;
      default:
        break;
    }
  }
};
#endif