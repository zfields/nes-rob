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
{ }

LedNtscDriver::ErrorCode
LedNtscDriver::init (
    void * params_
) {
    ErrorCode result;

    // Ignore parameters
    (void)params_;

    // Configure the HAL GPIO
    if (_gpio->pinMode(_pin, HalGpio::PIN_MODE_OUTPUT)) {
        result = ErrorCode::E_HAL_FAIL;
    } else if (_gpio->digitalWrite(_pin, HalGpio::PIN_STATE_LOW)) {
        result = ErrorCode::E_HAL_FAIL;
    } else {
        result = ErrorCode::SUCCESS;
    }

    return result;
}

LedNtscDriver::ErrorCode
LedNtscDriver::pulse (
    unsigned int active_
) const {
    ErrorCode result;

    if (active_) {
        if (_gpio->digitalWrite(_pin, HalGpio::PIN_STATE_HIGH)) {
            result = ErrorCode::E_HAL_FAIL;
        } else if (_clock->delayMicroseconds(1500)) {
            result = ErrorCode::E_HAL_FAIL;
        } else if (_gpio->digitalWrite(_pin, HalGpio::PIN_STATE_LOW)) {
            result = ErrorCode::E_HAL_FAIL;
        } else if (_clock->delayMicroseconds(15166)) {
            result = ErrorCode::E_HAL_FAIL;
        } else {
            result = ErrorCode::SUCCESS;
        }
    } else {
        if (_gpio->digitalWrite(_pin, HalGpio::PIN_STATE_LOW)) {
            result = ErrorCode::E_HAL_FAIL;
        } else if (_clock->delayMicroseconds(16666)) {
            result = ErrorCode::E_HAL_FAIL;
        } else {
            result = ErrorCode::SUCCESS;
        }
    }

    return result;
}
