#ifndef PULSE_DRIVER_HPP
#define PULSE_DRIVER_HPP

class PulseDriver {
  public:
    enum class ErrorCode : int {
        SUCCESS,    // Executed as expected
        E_HAL_FAIL, // Internal HAL failure
    };
    virtual ~PulseDriver (void) { };
    virtual int init (void * params) = 0;
    virtual int pulse (unsigned int active) const = 0;
};

#endif // PULSE_DRIVER_HPP
