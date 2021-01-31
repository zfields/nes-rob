#include "hal_arduino.hpp"

#include <Arduino.h>

namespace
{
    // Max delay of 16383 guaranteed to be accurate by Arduino reference
    // https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/
    static const unsigned int MAX_DELAY_MICROSECONDS = 16383;
} // namespace

int
HalArduino::delayMicroseconds (
    unsigned int us_
) const {
    while (MAX_DELAY_MICROSECONDS < us_) {
        us_ -= MAX_DELAY_MICROSECONDS;
        ::delayMicroseconds(MAX_DELAY_MICROSECONDS);
    }
    ::delayMicroseconds(us_);
    return static_cast<int>(ErrorCode::SUCCESS);
}

int
HalArduino::digitalWrite (
    unsigned int pin_,
    int state_
) const {
    ::digitalWrite(pin_,state_);
    return static_cast<int>(ErrorCode::SUCCESS);
}

int
HalArduino::init (
    void * params_
) {
    (void)params_; // ignore parameter
    return static_cast<int>(ErrorCode::SUCCESS);
}

int
HalArduino::pinMode (
    unsigned int pin_,
    int mode_
) const {
    ::pinMode(pin_,mode_);
    return static_cast<int>(ErrorCode::SUCCESS);
}

const int HardwareAbstractionLayer::PIN_STATE_HIGH = HIGH;
const int HardwareAbstractionLayer::PIN_MODE_INPUT = INPUT;
const int HardwareAbstractionLayer::PIN_MODE_INPUT_PULLUP = INPUT_PULLUP;
const int HardwareAbstractionLayer::PIN_STATE_LOW = LOW;
const int HardwareAbstractionLayer::PIN_MODE_OUTPUT = OUTPUT;
