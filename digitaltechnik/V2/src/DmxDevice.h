#ifndef DmxDevice_h
#define DmxDevice_h

#include "DmxSimple.h"
#include "DmxCommand.h"
#include <Arduino.h>

class DmxDevice {
public:
    virtual ~DmxDevice() = default;  // Virtueller Destruktor
    explicit DmxDevice(unsigned short address)
            : Address(address) {}

    unsigned short Address;

    virtual void Set(int channel, unsigned char value) {
        DmxSimpleClass::write(static_cast<int>(Address + channel), value);
    };

    virtual void RunTick(unsigned int currentMillis) = 0;

    virtual void CleanUp(unsigned int currentMillis) = 0;

    static void PrintTimeToSerial(unsigned int currentMillis) {
        Serial.print("Time elapsed: ");
        Serial.print(currentMillis);
        Serial.println("ms");
    }
};

#endif