#ifndef HAL_ARDUINO_HPP
#define HAL_ARDUINO_HPP

#include "hal_clock.hpp"
#include "hal_gpio.hpp"

class HalArduino final : public HalClock, public HalGpio {
  public:
    // Max delay of 16383 guaranteed by Arduino reference
    // https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/
    static const unsigned int MAX_DELAY_MICROSECONDS = 16383;

    int delayMicroseconds (unsigned int pin) const override;
    int digitalWrite (unsigned int pin, int state) const override;
    int pinMode (unsigned int pin, int mode) const override;
};

#endif // HAL_ARDUINO_HPP
