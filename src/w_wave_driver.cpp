#include "w_wave_driver.hpp"

#include "hardware_abstraction_layer.hpp"
#include "pulse_driver_error.hpp"

using namespace nes::rob;

WWaveDriver::WWaveDriver (
    HardwareAbstractionLayer * hal_,
    unsigned int pin_
) :
    _hal(hal_),
    _pin(pin_)
{ }

nes::rob::error_code
WWaveDriver::init (
    void * reserved_
) {
    nes::rob::error_code result;

    (void)reserved_;  // ignore parameters

    // Configure the HAL (high-impedence)
    if (_hal->init(nullptr)) {
        result = make_error_code(pulse_driver_error::hal_init);
    } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_INPUT)) {
        result = make_error_code(pulse_driver_error::hal_gpio_config);
    } else {
        result = make_error_code(pulse_driver_error::success);
    }

    return result;
}

nes::rob::error_code
WWaveDriver::pulse (
    void * reserved_
) const {
    nes::rob::error_code result;
    (void)reserved_;

    // Sink current for 800us (~4us of MCU instructions)
    if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_OUTPUT)) {
        result = make_error_code(pulse_driver_error::hal_gpio_config);
    } else if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
        result = make_error_code(pulse_driver_error::hal_gpio_state);
    } else if (_hal->delayMicroseconds(796)) {
        result = make_error_code(pulse_driver_error::hal_clock);

    // High-Z for 733us (~3us of MCU instructions)
    } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_INPUT)) {
        result = make_error_code(pulse_driver_error::hal_gpio_config);
    } else if (_hal->delayMicroseconds(730)) {
        result = make_error_code(pulse_driver_error::hal_clock);


    // Sink current for 800us (~4us of MCU instructions)
    } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_OUTPUT)) {
        result = make_error_code(pulse_driver_error::hal_gpio_config);
    } else if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
        result = make_error_code(pulse_driver_error::hal_gpio_state);
    } else if (_hal->delayMicroseconds(796)) {
        result = make_error_code(pulse_driver_error::hal_clock);

    // High-Z for remaining time slice (~3us of MCU instructions)
    } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_INPUT)) {
        result = make_error_code(pulse_driver_error::hal_gpio_config);
    } else if (_hal->delayMicroseconds(14330)) {
        result = make_error_code(pulse_driver_error::hal_clock);

    // W wave generated successfully
    } else {
        result = make_error_code(pulse_driver_error::success);
    }

    return result;
}

nes::rob::error_code
WWaveDriver::rest (
    void * reserved_
) const {
    nes::rob::error_code result;
    (void)reserved_;

    // High-Z for time slice (~3us of MCU instructions)
    if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_INPUT)) {
        result = make_error_code(pulse_driver_error::hal_gpio_config);
    } else if (_hal->delayMicroseconds(16663)) {
        result = make_error_code(pulse_driver_error::hal_clock);

    // W wave omitted successfully
    } else {
        result = make_error_code(pulse_driver_error::success);
    }

    return result;
}
