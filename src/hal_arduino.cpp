#include "hal_arduino.hpp"

#include <Arduino.h>

#include "hal_error.hpp"

using namespace nes::rob;

namespace
{
    // Max delay of 16383 guaranteed to be accurate by Arduino reference
    // https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/
    static const unsigned int MAX_DELAY_MICROSECONDS = 16383;
} // namespace

std::error_code
HalArduino::delayMicroseconds (
    unsigned int us_
) const {
    while (MAX_DELAY_MICROSECONDS < us_) {
        us_ -= MAX_DELAY_MICROSECONDS;
        ::delayMicroseconds(MAX_DELAY_MICROSECONDS);
    }
    ::delayMicroseconds(us_);
    return make_error_code(hal_error::success);
}

std::error_code
HalArduino::digitalWrite (
    unsigned int pin_,
    int state_
) const {
    ::digitalWrite(pin_,state_);
    return make_error_code(hal_error::success);
}

std::error_code
HalArduino::init (
    void * params_
) {
    (void)params_; // ignore parameter
    return make_error_code(hal_error::success);
}

std::error_code
HalArduino::pinMode (
    unsigned int pin_,
    int mode_
) const {
    ::pinMode(pin_,mode_);
    return make_error_code(hal_error::success);
}

const int HardwareAbstractionLayer::PIN_STATE_HIGH = HIGH;
const int HardwareAbstractionLayer::PIN_MODE_INPUT = INPUT;
const int HardwareAbstractionLayer::PIN_MODE_INPUT_PULLUP = INPUT_PULLUP;
const int HardwareAbstractionLayer::PIN_STATE_LOW = LOW;
const int HardwareAbstractionLayer::PIN_MODE_OUTPUT = OUTPUT;
