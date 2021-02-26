#include "pulse_driver_error.hpp"

namespace nes { namespace rob {

class pulse_driver_category_impl : public std::error_category
{
  public:
    virtual std::error_condition default_error_condition (int ev) const noexcept override;
    virtual std::string message(int ev) const override;
    virtual const char *name(void) const noexcept override;
};

}} // namespace nes::rob

using namespace nes::rob;

namespace {

const std::error_category &
pulse_driver_category (
    void
) {
    static pulse_driver_category_impl instance;
    return instance;
}

}

std::error_condition
pulse_driver_category_impl::default_error_condition (
    int ev
) const noexcept {
    // Define equivalence relationships with std::errc
    switch (static_cast<pulse_driver_error>(ev)) {
      default:
        return std::error_condition(ev, *this);
    };
}

std::string
pulse_driver_category_impl::message (
    int ev
) const {
    switch (static_cast<pulse_driver_error>(ev)) {
      case pulse_driver_error::success:
        return "Success.";
      case pulse_driver_error::hal_clock:
        return "HAL clock failure.";
      case pulse_driver_error::hal_gpio_config:
        return "Failed to update HAL GPIO configuration.";
      case pulse_driver_error::hal_gpio_state:
        return "Failed to update HAL GPIO state.";
      case pulse_driver_error::hal_init:
        return "Failed to initialize HAL interface.";
      default:
        return "ERROR! Hacking too much time!";
    };
}

const char *
pulse_driver_category_impl::name (
    void
) const noexcept {
    return "pulse_driver_error";
}

std::error_code
nes::rob::make_error_code (
    pulse_driver_error e
) {
    return {static_cast<int>(e), pulse_driver_category()};
}

std::error_condition
nes::rob::make_error_condition (
    pulse_driver_error e
) {
    return {static_cast<int>(e), pulse_driver_category()};
}
