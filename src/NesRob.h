#ifndef NES_ROB_H
#define NES_ROB_H

#include <cstdint>

class PulseDriver;
class SignalGenerator;
class HardwareAbstractionLayer;

class NesRob {
  public:
  enum class ErrorCode : int {
      SUCCESS = 0, // Executed as expected
      E_SIGGEN,    // Signal generation error
  };

  enum class Command : uint8_t {
    CALIBRATE_MOTORS = 0xAB,
    TEST_LED = 0xEB,
    ARMS_LEFT = 0xBA,
    ARMS_RIGHT = 0xEA,
    ARMS_LOWER = 0xAE,
    ARMS_LOWER_2 = 0xFB,
    ARMS_RAISE = 0xFA,
    ARMS_RAISE_2 = 0xBB,
    ARMS_CLOSE = 0xBE,
    ARMS_OPEN = 0xEE,
#if __cplusplus > 201103L
    HANDS_CLOSE [[deprecated("Use ARMS_CLOSE instead.")]] = 0xBE,
    HANDS_OPEN [[deprecated("Use ARMS_OPEN instead.")]] = 0xEE,
#else
    HANDS_CLOSE = 0xBE,
    HANDS_OPEN = 0xEE,
#endif
  };

  NesRob (
    unsigned int _pin
  );

  ~NesRob (
    void
  );

#if __cplusplus > 201103L
  [[deprecated("Use sendCommand() instead.")]]
#endif
  void
  blinkCommand(
    Command command
  ) const;

  int
  sendCommand(
    Command command
  ) const;

  private:
  HardwareAbstractionLayer * const _hal;
  PulseDriver * const _pulse_driver;
  SignalGenerator * const _signal_generator;
};

#endif // NES_ROB_H
