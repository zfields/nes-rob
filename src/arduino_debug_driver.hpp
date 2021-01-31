#ifndef ARDUINO_DEBUG_DRIVER_HPP
#define ARDUINO_DEBUG_DRIVER_HPP

#include "pulse_driver.hpp"

class ArduinoDebugDriver final : public PulseDriver {
  public:
  int init (void * params);
  int pulse (unsigned int active) const override;
};

#endif // ARDUINO_PRINT_DRIVER_HPP