/*
  TLE75080.h - SPI driver for TLE75080 8-channel high-side switch with diagnosis

  Copyright (c) 2026 Engeen

  This library is licensed under the MIT License.
  You may obtain a copy of the License in the LICENSE file
  accompanying this source code or at:
  https://opensource.org/licenses/MIT

  This software is provided "as is", without warranty of any kind,
  express or implied, including but not limited to the warranties of
  merchantability, fitness for a particular purpose and noninfringement.
*/

#pragma once

#include <Arduino.h>
#include <SPI.h>

#define MHz * 1000UL * 1000UL

// Read standard diagnosis command
#define TLE_CMD_READ_STD_DIAG     0x0001

// Read commands (fixed addresses)
#define TLE_CMD_READ_OUT          0x4002
#define TLE_CMD_READ_BIM          0x4102
#define TLE_CMD_READ_MAPIN0       0x4402
#define TLE_CMD_READ_MAPIN1       0x4502
#define TLE_CMD_READ_INST         0x4602
#define TLE_CMD_READ_DIAG_IOL     0x4802
#define TLE_CMD_READ_DIAG_OSM     0x4902
#define TLE_CMD_READ_DIAG_OLON    0x4A02
#define TLE_CMD_READ_DIAG_OLONEN  0x4B02
#define TLE_CMD_READ_HWCR         0x4C02
#define TLE_CMD_READ_HWCR_OCL     0x4D02
#define TLE_CMD_READ_HWCR_PWM     0x4E02
#define TLE_CMD_READ_PWM_CR0      0x5002

// Write commands (upper byte = command, lower byte = data)
#define TLE_CMD_WRITE_OUT         0x8000
#define TLE_CMD_WRITE_BIM         0x8100
#define TLE_CMD_WRITE_MAPIN0      0x8400
#define TLE_CMD_WRITE_MAPIN1      0x8500

// PWM_CR0 write (mode encoded in command)
#define TLE_CMD_WRITE_PWM_CR0_0   0x9000
#define TLE_CMD_WRITE_PWM_CR0_1   0x9100
#define TLE_CMD_WRITE_PWM_CR0_2   0x9200
#define TLE_CMD_WRITE_PWM_CR0_3   0x9300


class TLE75080 {
public:
    explicit TLE75080(uint8_t csPin, uint8_t enablePin, SPIClass &spi = SPI);

    union {
      struct {
        bool out0 : 1;
        bool out1 : 1;
        bool out2 : 1;
        bool out3 : 1;
        bool out4 : 1;
        bool out5 : 1;
        bool out6 : 1;
        bool out7 : 1;
      };
      byte out;
    };

    void begin();
    void update();
    
    uint16_t readDiag() { return readFrame(TLE_CMD_READ_STD_DIAG); }
    uint16_t readInst() { return readFrame(TLE_CMD_READ_INST); }
    uint16_t readOutputs() { return readFrame(TLE_CMD_READ_OUT); }

private:
    uint8_t _csPin;
    uint8_t _enablePin;
    SPIClass *_spi;
    
    uint16_t readFrame(uint16_t cmd);
    uint16_t transfer16(uint16_t tx);
    void beginTransaction();
    void endTransaction();
};
