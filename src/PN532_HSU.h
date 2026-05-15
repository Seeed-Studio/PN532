
#ifndef __PN532_HSU_H__
#define __PN532_HSU_H__


#ifdef USE_SOFT_SERIAL_PIN
#include <SoftwareSerial.h>
#define get_serial(x) (static_cast<SoftwareSerial*>(x))
#else
#define get_serial(x) (static_cast<HardwareSerial*>(x))
#endif


#include "PN532Interface.h"
#include "Arduino.h"

#define PN532_HSU_DEBUG

#define PN532_HSU_READ_TIMEOUT (1000)

class PN532_HSU : public PN532Interface
{
public:
#ifdef ESP32
    PN532_HSU(HardwareSerial &serial, int8_t rxPin = -1, int8_t txPin = -1);
#else
#ifdef USE_SOFT_SERIAL_PIN
    PN532_HSU(SoftwareSerial &serial);
#else
    PN532_HSU(HardwareSerial &serial);
#endif
#endif

    void begin();
    void wakeup();
    virtual int8_t writeCommand(const uint8_t *header, uint8_t hlen, const uint8_t *body = 0, uint8_t blen = 0);
    int16_t readResponse(uint8_t buf[], uint16_t len, uint16_t timeout);

private:
    // HardwareSerial *_serial;
    void *hsu_serial;
    uint8_t command;
#ifdef ESP32
    int8_t _rxPin;
    int8_t _txPin;
#endif
    int8_t readAckFrame();

    int8_t receive(uint8_t *buf, int len, uint16_t timeout = PN532_HSU_READ_TIMEOUT);
};

#endif
