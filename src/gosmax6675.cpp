#include <Arduino.h>

#include "gosmax6675.h"

#define MAX_6675_ERROR_COUNT  1
#define MAX_6675_ERROR_LENGTH 9 /* 8 character plus '\0' */

#define GOS_MAX_6675_ERRT_OPEN "OPEN"

namespace gos {

Max6675::Max6675(
  const uint8_t&  pincs,   /* PIN for Chip Select CS is often 9 */
  const uint32_t& clock,   /* SPI CLOCK 1000000 (1MHz) */
  const uint8_t&  order,   /* SPI bit order MSB FIRST */
  const uint8_t&  mode) :  /* MAX6677 works in MODE1 (or MODE3?) */
  pincs_(pincs), spisettings_(clock, order, mode) {
}

void Max6675::initialize() {
  pinMode(pincs_, OUTPUT);
  digitalWrite(pincs_, HIGH);
}

bool Max6675::read(double& value) {
  SPI.beginTransaction(spisettings_);
  digitalWrite(pincs_, LOW);
#ifndef SPI_NOT_USE_16_MAX_6675
  raw_ = SPI.transfer16(0x0000);
#else
  raw_  = SPI.transfer(0x00) << 8;
  raw_ |= SPI.transfer(0x00);
#endif
  digitalWrite(pincs_, HIGH);
  SPI.endTransaction();

  if (!(raw_ & 0x0004)) {
    value = (raw_ >> 3) / 4.0;
    return true;
  } else {
    return false;
  }
}

#ifndef SPI_NO_ERROR_HANDLING_MAX_6675
const char* Max6675::error(uint8_t& length) {
  if (raw_ & 0x0004) {
    length = sizeof(GOS_MAX_6675_ERRT_OPEN);
    return GOS_MAX_6675_ERRT_OPEN;
  } else {
    length = 0;
    return nullptr;
  }
}
#endif

}
