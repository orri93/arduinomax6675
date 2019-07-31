#ifndef _GOS_ARDUINO_LIBRARY_MAX_6675_H_
#define _GOS_ARDUINO_LIBRARY_MAX_6675_H_

#include <Arduino.h>

#include <SPI.h>

#define SPI_CLOCK_MAX_6675         1000000 /* (1MHz) */
#define SPI_MODE_MAX_6675        SPI_MODE1
#define SPI_BIT_ORDER_MAX_6675    MSBFIRST

namespace gos {
class Max6675 {
public:
  Max6675(
    const uint8_t&  pincs = 9,                        /* PIN for Chip Select CS is often 9 */
    const uint32_t& clock = SPI_CLOCK_MAX_6675,       /* SPI CLOCK 1000000 (1MHz) */
    const uint8_t&  order = SPI_BIT_ORDER_MAX_6675,   /* SPI bit order MSB FIRST */
    const uint8_t&  mode = SPI_MODE_MAX_6675);        /* MAX6677 works in MODE1 (or MODE3?) */
  void initialize();
  bool read(double& value);
#ifndef SPI_NO_ERROR_HANDLING_MAX_6675
  const char* error(uint8_t& length);
#endif
private:
  uint8_t pincs_;
  uint16_t raw_;
  SPISettings spisettings_;
};
}

#endif /* _GOS_ARDUINO_LIBRARY_MAX_31865_H_ */
