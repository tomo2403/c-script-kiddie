#include "DmxSimple.h"

class DmxDevice {
public:
    virtual ~DmxDevice() = default;  // Virtueller Destruktor
    DmxDevice(unsigned short channels, unsigned short address) : Channels(channels), Address(address) {}

    unsigned short Channels;
    unsigned short Address;

    enum Functions {};

    virtual void Set(Functions channel, short value);
};