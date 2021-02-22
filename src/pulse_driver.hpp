#ifndef PULSE_DRIVER_HPP
#define PULSE_DRIVER_HPP

#include <system_error>

class PulseDriver {
  public:
    virtual ~PulseDriver (void) { };
    virtual std::error_code init (void * params) = 0;
    virtual std::error_code pulse (unsigned int active) const = 0;
};

#endif // PULSE_DRIVER_HPP
