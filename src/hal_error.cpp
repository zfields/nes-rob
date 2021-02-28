#include "hal_error.hpp"

namespace nes { namespace rob {

class hal_error_category : public std::error_category
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
hal_error_category_instance (
    void
) {
    static hal_error_category instance;
    return instance;
}

}

std::error_condition
hal_error_category::default_error_condition (
    int ev
) const noexcept {
    // Define equivalence relationships with std::errc
    switch (static_cast<hal_error>(ev)) {
      default:
        return std::error_condition(ev, *this);
    };
}

const char *
hal_error_category::name (
    void
) const noexcept {
    return "hal_error";
}

std::string
hal_error_category::message (
    int ev
) const {
    switch (static_cast<hal_error>(ev)) {
      case hal_error::success:
        return "Success.";
      case hal_error::peripheral_gpio:
        return "GPIO peripheral error.";
      case hal_error::sys_clock:
        return "System clock error.";
      case hal_error::sys_config:
        return "Failed to properly configure hardware.";
      default:
        return "ERROR! Hacking too much time!";
    };
}

std::error_code
nes::rob::make_error_code (
    hal_error e
) {
    return {static_cast<int>(e), hal_error_category_instance()};
}

std::error_condition
nes::rob::make_error_condition (
    hal_error e
) {
    return {static_cast<int>(e), hal_error_category_instance()};
}
