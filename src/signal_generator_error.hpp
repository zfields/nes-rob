#ifndef SIGNAL_GENERATOR_ERROR_HPP
#define SIGNAL_GENERATOR_ERROR_HPP

#include <system_error>

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

std::error_code make_error_code(signal_generator_error e);
std::error_condition make_error_condition(signal_generator_error e);

}} // namespace nes::rob

namespace std {

template <>
struct is_error_code_enum<nes::rob::signal_generator_error> : true_type {};

}

#endif // SIGNAL_GENERATOR_ERROR_HPP
