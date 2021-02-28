#ifndef SIGNAL_GENERATOR_HPP
#define SIGNAL_GENERATOR_HPP

#include <system_error>

namespace nes { namespace rob {

class PulseDriver;

/**
 * \brief Generate signals for the R.O.B. protocol
 *
 * This class will generate the appropriate set of pulses and rests to generate
 * signals from the Nintendo Robotic Operating Buddy protocol.
 */
class SignalGenerator {
  public:
    /**
     * \brief <em> constructor </em>
     *
     * \param[in] driver A PulseDriver instance
     */
    SignalGenerator (PulseDriver * driver);

    /**
     * \brief Initialize the signal generator
     *
     * Performs necessary operations to initialize the signal generator.
     *
     * \param[in,out] reserved Supports driver specific initialization
     * parameters
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::signal_generator_error::success No errors encountered
     * during processing.
     * \retval nes::rob::signal_generator_error::driver_init A HAL error occured
     * during the pulse driver initialization.
     */
    std::error_code init (void * reserved = nullptr);

    /**
     * \brief Generate a protocol compatible signal
     *
     * Accepts an 8-bit binary array, and generates a corresponding signal.
     *
     * \param[in] sequence 8-bit binary sequence used to invoke R.O.B.
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::signal_generator_error::success No errors encountered
     * during processing.
     * \retval nes::rob::signal_generator_error::driver_error A driver error
     * occured during pulse driver invocation.
     */
    std::error_code signal (int sequence) const;

    /**
     * \brief Generate the R.O.B. test signal
     *
     * The test signal will disable R.O.B.'s LED if enabled. However, if
     * R.O.B.'s LED is disabled, then the LED will be enabled and then disabled.
     * When sent continuously, the LED will blink on a fixed interval.
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::signal_generator_error::success No errors encountered
     * during processing.
     * \retval nes::rob::signal_generator_error::driver_error A driver error
     * occured during pulse driver invocation.
     */
    std::error_code testSignal (void) const;

  private:
    PulseDriver * const _driver;
};

}} // namespace nes::rob

#endif // SIGNAL_GENERATOR_HPP
