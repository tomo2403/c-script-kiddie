#ifndef DmxCommand_h
#define DmxCommand_h

struct DmxCommand {
    unsigned int executionTime;
    int function;
    unsigned char value;
};
#endif