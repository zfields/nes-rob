#ifndef LED_NTSC_DRIVER_HPP
#define LED_NTSC_DRIVER_HPP

#include "pulse_driver.hpp"

class HardwareAbstractionLayer;

class LedNtscDriver final : public PulseDriver {
  public:
  LedNtscDriver (HardwareAbstractionLayer * hal, unsigned int pin);
  int init (void * params) override;
  int pulse (unsigned int active) const override;

  private:
  HardwareAbstractionLayer * const _hal;
  const unsigned int _pin;
};

#endif // LED_NTSC_DRIVER_HPP