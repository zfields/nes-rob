#ifndef SIGNAL_GENERATOR_ERROR_HPP
#define SIGNAL_GENERATOR_ERROR_HPP

#ifndef __AVR__
  #include <system_error>
  #include <type_traits>
#endif

namespace nes { namespace rob {

/**
 * \brief Signal Generator Errors
 */
enum class signal_generator_error
{
    success = 0,    /**< Success. */
    driver_error,   /**< Pulse driver error occurred. */
    driver_init     /**< Failed to initialize pulse driver. */
};

#ifndef __AVR__

typedef std::error_code error_code;
std::error_condition make_error_condition(signal_generator_error e);

#else // __AVR__

typedef int error_code;

#endif // not __AVR__

error_code make_error_code(signal_generator_error e);

}} // namespace nes::rob

#ifndef __AVR__

namespace std {

template <>
struct is_error_code_enum<nes::rob::signal_generator_error> : true_type {};

}

#endif // not __AVR__

#endif // SIGNAL_GENERATOR_ERROR_HPP
