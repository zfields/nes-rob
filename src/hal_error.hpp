#ifndef HAL_ERROR_HPP
#define HAL_ERROR_HPP

#ifndef __AVR__
  #include <system_error>
  #include <type_traits>
#endif

namespace nes { namespace rob {

/**
 * \brief Hardware Abstraction Layer Errors
 */
enum class hal_error
{
    success = 0,        /**< Success. */
    peripheral_gpio,    /**< GPIO peripheral error. */
    sys_clock,          /**< System clock error. */
    sys_config,         /**< Failed to properly configure hardware. */
};

#ifndef __AVR__

typedef std::error_code error_code;
std::error_condition make_error_condition(hal_error e);

#else // __AVR__

typedef int error_code;

#endif // not __AVR__

error_code make_error_code(hal_error e);

}} // namespace nes::rob

#ifndef __AVR__

namespace std {

template <>
struct is_error_code_enum<nes::rob::hal_error> : true_type {};

}

#endif // not __AVR__

#endif // HAL_ERROR_HPP
