#ifndef ARDUINO_DEBUG_DRIVER_HPP
#define ARDUINO_DEBUG_DRIVER_HPP

#include "pulse_driver.hpp"

namespace nes { namespace rob {

class ArduinoDebugDriver final : public PulseDriver {
  public:
    std::error_code init (void * params);
    std::error_code pulse (void * reserved = nullptr) const override;
    std::error_code rest (void * reserved = nullptr) const override;
};

}} // namespace nes::rob

#endif // ARDUINO_PRINT_DRIVER_HPP
