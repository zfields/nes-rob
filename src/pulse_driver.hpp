#ifndef PULSE_DRIVER_HPP
#define PULSE_DRIVER_HPP

class PulseDriver {
  public:
    enum class ErrorCode {
        SUCCESS,    // Executed as expected
        E_HAL_FAIL, // Internal HAL failure
    };
    virtual ~PulseDriver (void) { };
    virtual ErrorCode init (void * params) = 0;
    virtual ErrorCode pulse (unsigned int active) const = 0;
};

#endif // PULSE_DRIVER_HPP
