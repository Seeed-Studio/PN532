#ifndef __DEBUG_H__
#define __DEBUG_H__

#define DEBUG

#include "Arduino.h"

#ifdef ARDUINO_STM_NUCLEU_F103RB
    #define SERIALPORT Serial1
#else
    #define SERIALPORT Serial
#endif

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
