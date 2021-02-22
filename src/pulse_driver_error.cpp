#include "pulse_driver_error.hpp"

class pulse_driver_category_impl : public std::error_category
{
  public:
    virtual std::error_condition default_error_condition (int ev) const noexcept override;
    virtual std::string message(int ev) const override;
    virtual const char *name(void) const noexcept override;
};

std::error_condition
pulse_driver_category_impl::default_error_condition (
    int ev
) const noexcept {
    // Define equivalence relationships with std::errc
    switch (static_cast<nes::rob::pulse_driver_error>(ev)) {
      default:
        return std::error_condition(ev, *this);
    };
}

std::string
pulse_driver_category_impl::message (
    int ev
) const {
    switch (static_cast<nes::rob::pulse_driver_error>(ev)) {
      case nes::rob::pulse_driver_error::success:
        return "Success.";
      case nes::rob::pulse_driver_error::hal_clock:
        return "HAL clock failure.";
      case nes::rob::pulse_driver_error::hal_gpio_config:
        return "Failed to update HAL GPIO configuration.";
      case nes::rob::pulse_driver_error::hal_gpio_state:
        return "Failed to update HAL GPIO state.";
      case nes::rob::pulse_driver_error::hal_init:
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

const std::error_category &pulse_driver_category()
{
    static pulse_driver_category_impl instance;
    return instance;
}

std::error_code nes::rob::make_error_code(nes::rob::pulse_driver_error e)
{
    return {static_cast<int>(e), pulse_driver_category()};
}

std::error_condition nes::rob::make_error_condition(nes::rob::pulse_driver_error e)
{
    return {static_cast<int>(e), pulse_driver_category()};
}
