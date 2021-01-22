#ifndef LED_NTSC_DRIVER_HPP
#define LED_NTSC_DRIVER_HPP

#include "signal_driver.hpp"

class HalClock;
class HalGpio;

class LedNtscDriver final : public SignalDriver {
  public:
  LedNtscDriver (const HalClock * clock, const HalGpio * gpio, unsigned int pin);
  int pulse (unsigned int active_) const override;

  private:
  const HalClock * const _clock;
  const HalGpio * const _gpio;
  const unsigned int _pin;
};

#endif // LED_NTSC_DRIVER_HPP