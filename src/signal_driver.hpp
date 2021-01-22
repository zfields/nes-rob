#ifndef SIGNAL_DRIVER_HPP
#define SIGNAL_DRIVER_HPP

class SignalDriver {
  public:
    virtual ~SignalDriver (void) { };
    virtual int pulse (unsigned int active) const = 0;
};

#endif // SIGNAL_DRIVER_HPP
