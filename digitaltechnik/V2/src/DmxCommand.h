#ifndef DmxCommand_h
#define DmxCommand_h

struct DmxCommand{
    unsigned long executionTime;
    int function;
    unsigned char value;
};
#endif