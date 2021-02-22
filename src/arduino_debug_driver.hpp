#ifndef ARDUINO_DEBUG_DRIVER_HPP
#define ARDUINO_DEBUG_DRIVER_HPP

#include "pulse_driver.hpp"

class ArduinoDebugDriver final : public PulseDriver {
  public:
    std::error_code init (void * params);
    std::error_code pulse (unsigned int active) const override;
};

#endif // ARDUINO_PRINT_DRIVER_HPP
