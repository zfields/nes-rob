#ifndef HARDWARE_ABSTRACTION_LAYER_HPP
#define HARDWARE_ABSTRACTION_LAYER_HPP

#include <system_error>

namespace nes { namespace rob {

class HardwareAbstractionLayer {
  public:
    // Implementation specific inputs to the interface
    // Values must be defined in the concrete implementation
    static const int PIN_STATE_HIGH;
    static const int PIN_MODE_INPUT;
    static const int PIN_MODE_INPUT_PULLUP;
    static const int PIN_STATE_LOW;
    static const int PIN_MODE_OUTPUT;

    virtual ~HardwareAbstractionLayer (void) { }
    virtual std::error_code init (void * params) = 0;
    virtual std::error_code delayMicroseconds (unsigned int pin) const = 0;
    virtual std::error_code digitalWrite (unsigned int pin, int state) const = 0;
    virtual std::error_code pinMode (unsigned int pin, int mode) const = 0;
};

}} // namespace nes::rob

#endif // HARDWARE_ABSTRACTION_LAYER_HPP
