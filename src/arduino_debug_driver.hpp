#ifndef ARDUINO_DEBUG_DRIVER_HPP
#define ARDUINO_DEBUG_DRIVER_HPP

#include "pulse_driver.hpp"

namespace nes { namespace rob {

/**
 * \brief The debugging implementation of the pulse driver interface
 *
 * This class is intended to be a debugging tool. It is designed for logging the
 * pulse behavior requested by the SignalGenerator class.
 *
 * \note This implementation has a dependency on the Arduino SDK.
 */
class ArduinoDebugDriver final : public PulseDriver {
  public:
    std::error_code init (void * reserved = nullptr) override;
    std::error_code pulse (void * reserved = nullptr) const override;
    std::error_code rest (void * reserved = nullptr) const override;
};

}} // namespace nes::rob

#endif // ARDUINO_PRINT_DRIVER_HPP
