#ifndef ARDUINO_DEBUG_DRIVER_HPP
#define ARDUINO_DEBUG_DRIVER_HPP

#include "signal_driver.hpp"

class ArduinoDebugDriver final : public SignalDriver {
  public:
  ArduinoDebugDriver (void);
  int pulse (unsigned int active) const override;
};

#endif // ARDUINO_PRINT_DRIVER_HPP