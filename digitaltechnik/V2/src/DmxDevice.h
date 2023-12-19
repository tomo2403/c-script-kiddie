#ifndef DmxDevice_h
#define DmxDevice_h

#include "DmxSimple.h"
#include "DmxCommand.h"

class DmxDevice {
public:
    virtual ~DmxDevice() = default;  // Virtueller Destruktor
    explicit DmxDevice(unsigned short address)
            : Address(address) {}

    unsigned short Address;

    virtual void RunTick(unsigned long currentMillis) = 0;
    virtual void CleanUp(unsigned long currentMillis) = 0;
};
#endif