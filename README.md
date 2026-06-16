# Arduino-TLE75080
Simple SPI driver for Infineon's TLE75080 8-channel high side switch.

The TLE75080 is an 8 channel high side switch, switching up to 28V with 300 mA per channel and a total of 1A.

## Dependencies: 
  LibPrintf - https://github.com/embeddedartistry/arduino-printf

Tested on Arduino MKR series (SAMD21 based).

Demo output:
```
TLE75080 demo
INST frame: 0x8600
STD_DIAG frame: 0x3800
OUTPUT frame: 0x8000
OUTPUT frame: 00000001
STD_DIAG frame: 0x3000
OUTPUT frame: 00000011
STD_DIAG frame: 0x3000
OUTPUT frame: 00000111
STD_DIAG frame: 0x3000
OUTPUT frame: 00001111
STD_DIAG frame: 0x3000
OUTPUT frame: 00011110
STD_DIAG frame: 0x3000
OUTPUT frame: 00111100
STD_DIAG frame: 0x3000
```
