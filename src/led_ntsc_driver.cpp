#include "led_ntsc_driver.hpp"

#include "hardware_abstraction_layer.hpp"
#include "pulse_driver_error.hpp"

using namespace nes::rob;

LedNtscDriver::LedNtscDriver (
    HardwareAbstractionLayer * hal_,
    unsigned int pin_
) :
    _hal(hal_),
    _pin(pin_)
{ }

std::error_code
LedNtscDriver::init (
    void * params_
) {
    std::error_code result;

    (void)params_;  // ignore parameters

    // Configure the HAL
    if (_hal->init(nullptr)) {
        result = make_error_code(pulse_driver_error::hal_init);
    } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_OUTPUT)) {
        result = make_error_code(pulse_driver_error::hal_gpio_config);
    } else if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
        result = make_error_code(pulse_driver_error::hal_gpio_state);
    } else {
        result = make_error_code(pulse_driver_error::success);
    }

    return result;
}

std::error_code
LedNtscDriver::pulse (
    unsigned int active_
) const {
    std::error_code result;

    if (active_) {
        // Enable LED
        if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_HIGH)) {
            result = make_error_code(pulse_driver_error::hal_gpio_state);
        } else if (_hal->delayMicroseconds(1500)) {
            result = make_error_code(pulse_driver_error::hal_clock);

        // Disable LED
        } else if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
            result = make_error_code(pulse_driver_error::hal_gpio_state);
        } else if (_hal->delayMicroseconds(15166)) {
            result = make_error_code(pulse_driver_error::hal_clock);

        // NTSC pulse generated successfully
        } else {
            result = make_error_code(pulse_driver_error::success);
        }
    } else {
        // Disable LED
        if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
            result = make_error_code(pulse_driver_error::hal_gpio_state);
        } else if (_hal->delayMicroseconds(16666)) {
            result = make_error_code(pulse_driver_error::hal_clock);

        // NTSC blank generated successfully
        } else {
            result = make_error_code(pulse_driver_error::success);
        }
    }

    return result;
}
