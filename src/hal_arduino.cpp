#include "hal_arduino.hpp"

#include <Arduino.h>

int
HalArduino::delayMicroseconds (
    unsigned int us_
) const {
    while (MAX_DELAY_MICROSECONDS < us_) {
        us_ -= MAX_DELAY_MICROSECONDS;
        ::delayMicroseconds(MAX_DELAY_MICROSECONDS);
    }
    ::delayMicroseconds(us_);
    return 0;
}

int
HalArduino::digitalWrite (
    unsigned int pin_,
    int state_
) const {
    ::digitalWrite(pin_,state_);
    return 0;
}

int
HalArduino::pinMode (
    unsigned int pin_,
    int mode_
) const {
    ::pinMode(pin_,mode_);
    return 0;
}

const int HalGpio::PIN_STATE_HIGH = HIGH;
const int HalGpio::PIN_MODE_INPUT = INPUT;
const int HalGpio::PIN_MODE_INPUT_PULLUP = INPUT_PULLUP;
const int HalGpio::PIN_STATE_LOW = LOW;
const int HalGpio::PIN_MODE_OUTPUT = OUTPUT;
