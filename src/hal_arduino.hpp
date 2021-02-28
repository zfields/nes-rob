#ifndef HAL_ARDUINO_HPP
#define HAL_ARDUINO_HPP

#include <system_error>

#include "hardware_abstraction_layer.hpp"

namespace nes { namespace rob {

/**
 * \brief The Arduino implementation of the hardware abstraction layer
 * interface
 *
 * The hardware abstraction layer abstracts Arduino specific behavior such as
 * GPIO peripherals, clock timing, and other configuration.
 */
class HalArduino final : public HardwareAbstractionLayer {
  public:
    std::error_code delayMicroseconds (unsigned int us) const override;
    std::error_code digitalWrite (unsigned int pin, int state) const override;
    std::error_code init (void * reserved = nullptr) override;
    std::error_code pinMode (unsigned int pin, int mode) const override;
};

}} // namespace nes::rob

#endif // HAL_ARDUINO_HPP
