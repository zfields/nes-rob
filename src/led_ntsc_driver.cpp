#include "led_ntsc_driver.hpp"

#include "hal_clock.hpp"
#include "hal_gpio.hpp"

LedNtscDriver::LedNtscDriver (
    const HalClock * clock_,
    const HalGpio * gpio_,
    unsigned int pin_
) :
    _clock(clock_),
    _gpio(gpio_),
    _pin(pin_)
{
    _gpio->pinMode(_pin, HalGpio::PIN_MODE_OUTPUT);
    _gpio->digitalWrite(_pin, HalGpio::PIN_STATE_LOW);
}

int
LedNtscDriver::pulse (
    unsigned int active_
) const {
    if (active_) {
        _gpio->digitalWrite(_pin, HalGpio::PIN_STATE_HIGH);
        _clock->delayMicroseconds(1500);
        _gpio->digitalWrite(_pin, HalGpio::PIN_STATE_LOW);
        _clock->delayMicroseconds(15166);
    } else {
        _clock->delayMicroseconds(16666);
    }

    return 0;
}
