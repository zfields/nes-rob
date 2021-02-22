#include "signal_generator_error.hpp"

class signal_generator_category_impl : public std::error_category
{
  public:
    virtual std::error_condition default_error_condition (int ev) const noexcept override;
    virtual std::string message (int ev) const override;
    virtual const char *name (void) const noexcept override;
};

std::error_condition
signal_generator_category_impl::default_error_condition (
    int ev
) const noexcept {
    // Define equivalence relationships with std::errc
    switch (static_cast<nes::rob::signal_generator_error>(ev)) {
      default:
        return std::error_condition(ev, *this);
    };
}

std::string
signal_generator_category_impl::message (
    int ev
) const {
    switch (static_cast<nes::rob::signal_generator_error>(ev)) {
      case nes::rob::signal_generator_error::success:
        return "Success.";
      case nes::rob::signal_generator_error::driver_error:
        return "Signal driver error.";
      case nes::rob::signal_generator_error::driver_init:
        return "Failed to initialize signal driver.";
      default:
        return "ERROR! Hacking too much time!";
    };
}

const char *
signal_generator_category_impl::name (
    void
) const noexcept {
    return "signal_generator_error";
}

const std::error_category &signal_generator_category()
{
    static signal_generator_category_impl instance;
    return instance;
}

std::error_code nes::rob::make_error_code(nes::rob::signal_generator_error e)
{
    return {static_cast<int>(e), signal_generator_category()};
}

std::error_condition nes::rob::make_error_condition(nes::rob::signal_generator_error e)
{
    return {static_cast<int>(e), signal_generator_category()};
}
