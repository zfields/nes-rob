#ifndef W_WAVE_DRIVER_HPP
#define W_WAVE_DRIVER_HPP

#include <system_error>

#include "pulse_driver.hpp"

class HardwareAbstractionLayer;

class WWaveDriver final : public PulseDriver {
  public:
    WWaveDriver (HardwareAbstractionLayer * hal, unsigned int pin);
    std::error_code init (void * params) override;
    std::error_code pulse (unsigned int active) const override;

  private:
    HardwareAbstractionLayer * const _hal;
    const unsigned int _pin;
};

#endif // W_WAVE_DRIVER_HPP