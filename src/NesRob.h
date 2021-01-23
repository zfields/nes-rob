#ifndef NES_ROB_H
#define NES_ROB_H

#include <cstdint>

class SignalDriver;
class SignalGenerator;
class HalClock;
class HalGpio;

class NesRob {
  public:
  enum class Command : uint8_t {
    CALIBRATE_MOTORS = 0xAB,
    TEST_LED = 0xEB,
    ARMS_LEFT = 0xBA,
    ARMS_RIGHT = 0xEA,
    ARMS_LOWER = 0xAE,
    ARMS_LOWER_2 = 0xFB,
    ARMS_RAISE = 0xFA,
    ARMS_RAISE_2 = 0xBB,
    HANDS_CLOSE = 0xBE,
    HANDS_OPEN = 0xEE,
  };

  NesRob (
    unsigned int _pin
  );

  ~NesRob (
    void
  );

  [[deprecated("Use sendCommand() instead.")]]
  void
  blinkCommand(
    Command command
  );

  int
  sendCommand(
    Command command
  );

  private:
  const HalClock * const _hal_clock;
  const HalGpio * const _hal_gpio;
  const SignalDriver * const _sig_drv;
  const SignalGenerator * const _sig_gen;
};

#endif // NES_ROB_H
