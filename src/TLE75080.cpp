/*
  TLE75080.cpp - SPI driver for TLE75080 8-channel high-side switch with diagnosis

  Copyright (c) 2026 Engeen

  This library is licensed under the MIT License.
  You may obtain a copy of the License in the LICENSE file
  accompanying this source code or at:
  https://opensource.org/licenses/MIT

  This software is provided "as is", without warranty of any kind,
  express or implied, including but not limited to the warranties of
  merchantability, fitness for a particular purpose and noninfringement.
*/

#include "TLE75080.h"

TLE75080::TLE75080(uint8_t csPin, uint8_t enablePin, SPIClass &spi)
    : _csPin(csPin), _enablePin(enablePin), _spi(&spi), out(0) {}

void TLE75080::begin() {
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);

    pinMode(_enablePin, OUTPUT);
    digitalWrite(_enablePin, HIGH);

    _spi->begin();
}

void TLE75080::update() {
    beginTransaction();
    transfer16(TLE_CMD_WRITE_OUT + out);
    endTransaction();
}

uint16_t TLE75080::transfer16(uint16_t tx) {
    digitalWrite(_csPin, LOW);
    uint16_t rx = _spi->transfer16(tx);
    digitalWrite(_csPin, HIGH);
    return rx;
}

uint16_t TLE75080::readFrame(uint16_t cmd) {
    beginTransaction();

    // Send read-INST command
    transfer16(cmd);

    // Clock out the response with a harmless follow-up command
    uint16_t resp = transfer16(TLE_CMD_READ_STD_DIAG);

    endTransaction();
    return resp;
}

void TLE75080::beginTransaction() {
    // Conservative starting point: 1 MHz.
    // The datasheet says SPI supports up to 5 MHz (page 3).
    // If needed, adjust mode/speed after probing on your hardware.
    _spi->beginTransaction(SPISettings(5UL MHz, MSBFIRST, SPI_MODE1)); 
}

void TLE75080::endTransaction() {
    _spi->endTransaction();
}

