#ifndef SIGNAL_GENERATOR_HPP
#define SIGNAL_GENERATOR_HPP

#include <system_error>

class PulseDriver;

class SignalGenerator {
  public:
    SignalGenerator (PulseDriver * driver);
    std::error_code init (void * params);
    std::error_code signal (int sequence) const;
    std::error_code testSignal (void) const;

  private:
    PulseDriver * const _driver;
};

#endif // SIGNAL_GENERATOR_HPP
