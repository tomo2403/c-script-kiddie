#ifndef RgbwSpotlight8ChDemo_h
#define RgbwSpotlight8ChDemo_h

#include "RgbwSpotlight8Ch.h"

class RgbwSpotlight8ChDemo : public RgbwSpotlight8Ch {
public:
  explicit RgbwSpotlight8ChDemo(unsigned short address)
    : RgbwSpotlight8Ch(address) {}

  void Set(Functions channel, unsigned char value) override {
      switch (channel) {
          case 1:
              switch (value) {
                  case 0:
                      digitalWrite(Address, LOW);
                      break;
                  default:
                      digitalWrite(Address, HIGH);
                      break;
              }
              break;
          default:
              break;
      }
  }

  void CleanUp() override {
    if (blinkOn && (millis() - blinkStart) > 100) {
      digitalWrite(Address, LOW);
      blinkOn = false;
    }
  }
};
#endif