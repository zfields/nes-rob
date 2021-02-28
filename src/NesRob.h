#ifndef NES_ROB_H
#define NES_ROB_H

#include <stdint.h>

namespace nes { namespace rob {

class PulseDriver;
class SignalGenerator;
class HardwareAbstractionLayer;

}} // namespace nes::rob

class NesRob {
  public:
    enum class Command : uint8_t {
        LEFT = 0xBA,
        RIGHT = 0xEA,
        DOWN = 0xAE,
        DOWN_2 = 0xFB,
        UP = 0xFA,
        UP_2 = 0xBB,
        CLOSE = 0xBE,
        OPEN = 0xEE,
        LED_DISABLE = 0xAA,
        LED_ENABLE = 0xEB,
        RECALIBRATE = 0xAB,
#if __cplusplus > 201103L
        CALIBRATE_MOTORS [[deprecated("Use RECALIBRATE instead.")]] = 0xAB,
        ARMS_LEFT [[deprecated("Use LEFT instead.")]] = 0xBA,
        ARMS_RIGHT [[deprecated("Use RIGHT instead.")]] = 0xEA,
        ARMS_LOWER [[deprecated("Use DOWN instead.")]] = 0xAE,
        ARMS_LOWER_2 [[deprecated("Use DOWN_2 instead.")]] = 0xFB,
        ARMS_RAISE [[deprecated("Use UP instead.")]] = 0xFA,
        ARMS_RAISE_2 [[deprecated("Use UP_2 instead.")]] = 0xBB,
        HANDS_CLOSE [[deprecated("Use CLOSE instead.")]] = 0xBE,
        HANDS_OPEN [[deprecated("Use OPEN instead.")]] = 0xEE,
        TEST_LED [[deprecated("Use LED_ENABLE instead.")]] = 0xEB,
#else
        CALIBRATE_MOTORS = 0xAB,
        ARMS_LEFT = 0xBA,
        ARMS_RIGHT = 0xEA,
        ARMS_LOWER = 0xAE,
        ARMS_LOWER_2 = 0xFB,
        ARMS_RAISE = 0xFA,
        ARMS_RAISE_2 = 0xBB,
        HANDS_CLOSE = 0xBE,
        HANDS_OPEN = 0xEE,
        TEST_LED = 0xEB,
#endif
    };

    enum class CommandTarget {
        PHOTOSENSOR,
        MAIN_CPU,
    };

    enum class ErrorCode : int {
        SUCCESS = 0, // Executed as expected
        E_SIGGEN,    // Signal generation error
    };

    NesRob (unsigned int pin, CommandTarget target = CommandTarget::PHOTOSENSOR);
    ~NesRob (void);

#if __cplusplus > 201103L
    [[deprecated("Use sendCommand() instead.")]]
#endif
    void blinkCommand(Command command) const;

    int sendCommand(Command command) const;

  private:
    nes::rob::HardwareAbstractionLayer * const _hal;
    nes::rob::PulseDriver * const _pulse_driver;
    nes::rob::SignalGenerator * const _signal_generator;
};

#endif // NES_ROB_H
