#include "led_ntsc_driver.hpp"

#include "hardware_abstraction_layer.hpp"

LedNtscDriver::LedNtscDriver (
    HardwareAbstractionLayer * hal_,
    unsigned int pin_
) :
    _hal(hal_),
    _pin(pin_)
{ }

int
LedNtscDriver::init (
    void * params_
) {
    ErrorCode result;

    (void)params_;  // ignore parameters

    // Configure the HAL
    if (_hal->init(nullptr)) {
        result = ErrorCode::E_HAL_FAIL;
    } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_OUTPUT)) {
        result = ErrorCode::E_HAL_FAIL;
    } else if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
        result = ErrorCode::E_HAL_FAIL;
    } else {
        result = ErrorCode::SUCCESS;
    }

    return static_cast<int>(result);
}

int
LedNtscDriver::pulse (
    unsigned int active_
) const {
    ErrorCode result;

    if (active_) {
        if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_HIGH)) {
            result = ErrorCode::E_HAL_FAIL;
        } else if (_hal->delayMicroseconds(1500)) {
            result = ErrorCode::E_HAL_FAIL;
        } else if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
            result = ErrorCode::E_HAL_FAIL;
        } else if (_hal->delayMicroseconds(15166)) {
            result = ErrorCode::E_HAL_FAIL;
        } else {
            result = ErrorCode::SUCCESS;
        }
    } else {
        if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
            result = ErrorCode::E_HAL_FAIL;
        } else if (_hal->delayMicroseconds(16666)) {
            result = ErrorCode::E_HAL_FAIL;
        } else {
            result = ErrorCode::SUCCESS;
        }
    }

    return static_cast<int>(result);
}
