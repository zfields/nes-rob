#ifndef HAL_ERROR_HPP
#define HAL_ERROR_HPP

#include <system_error>

namespace nes { namespace rob {

enum class hal_error
{
    success = 0,
    peripheral_gpio,
    sys_clock,
    sys_config,
};

std::error_code make_error_code(hal_error e);
std::error_condition make_error_condition(hal_error e);

}} // namespace nes::rob

namespace std {

template <>
struct is_error_code_enum<nes::rob::hal_error> : true_type {};

}

#endif // HAL_ERROR_HPP
