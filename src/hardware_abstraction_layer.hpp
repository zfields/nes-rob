#ifndef HARDWARE_ABSTRACTION_LAYER_HPP
#define HARDWARE_ABSTRACTION_LAYER_HPP

class HardwareAbstractionLayer {
  public:
    enum class ErrorCode : int {
        SUCCESS,    // Executed as expected
        E_HARDWARE, // Hardware Error
    };

    // Implementation specific inputs to the interface
    // Values must be defined in the concrete implementation
    static const int PIN_STATE_HIGH;
    static const int PIN_MODE_INPUT;
    static const int PIN_MODE_INPUT_PULLUP;
    static const int PIN_STATE_LOW;
    static const int PIN_MODE_OUTPUT;

    virtual ~HardwareAbstractionLayer (void) { }
    virtual int init (void * params) = 0;
    virtual int delayMicroseconds (unsigned int pin) const = 0;
    virtual int digitalWrite (unsigned int pin, int state) const = 0;
    virtual int pinMode (unsigned int pin, int mode) const = 0;
};

#endif // HARDWARE_ABSTRACTION_LAYER_HPP
