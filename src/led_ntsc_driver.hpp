#ifndef LED_NTSC_DRIVER_HPP
#define LED_NTSC_DRIVER_HPP

#include <system_error>

#include "pulse_driver.hpp"

namespace nes { namespace rob {

class HardwareAbstractionLayer;

class LedNtscDriver final : public PulseDriver {
  public:
    LedNtscDriver (HardwareAbstractionLayer * hal, unsigned int pin);
    std::error_code init (void * params) override;
    std::error_code pulse (void * reserved = nullptr) const override;
    std::error_code rest (void * reserved = nullptr) const override;

  private:
    HardwareAbstractionLayer * const _hal;
    const unsigned int _pin;
};

}} // namespace nes::rob

#endif // LED_NTSC_DRIVER_HPP
