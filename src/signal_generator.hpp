#ifndef SIGNAL_GENERATOR_HPP
#define SIGNAL_GENERATOR_HPP

class PulseDriver;

class SignalGenerator {
  public:
    enum class ErrorCode : int {
        SUCCESS,  // Executed as expected
        E_DRIVER, // Driver Error
    };

    SignalGenerator (PulseDriver * driver);
    int init (void * params);
    int signal (int sequence) const;
    int testSignal (void) const;

  private:
    PulseDriver * const _driver;
};

#endif // SIGNAL_GENERATOR_HPP
