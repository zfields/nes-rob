#ifndef PULSE_DRIVER_HPP
#define PULSE_DRIVER_HPP

#include <system_error>

namespace nes { namespace rob {

/**
 * \brief The pulse driver interface
 *
 * A pulse driver is responsible for generating protocol signals to be
 * interpreted by the Nintendo R.O.B.
 */
class PulseDriver {
  public:
    virtual ~PulseDriver (void) { };

    /**
     * \brief Initialize the pulse driver
     *
     * Performs necessary operations to initialize the pulse driver
     * implementation.
     *
     * \param[in,out] reserved Supports driver specific initialization
     * parameters
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::pulse_driver_error::success No errors encountered
     * during processing.
     * \retval nes::rob::pulse_driver_error::hal_init A HAL error occured during
     * the pulse driver initialization.
     */
    virtual std::error_code init (void * reserved = nullptr) = 0;

    /**
     * \brief Generate a protocol specific pulse
     *
     * Performs necessary GPIO operations to generate a protocol compatible
     * pulse.
     *
     * \param[in,out] reserved Supports driver specific implementation
     * parameters
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::pulse_driver_error::success No errors encountered
     * during processing.
     * \retval nes::rob::pulse_driver_error::hal_clock A clock error occured
     * during pulse generation.
     * \retval nes::rob::pulse_driver_error::hal_gpio_config Unable to configure
     * GPIO peripheral for pulse generation.
     * \retval nes::rob::pulse_driver_error::hal_gpio_state Unable to set GPIO
     * state during pulse generation.
     */
    virtual std::error_code pulse (void * reserved = nullptr) const = 0;

    /**
     * \brief Generate a protocol specified rest period
     *
     * Places GPIO in resting state and awaits a period defined by the protocol.
     *
     * \param[in,out] reserved Supports driver specific implementation
     * parameters
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::pulse_driver_error::success No errors encountered
     * during processing.
     * \retval nes::rob::pulse_driver_error::hal_clock A clock error occured
     * while observing rest period.
     * \retval nes::rob::pulse_driver_error::hal_gpio_config Unable to configure
     * GPIO peripheral for resting state.
     * \retval nes::rob::pulse_driver_error::hal_gpio_state Unable to set GPIO
     * pin in resting state.
     */
    virtual std::error_code rest (void * reserved = nullptr) const = 0;
};

}} // namespace nes::rob

#endif // PULSE_DRIVER_HPP
