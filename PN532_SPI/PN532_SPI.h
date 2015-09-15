
#ifndef __PN532_SPI_H__
#define __PN532_SPI_H__

#include <SPI.h>
#include "PN532Interface.h"

class PN532_SPI : public PN532Interface {
public:
    PN532_SPI(SPIClass &spi, uint8_t ss);
    
    void begin();
    void wakeup();
    int8_t writeCommand(const uint8_t *header, uint8_t hlen, const uint8_t *body = 0, uint8_t blen = 0);

    int16_t readResponse(uint8_t buf[], uint8_t len, uint16_t timeout);
    
private:
    SPIClass* _spi;
    SPISettings _spiSettings;
    uint8_t   _ss;
    uint8_t command;
    
    boolean isReady();
    void writeFrame(const uint8_t *header, uint8_t hlen, const uint8_t *body = 0, uint8_t blen = 0);
    int8_t readAckFrame();
    
    inline void write(uint8_t data) {
        _spi->beginTransaction(_spiSettings);
        _spi->transfer(data);
        _spi->endTransaction();
    };

    inline uint8_t read() {
        uint8_t retVal;
        _spi->beginTransaction(_spiSettings);
        retVal=_spi->transfer(0);
        _spi->endTransaction();
        return retVal;
    };
};

#endif
