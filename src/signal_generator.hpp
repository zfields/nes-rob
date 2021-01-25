#ifndef SIGNAL_GENERATOR_HPP
#define SIGNAL_GENERATOR_HPP

class SignalDriver;

class SignalGenerator {
  public:
    SignalGenerator (const SignalDriver * driver);
    int signal (int sequence) const;

  private:
    const SignalDriver * const _driver;
};

#endif // SIGNAL_GENERATOR_HPP
