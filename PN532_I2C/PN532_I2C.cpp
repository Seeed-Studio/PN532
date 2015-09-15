
#include "PN532_I2C.h"
#include "PN532_debug.h"
#include "Arduino.h"

#define PN532_I2C_ADDRESS       (0x48 >> 1)


PN532_I2C::PN532_I2C(TwoWire &wire, uint8_t pinReset, uint8_t pinIrq):
    _wire(&wire),
    _reset(pinReset),
    _irq(pinIrq)
{
    command = 0;
}

void PN532_I2C::begin()
{
    _wire->begin();
    pinMode(_reset, OUTPUT);
    pinMode(_irq, INPUT);
    // Reset the PN532
    digitalWrite(_reset, HIGH);
    digitalWrite(_reset, LOW);
    delay(400);
    digitalWrite(_reset, HIGH);
    delay(10);  // Small delay required before taking other actions after reset.
    // See timing diagram on page 209 of the datasheet, section 12.23.
}

void PN532_I2C::wakeup()
{
    _wire->beginTransmission(PN532_I2C_ADDRESS); // I2C start
    delay(20);
    _wire->endTransmission();                    // I2C end
}

int8_t PN532_I2C::writeCommand(const uint8_t *header, uint8_t hlen, const uint8_t *body, uint8_t blen)
{
    command = header[0];
    _wire->beginTransmission(PN532_I2C_ADDRESS);
    
    write(PN532_PREAMBLE);
    write(PN532_STARTCODE1);
    write(PN532_STARTCODE2);
    
    uint8_t length = hlen + blen + 1;   // length of data field: TFI + DATA
    write(length);
    write(~length + 1);                 // checksum of length
    
    write(PN532_HOSTTOPN532);
    uint8_t sum = PN532_HOSTTOPN532;    // sum of TFI + DATA
    
    DMSG("write: ");

    for (uint8_t i = 0; i < hlen; i++) {
        if (write(header[i])) {
            sum += header[i];
            
            DMSG_HEX(header[i]);
        } else {
            DMSG_STR("Header too long, I2C doesn't support such a big packet");     // I2C max packet: 32 bytes
            return PN532_INVALID_FRAME;
        }
    }

    for (uint8_t i = 0; i < blen; i++) {
        if (write(body[i])) {
            sum += body[i];
            
            DMSG_HEX(body[i]);
        } else {
            DMSG_STR("Body too long, I2C doesn't support such a big packet");     // I2C max packet: 32 bytes
            return PN532_INVALID_FRAME;
        }
    }

    uint8_t checksum = ~sum + 1;            // checksum of TFI + DATA
    write(checksum);
    write(PN532_POSTAMBLE);
    
    _wire->endTransmission();
    
    DMSG_STR();

    return readAckFrame();
}

int16_t PN532_I2C::readResponse(uint8_t buf[], uint8_t len, uint16_t timeout)
{
    if(!waitready(timeout)){
        return PN532_TIMEOUT;
    }
    if (_wire->requestFrom(PN532_I2C_ADDRESS, len + 2)) {
        if (!bitRead(read(),0)) {  // check first byte --- status
            return PN532_INVALID_FRAME;
        }
    }

    if (0x00 != read()      ||       // PREAMBLE
            0x00 != read()  ||       // STARTCODE1
            0xFF != read()           // STARTCODE2
            ) {
        return PN532_INVALID_FRAME;
    }
    
    uint8_t length = read();
    if (0 != (uint8_t)(length + read())) {   // checksum of length
        return PN532_INVALID_FRAME;
    }
    
    uint8_t cmd = command + 1;               // response command
    if (PN532_PN532TOHOST != read() || (cmd) != read()) {
        return PN532_INVALID_FRAME;
    }
    
    length -= 2;
    if (length > len) {
        return PN532_NO_SPACE;  // not enough space
    }
    
    DMSG("read:  ");
    DMSG_HEX(cmd);
    
    uint8_t sum = PN532_PN532TOHOST + cmd;
    for (uint8_t i = 0; i < length; i++) {
        buf[i] = read();
        sum += buf[i];
        
        DMSG_HEX(buf[i]);
    }
    DMSG_STR();
    
    uint8_t checksum = read();
    if (0 != (uint8_t)(sum + checksum)) {
        DMSG_STR("checksum is not ok");
        return PN532_INVALID_FRAME;
    }
    read();         // POSTAMBLE
    
    return length;
}

int8_t PN532_I2C::readAckFrame()
{
    const uint8_t PN532_ACK[] = {0, 0, 0xFF, 0, 0xFF, 0};
    uint8_t ackBuf[sizeof(PN532_ACK)];
    
    DMSG("wait for ack at : ");
    DMSG_STR(millis());

    if(!waitready(PN532_ACK_WAIT_TIME)){
        return PN532_TIMEOUT;
    }
    if (_wire->requestFrom(PN532_I2C_ADDRESS,  sizeof(PN532_ACK) + 1)) {
        if (!bitRead(read(),0)) {  // check first byte --- status
            return PN532_INVALID_ACK;
        }
    }

    DMSG("ready at : ");
    DMSG_STR(millis());
    

    for (uint8_t i = 0; i < sizeof(PN532_ACK); i++) {
        ackBuf[i] = read();
    }
    
    if (memcmp(ackBuf, PN532_ACK, sizeof(PN532_ACK))) {
        DMSG_STR("Invalid ACK");
        return PN532_INVALID_ACK;
    }
    
    return 0;
}

bool PN532_I2C::waitready(uint16_t timeout){
    unsigned long ulStartTime=millis();
    while(timeout>0 && millis()-ulStartTime<timeout){
         if(digitalRead(_irq)==LOW){
            return true;
        }
    }
    return false;
}

