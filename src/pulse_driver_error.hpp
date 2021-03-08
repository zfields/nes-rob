#ifndef PULSE_DRIVER_ERROR_HPP
#define PULSE_DRIVER_ERROR_HPP

#ifndef __AVR__
  #include <system_error>
  #include <type_traits>
#endif

namespace nes { namespace rob {

/**
 * \brief Pulse Driver Errors
 */
enum class pulse_driver_error
{
    success = 0,        /**< Success. */
    hal_clock,          /**< HAL clock error occurred. */
    hal_gpio_config,    /**< HAL GPIO peripheral configuration error occurred. */
    hal_gpio_state,     /**< HAL failed to update the GPIO state. */
    hal_init            /**< Failed to initialize HAL interface. */
};

#ifndef __AVR__

typedef std::error_code error_code;
std::error_condition make_error_condition(pulse_driver_error e);

#else // __AVR__

typedef int error_code;

#endif // not __AVR__

error_code make_error_code(pulse_driver_error e);

}} // namespace nes::rob

#ifndef __AVR__

namespace std {

template <>
struct is_error_code_enum<nes::rob::pulse_driver_error> : true_type {};

}

#endif // not __AVR__

#endif // PULSE_DRIVER_ERROR_HPP
