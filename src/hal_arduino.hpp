#ifndef HAL_ARDUINO_HPP
#define HAL_ARDUINO_HPP

#include <system_error>

#include "hardware_abstraction_layer.hpp"

class HalArduino final : public HardwareAbstractionLayer {
  public:
    std::error_code delayMicroseconds (unsigned int pin) const override;
    std::error_code digitalWrite (unsigned int pin, int state) const override;
    std::error_code init (void * params) override;
    std::error_code pinMode (unsigned int pin, int mode) const override;
};

#endif // HAL_ARDUINO_HPP
