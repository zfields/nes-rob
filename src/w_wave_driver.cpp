#include "w_wave_driver.hpp"

#include "hardware_abstraction_layer.hpp"

WWaveDriver::WWaveDriver (
    HardwareAbstractionLayer * hal_,
    unsigned int pin_
) :
    _hal(hal_),
    _pin(pin_)
{ }

int
WWaveDriver::init (
    void * params_
) {
    ErrorCode result;

    (void)params_;  // ignore parameters

    // Configure the HAL
    if (_hal->init(nullptr)) {
        result = ErrorCode::E_HAL_INIT;
    } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_INPUT)) {
        result = ErrorCode::E_HAL_GPIO_CFG;
    } else {
        result = ErrorCode::SUCCESS;
    }

    return static_cast<int>(result);
}

int
WWaveDriver::pulse (
    unsigned int active_
) const {
    ErrorCode result;

    if (active_) {
        // Sink current for 800us (~4us of MCU instructions)
        if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_OUTPUT)) {
            result = ErrorCode::E_HAL_GPIO;
        } else if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
            result = ErrorCode::E_HAL_GPIO;
        } else if (_hal->delayMicroseconds(796)) {
            result = ErrorCode::E_HAL_CLOCK;

        // High-Z for 733us (~3us of MCU instructions)
        } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_INPUT)) {
            result = ErrorCode::E_HAL_GPIO;
        } else if (_hal->delayMicroseconds(730)) {
            result = ErrorCode::E_HAL_CLOCK;


        // Sink current for 800us (~4us of MCU instructions)
        } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_OUTPUT)) {
            result = ErrorCode::E_HAL_GPIO;
        } else if (_hal->digitalWrite(_pin, HardwareAbstractionLayer::PIN_STATE_LOW)) {
            result = ErrorCode::E_HAL_GPIO;
        } else if (_hal->delayMicroseconds(796)) {
            result = ErrorCode::E_HAL_CLOCK;

        // High-Z for remaining time slice (~3us of MCU instructions)
        } else if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_INPUT)) {
            result = ErrorCode::E_HAL_GPIO;
        } else if (_hal->delayMicroseconds(14330)) {
            result = ErrorCode::E_HAL_CLOCK;

        // W wave generated successfully
        } else {
            result = ErrorCode::SUCCESS;
        }
    } else {
        // High-Z for time slice (~3us of MCU instructions)
        if (_hal->pinMode(_pin, HardwareAbstractionLayer::PIN_MODE_INPUT)) {
            result = ErrorCode::E_HAL_GPIO;
        } else if (_hal->delayMicroseconds(16663)) {
            result = ErrorCode::E_HAL_CLOCK;

        // W wave omitted successfully
        } else {
            result = ErrorCode::SUCCESS;
        }
    }

    return static_cast<int>(result);
}
