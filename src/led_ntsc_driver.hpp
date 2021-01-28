#ifndef LED_NTSC_DRIVER_HPP
#define LED_NTSC_DRIVER_HPP

#include "pulse_driver.hpp"

class HalClock;
class HalGpio;

class LedNtscDriver final : public PulseDriver {
  public:
  LedNtscDriver (const HalClock * clock, const HalGpio * gpio, unsigned int pin);
  ErrorCode init (void * params) override;
  ErrorCode pulse (unsigned int active) const override;

  private:
  const HalClock * const _clock;
  const HalGpio * const _gpio;
  const unsigned int _pin;
};

#endif // LED_NTSC_DRIVER_HPP