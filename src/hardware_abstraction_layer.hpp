#ifndef HARDWARE_ABSTRACTION_LAYER_HPP
#define HARDWARE_ABSTRACTION_LAYER_HPP

#include <system_error>

namespace nes { namespace rob {

/**
 * \brief The hardware abstraction layer interface
 *
 * The hardware abstraction layer abstracts hardware specific behavior such as
 * GPIO peripherals, clock timing, and other configuration.
 */
class HardwareAbstractionLayer {
  public:
    // Implementation specific inputs to the interface
    // Values must be defined in the concrete implementation

    /**
     * \brief The GPIO mode used to sample digital signals
     */
    static const int PIN_MODE_INPUT;

    /**
     * \brief The GPIO mode used to sample digital signals with internal pullup
     * resistor enabled
     */
    static const int PIN_MODE_INPUT_PULLUP;

    /**
     * \brief The GPIO mode used to write digital signals
     */
    static const int PIN_MODE_OUTPUT;

    /**
     * \brief The digital signal value indicating high voltage <em> (typically
     * Vcc) </em>
     */
    static const int PIN_STATE_HIGH;

    /**
     * \brief The digital signal value indicating low voltage <em> (typically
     * Vdd) </em>
     */
    static const int PIN_STATE_LOW;

    virtual ~HardwareAbstractionLayer (void) { }

    /**
     * \brief Initialize the HAL
     *
     * Performs necessary operations to initialize the hardware abstraction
     * layer implementation.
     *
     * \param[in,out] reserved Supports hardware specific initialization
     * parameters
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::hal_error::success No errors encountered during
     * processing.
     * \retval nes::rob::hal_error::sys_config An unspecified error occured
     * during system configuration.
     */
    virtual std::error_code init (void * reserved = nullptr) = 0;

    /**
     * \brief Delay program execution for the specified number of microseconds
     *
     * \param[in] us The number of microseconds to delay
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::hal_error::success No errors encountered during
     * processing.
     * \retval nes::rob::hal_error::sys_clock An unspecified error occured
     * while interacting with the system clock.
     */
    virtual std::error_code delayMicroseconds (unsigned int us) const = 0;

    /**
     * \brief Drive the output voltage of a digital GPIO pin.
     *
     * \param[in] pin The pin number associated to the target GPIO pin
     * \param[in] state The desired state of the pin
     * \par
     * - \c PIN_STATE_HIGH
     * - \c PIN_STATE_LOW
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::hal_error::success No errors encountered during
     * processing.
     * \retval nes::rob::hal_error::peripheral_gpio An unspecified error occured
     * while interacting with the GPIO peripheral.
     *
     * \see nes::rob::HardwareAbstractionLayer::PIN_STATE_HIGH
     * \see nes::rob::HardwareAbstractionLayer::PIN_STATE_LOW
     * \see nes::rob::HardwareAbstractionLayer::pinMode
     */
    virtual std::error_code digitalWrite (unsigned int pin, int state) const = 0;

    /**
     * \brief Drive the output voltage of a digital GPIO pin.
     *
     * \param[in] pin The pin number associated to the target GPIO pin
     * \param[in] mode The desired mode of operation for the pin
     * \par
     * - \c PIN_MODE_INPUT
     * - \c PIN_MODE_INPUT_PULLUP
     * - \c PIN_MODE_OUTPUT
     *
     * \returns \c std::error code describing errors encountered during
     * processing
     * \retval nes::rob::hal_error::success No errors encountered during
     * processing.
     * \retval nes::rob::hal_error::peripheral_gpio An unspecified error occured
     * while interacting with the GPIO peripheral.
     *
     * \see nes::rob::HardwareAbstractionLayer::PIN_MODE_INPUT
     * \see nes::rob::HardwareAbstractionLayer::PIN_MODE_INPUT_PULLUP
     * \see nes::rob::HardwareAbstractionLayer::PIN_MODE_OUTPUT
     * \see nes::rob::HardwareAbstractionLayer::digitalWrite
     */
    virtual std::error_code pinMode (unsigned int pin, int mode) const = 0;
};

}} // namespace nes::rob

#endif // HARDWARE_ABSTRACTION_LAYER_HPP
