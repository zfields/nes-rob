#ifndef LED_NTSC_DRIVER_HPP
#define LED_NTSC_DRIVER_HPP

#include "pulse_driver.hpp"

namespace nes { namespace rob {

class HardwareAbstractionLayer;

/**
 * \brief The LED NTSC implementation of the pulse driver interface
 *
 * This implementation requires an LED light to be attached to the digital GPIO
 * pin. The pulses emitted adhere to the NTSC protocol, which is required to
 * communicate with R.O.B.
 */
class LedNtscDriver final : public PulseDriver {
  public:
    /**
     * \brief <em> constructor </em>
     *
     * \param[in] hal A HardwareAbstractionLayer instance
     * \param[in] pin The digital GPIO pin used to generate pulses
     */
    LedNtscDriver (HardwareAbstractionLayer * hal, unsigned int pin);
    nes::rob::error_code init (void * reserved = nullptr) override;
    nes::rob::error_code pulse (void * reserved = nullptr) const override;
    nes::rob::error_code rest (void * reserved = nullptr) const override;

  private:
    HardwareAbstractionLayer * const _hal;
    const unsigned int _pin;
};

}} // namespace nes::rob

#endif // LED_NTSC_DRIVER_HPP
