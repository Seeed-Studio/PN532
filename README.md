## NFC library 

This is an library for PN532 to use NFC technology.
It is for [NFC Shield](http://goo.gl/Cac2OH) and [Grove - NFC](http://goo.gl/L3Uw5G).

[![NFC Shield](https://statics3.seeedstudio.com/images/113030001%201.jpg)](http://goo.gl/Cac2OH)
[![Grove - NFC](https://statics3.seeedstudio.com/images/product/grove%20nfc.jpg)](http://goo.gl/L3Uw5G)

### Features
+ Support all interfaces of PN532 (I2C, SPI, HSU )
+ Read/write Mifare Classic Card
+ Works with [Don's NDEF Library](http://goo.gl/jDjsXl)
+ Communicate with android 4.0+([Lists of devices supported](https://github.com/Seeed-Studio/PN532/wiki/List-of-devices-supported))
+ Support [mbed platform](http://goo.gl/kGPovZ)
+ Card emulation (NFC Type 4 tag)

### To Do
+ To support more than one INFO PDU of P2P communication
+ To read/write NFC Type 4 tag

### Getting Started
+ Easy way

  1. Download [zip file](https://github.com/Seeed-Studio/PN532/archive/refs/heads/arduino.zip) and extract the 4 folders(PN532, PN532_SPI, PN532_I2C and PN532_HSU) into Arduino's libraries.
  2. Download [Don's NDEF library](https://github.com/don/NDEF/archive/refs/heads/master.zip)， extract it into Arduino's libraries and rename it to NDEF.
  3. Follow the examples of the two libraries.

+ Git way for Linux/Mac (recommended)

  1. Get PN532 library and NDEF library

          cd {Arduino}\libraries  
          git clone --recursive https://github.com/Seeed-Studio/PN532.git NFC
          ln -s NFC/PN532 ./
          ln -s NFC/PN532_SPI ./
          ln -s NFC/PN532_I2C ./
          ln -s NFC/PN532_HSU ./
          ln -s NFC/NDEF ./

  2. Follow the examples of the two libraries

### Contribution
It's based on [Adafruit_NFCShield_I2C](http://goo.gl/pk3FdB). 
[Seeed Studio](http://goo.gl/zh1iQh) rewrite the library to make it easy to support different interfaces and platforms. 
@Don writes the [NDEF library](http://goo.gl/jDjsXl) to make it more easy to use. 
@JiapengLi adds HSU interface.
@awieser adds card emulation function.

## HSU Interface

HSU is short for High Speed Uart. HSU interface needs only 4 wires to connect PN532 with Arduino, [Sensor Shield](http://goo.gl/i0EQgd) can make it more easier. For some Arduino boards like [Leonardo][Leonardo], [DUE][DUE], [Mega][Mega] ect, there are more than one `Serial` on these boards, so we can use this additional Serial to control PN532, HSU uses 115200 baud rate .

To use the `Serial1` control PN532, refer to the code below.
```c++
	#include <PN532_HSU.h>
	#include <PN532.h>
	
	PN532_HSU pn532hsu(Serial1);
	PN532 nfc(pn532hsu);

	void setup(void)
	{
		nfc.begin();
		//...
	}
```
If your Arduino has only one serial interface and you want to keep it for control or debugging with the Serial Monitor, you can use the [`SoftwareSerial`][SoftwareSerial] library to control the PN532 by emulating a serial interface. Include `PN532_SWHSU.h` instead of `PN532_HSU.h`:
```c++
	#include <SoftwareSerial.h>
	#include <PN532_SWHSU.h>
	#include <PN532.h>
	
	SoftwareSerial SWSerial( 10, 11 ); // RX, TX

	PN532_SWHSU pn532swhsu( SWSerial );
	PN532 nfc( pn532swhsu );

	void setup(void)
	{
		nfc.begin();
		//...
	}
```
[Mega]: http://arduino.cc/en/Main/arduinoBoardMega
[DUE]: http://arduino.cc/en/Main/arduinoBoardDue
[Leonardo]: http://arduino.cc/en/Main/arduinoBoardLeonardo
[SoftwareSerial]: https://www.arduino.cc/en/Reference/softwareSerial

