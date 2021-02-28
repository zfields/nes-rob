#include "signal_generator_error.hpp"

namespace nes { namespace rob {

class signal_generator_error_category : public std::error_category
{
  public:
    virtual std::error_condition default_error_condition (int ev) const noexcept override;
    virtual std::string message (int ev) const override;
    virtual const char *name (void) const noexcept override;
};

}} // namespace nes::rob

using namespace nes::rob;

namespace {

const std::error_category &
signal_generator_error_category_instance (
    void
) {
    static signal_generator_error_category instance;
    return instance;
}

}

std::error_condition
signal_generator_error_category::default_error_condition (
    int ev
) const noexcept {
    // Define equivalence relationships with std::errc
    switch (static_cast<signal_generator_error>(ev)) {
      default:
        return std::error_condition(ev, *this);
    };
}

std::string
signal_generator_error_category::message (
    int ev
) const {
    switch (static_cast<signal_generator_error>(ev)) {
      case signal_generator_error::success:
        return "Success.";
      case signal_generator_error::driver_error:
        return "Pulse driver error occurred.";
      case signal_generator_error::driver_init:
        return "Failed to initialize pulse driver.";
      default:
        return "ERROR! Hacking too much time!";
    };
}

const char *
signal_generator_error_category::name (
    void
) const noexcept {
    return "signal_generator_error";
}

std::error_code
nes::rob::make_error_code (
    signal_generator_error e
) {
    return {static_cast<int>(e), signal_generator_error_category_instance()};
}

std::error_condition
nes::rob::make_error_condition (
    signal_generator_error e
) {
    return {static_cast<int>(e), signal_generator_error_category_instance()};
}
