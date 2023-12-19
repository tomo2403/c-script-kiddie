#ifndef DmxDevice_h
#define DmxDevice_h

#include "DmxSimple.h"
#include "DmxCommand.h"

class DmxDevice {
public:
  virtual ~DmxDevice() = default;  // Virtueller Destruktor
  DmxDevice(unsigned int channels, unsigned short address)
    : Channels(channels), Address(address) {}

  unsigned short Channels;
  unsigned short Address;

  enum Functions {};

  virtual void Set(Functions channel, unsigned char value) {};
};
#endif