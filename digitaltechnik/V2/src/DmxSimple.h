/**
 * DmxSimple - A simple interface to DMX.
 *
 * Copyright (c) 2008-2009 Peter Knight, Tinker.it! All rights reserved.
 */

#ifndef DmxSimple_h
#define DmxSimple_h

#if RAMEND <= 0x4FF
#define DMX_SIZE 128
#else
#define DMX_SIZE 512
#endif

class DmxSimpleClass {
public:
    static void maxChannel(int);
    static void write(int, uint8_t);
    static void usePin(uint8_t);
};

#endif