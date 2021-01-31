#ifndef PULSE_DRIVER_HPP
#define PULSE_DRIVER_HPP

class PulseDriver {
  public:
    enum class ErrorCode : int {
        SUCCESS,        // Executed as expected
        E_HAL_INIT,     // Failed to initialize HAL
        E_HAL_CLOCK,    // HAL clock failure
        E_HAL_GPIO,     // HAL GPIO failure
        E_HAL_GPIO_CFG, // HAL GPIO configuration error
    };
    virtual ~PulseDriver (void) { };
    virtual int init (void * params) = 0;
    virtual int pulse (unsigned int active) const = 0;
};

#endif // PULSE_DRIVER_HPP
