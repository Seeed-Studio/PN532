## NFC library for Arduino

This is an Arduino library for PN532 to use NFC technology.
It is for [NFC Shield](http://goo.gl/Cac2OH) and [Xadow NFC](http://goo.gl/qBZMt0).

[![NFC Shield](http://www.seeedstudio.com/depot/bmz_cache/a/abe9904d46e29565fb15ec36e17a4a52.image.114x85.jpg)](http://goo.gl/Cac2OH)
[![Xadow NFC](http://www.seeedstudio.com/depot/bmz_cache/d/d5f551a693fee5342877864ca5580cb6.image.114x85.jpg)](http://goo.gl/qBZMt0)

### Features
+ Support I2C, SPI and HSU of PN532
+ Read/write Mifare Classic Card
+ Works with [Don's NDEF Library](http://goo.gl/jDjsXl)
+ Communicate with android 4.0+([Lists of devices supported](https://github.com/Seeed-Studio/PN532/wiki/List-of-devices-supported))
+ Support [mbed platform](http://goo.gl/kGPovZ)
+ Card emulation (NFC Type 4 tag)

### Getting Started
+ Easy way

  1. Download [zip file](http://goo.gl/F6beRM) and extract the 4 folders(PN532, PN532_SPI, PN532_I2C and PN532_HSU) into Arduino's libraries.
  2. Downlaod [Don's NDEF library](http://goo.gl/ewxeAe) and extract it intro Arduino's libraries.
  3. Follow the examples of the two libraries.

+ Git way (recommended)

  1. Get PN532 library and NDEF library

```
cd {Arduino}\libraries  
git clone https://github.com/Seeed-Studio/PN532.git .
git clone https://github.com/don/NDEF.git NDEF

```

  2. Follow the examples of the two libraries

### Contribution
It's based on [Adafruit_NFCShield_I2C](http://goo.gl/pk3FdB). 
[Seeed Studio](http://goo.gl/zh1iQh) rewrite the library to make it easy to support different interfaces and platforms. 
@Don writes the [NDEF library](http://goo.gl/jDjsXl) to make it more easy to use. 
@JiapengLi adds HSU interface.
@awieser adds card emulation function.

