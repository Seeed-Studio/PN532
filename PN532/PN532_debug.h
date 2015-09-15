#ifndef __DEBUG_H__
#define __DEBUG_H__

//#define DEBUG

#include "Arduino.h"

#define SERIALPORT Serial

#ifdef DEBUG
    #define DMSG(args...)       SERIALPORT.print(args)
    #define DMSG_STR(str)       SERIALPORT.println(str)
    #define DMSG_HEX(num)       SERIALPORT.print(' '); SERIALPORT.print(num, HEX)
    #define DMSG_INT(num)       SERIALPORT.print(' '); SERIALPORT.print(num)
#else
    #define DMSG(args...)
    #define DMSG_STR(str)
    #define DMSG_HEX(num)
    #define DMSG_INT(num)
#endif

#endif
