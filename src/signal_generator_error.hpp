#include <system_error>

namespace nes { namespace rob {

enum class signal_generator_error
{
    success = 0,
    driver_error,
    driver_init
};

std::error_code make_error_code(signal_generator_error e);
std::error_condition make_error_condition(signal_generator_error e);

}} // namespace nes::rob

namespace std {

template <>
struct is_error_code_enum<nes::rob::signal_generator_error> : true_type {};

}
