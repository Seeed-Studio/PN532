## NFC library for Arduino

This is an Arduino library for PN532 to use NFC technology.
It is for [NFC Shield](http://goo.gl/Cac2OH), [Xadow NFC](http://goo.gl/qBZMt0) and [Grove - NFC](http://goo.gl/L3Uw5G).

[![NFC Shield](http://www.seeedstudio.com/depot/bmz_cache/a/abe9904d46e29565fb15ec36e17a4a52.image.114x85.jpg)](http://goo.gl/Cac2OH)
[![Xadow NFC](http://www.seeedstudio.com/depot/bmz_cache/d/d5f551a693fee5342877864ca5580cb6.image.114x85.jpg)](http://goo.gl/qBZMt0)
[![Grove - NFC](http://www.seeedstudio.com/depot/bmz_cache/0/0170da02ed762650524f1d6bdbe1eae5.image.114x85.jpg)](http://goo.gl/L3Uw5G)

### Features
+ Support I2C, SPI and HSU of PN532
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

  1. Download zip file and extract the 5 folders(PN532, PN532_SPI, PN532_I2C, PN532_HSU, NDEF) to Arduino's libraries.

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

[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/PN532)](https://github.com/igrigorik/ga-beacon)
