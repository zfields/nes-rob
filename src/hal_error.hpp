#ifndef HAL_ERROR_HPP
#define HAL_ERROR_HPP

#include <system_error>

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

std::error_code make_error_code(hal_error e);
std::error_condition make_error_condition(hal_error e);

}} // namespace nes::rob

namespace std {

template <>
struct is_error_code_enum<nes::rob::hal_error> : true_type {};

}

#endif // HAL_ERROR_HPP
