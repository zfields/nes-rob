#ifndef NES_ROB_H
#define NES_ROB_H

#include <stdint.h>

namespace nes { namespace rob {

class PulseDriver;
class SignalGenerator;
class HardwareAbstractionLayer;

}} // namespace nes::rob

/**
 * \brief Nintendo R.O.B. Control Library
 *
 * The library defines and generates all known R.O.B. commands.
 */
class NesRob {
  public:
    /**
     * \brief Available R.O.B. Commands
     */
    enum class Command : uint8_t {
        LEFT = 0xBA,        /**< Rotate R.O.B.'s torso left one station. */
        RIGHT = 0xEA,       /**< Rotate R.O.B.'s torso right one station. */
        DOWN = 0xAE,        /**< Lower R.O.B.'s shoulders one notch. */
        DOWN_2 = 0xFB,      /**< Lower R.O.B.'s shoulders two notches. */
        UP = 0xFA,          /**< Raise R.O.B.'s shoulders one notch. */
        UP_2 = 0xBB,        /**< Raise R.O.B.'s shoulders two notches. */
        CLOSE = 0xBE,       /**< Close R.O.B.'s arms. */
        OPEN = 0xEE,        /**< Open R.O.B.'s arms. */
        LED_DISABLE = 0xAA, /**< Disable R.O.B.'s LED. */
        LED_ENABLE = 0xEB,  /**< Enable R.O.B.'s LED. */
        RECALIBRATE = 0xAB, /**< Reruns the start-up calibration routine. */
#if __cplusplus > 201103L
        CALIBRATE_MOTORS [[deprecated("Use RECALIBRATE instead.")]] = 0xAB, /**< \deprecated Use RECALIBRATE instead. */
        ARMS_LEFT [[deprecated("Use LEFT instead.")]] = 0xBA,               /**< \deprecated Use LEFT instead. */
        ARMS_RIGHT [[deprecated("Use RIGHT instead.")]] = 0xEA,             /**< \deprecated Use RIGHT instead. */
        ARMS_LOWER [[deprecated("Use DOWN instead.")]] = 0xAE,              /**< \deprecated Use DOWN instead. */
        ARMS_LOWER_2 [[deprecated("Use DOWN_2 instead.")]] = 0xFB,          /**< \deprecated Use DOWN_2 instead. */
        ARMS_RAISE [[deprecated("Use UP instead.")]] = 0xFA,                /**< \deprecated Use UP instead. */
        ARMS_RAISE_2 [[deprecated("Use UP_2 instead.")]] = 0xBB,            /**< \deprecated Use UP_2 instead. */
        HANDS_CLOSE [[deprecated("Use CLOSE instead.")]] = 0xBE,            /**< \deprecated Use CLOSE instead. */
        HANDS_OPEN [[deprecated("Use OPEN instead.")]] = 0xEE,              /**< \deprecated Use OPEN instead. */
        TEST_LED [[deprecated("Use LED_ENABLE instead.")]] = 0xEB,          /**< \deprecated Use LED_ENABLE instead. */
#else
        CALIBRATE_MOTORS = 0xAB,    /**< \deprecated Use RECALIBRATE instead. */
        ARMS_LEFT = 0xBA,           /**< \deprecated Use LEFT instead. */
        ARMS_RIGHT = 0xEA,          /**< \deprecated Use RIGHT instead. */
        ARMS_LOWER = 0xAE,          /**< \deprecated Use DOWN instead. */
        ARMS_LOWER_2 = 0xFB,        /**< \deprecated Use DOWN_2 instead. */
        ARMS_RAISE = 0xFA,          /**< \deprecated Use UP instead. */
        ARMS_RAISE_2 = 0xBB,        /**< \deprecated Use UP_2 instead. */
        HANDS_CLOSE = 0xBE,         /**< \deprecated Use CLOSE instead. */
        HANDS_OPEN = 0xEE,          /**< \deprecated Use OPEN instead. */
        TEST_LED = 0xEB,            /**< \deprecated Use LED_ENABLE instead. */
#endif
    };

    /**
     * \brief Valid targets for commands
     *
     * \note The `MAIN_CPU` target requires hardware modification to utilize.
     * The signal should be injected inline with the ribbon cable, running down
     * R.O.B.'s neck from his head to the base.
     *
     * \see NesRob::Command
     */
    enum class CommandTarget {
        PHOTOSENSOR,    /**< Generates NTSC signal for the optical sensor in the left eye. */
        MAIN_CPU,       /**< Generates the W square wave for the main CPU on R.O.B.'s motherboard. */
    };

    /**
     * \brief Error codes
     */
    enum class ErrorCode : int {
        SUCCESS = 0,    /**< No errors encountered during execution. */
        E_SIGGEN,       /**< An unspecified error occured during signal generation. */
    };

    /**
     * \brief Allocate required resources
     *
     * \param[in] pin The digital GPIO used to send commands
     * \param[in] target The target of the commands <em> Default:
     * \c NesRob::CommandTarget::PHOTOSENSOR </em>
     * \par
     * - \c NesRob::CommandTarget::PHOTOSENSOR
     * - \c NesRob::CommandTarget::MAIN_CPU
     *
     * \see NesRob::CommandTarget
     */
    NesRob (unsigned int pin, CommandTarget target = CommandTarget::PHOTOSENSOR);

    /**
     * \brief Destroy allocated resources
     */
    ~NesRob (void);

    /**
     * \brief Blink command to R.O.B.
     *
     * \deprecated Use NesRob::sendCommand instead.
     *
     * \param[in] command The command you wish R.O.B. to perform
     * \par
     * - \c NesRob::Command::LEFT
     * - \c NesRob::Command::RIGHT
     * - \c NesRob::Command::DOWN
     * - \c NesRob::Command::DOWN_2
     * - \c NesRob::Command::UP
     * - \c NesRob::Command::UP_2
     * - \c NesRob::Command::OPEN
     * - \c NesRob::Command::CLOSE
     * - \c NesRob::Command::LED_DISABLE
     * - \c NesRob::Command::LED_ENABLE
     * - \c NesRob::Command::RECALIBRATE
     *
     * \see NesRob::Command
     * \see NesRob::sendCommand
     */
#if __cplusplus > 201103L
    [[deprecated("Use sendCommand() instead.")]]
#endif
    void blinkCommand(Command command) const;

    /**
     * \brief Send command to R.O.B.
     *
     * \param[in] command The command you wish R.O.B. to perform
     * \par
     * - \c NesRob::Command::LEFT
     * - \c NesRob::Command::RIGHT
     * - \c NesRob::Command::DOWN
     * - \c NesRob::Command::DOWN_2
     * - \c NesRob::Command::UP
     * - \c NesRob::Command::UP_2
     * - \c NesRob::Command::OPEN
     * - \c NesRob::Command::CLOSE
     * - \c NesRob::Command::LED_DISABLE
     * - \c NesRob::Command::LED_ENABLE
     * - \c NesRob::Command::RECALIBRATE
     *
     * \returns \c int An error code describing errors encountered during
     * processing
     * \retval NesRob::SUCCESS No errors encountered during processing.
     * \retval NesRob::E_SIGGEN An unspecified error occured during signal
     * generation.
     *
     * \see NesRob::Command
     */
    int sendCommand(Command command) const;

  private:
    nes::rob::HardwareAbstractionLayer * const _hal;
    nes::rob::PulseDriver * const _pulse_driver;
    nes::rob::SignalGenerator * const _signal_generator;
};

#endif // NES_ROB_H
