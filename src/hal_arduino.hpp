#ifndef HAL_ARDUINO_HPP
#define HAL_ARDUINO_HPP

#include "hardware_abstraction_layer.hpp"
class HalArduino final : public HardwareAbstractionLayer {
  public:
    int delayMicroseconds (unsigned int pin) const override;
    int digitalWrite (unsigned int pin, int state) const override;
    int init (void * params) override;
    int pinMode (unsigned int pin, int mode) const override;
};

#endif // HAL_ARDUINO_HPP
