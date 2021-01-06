#ifndef NES_ROB_H
#define NES_ROB_H

#include <cstdint>

class NesRob {
  public:
  enum class Command : uint8_t {
    CALIBRATE_MOTORS = 0xAB,
    TEST_LED = 0xEB,
    ARMS_LEFT = 0xBA,
    ARMS_RIGHT = 0xEA,
    ARMS_LOWER = 0xFB,
    ARMS_LOWER_2 = 0xAE,
    ARMS_RAISE = 0xFA,
    ARMS_RAISE_2 = 0xBB,
    HANDS_CLOSE = 0xBE,
    HANDS_OPEN = 0xEE,
  };

  NesRob (
    unsigned int led_pin
  );

  void
  blinkCommand(
    Command command
  );

  private:
  const unsigned int _led_pin;
};

#endif // NES_ROB_H
