#include "hal_error.hpp"

namespace nes { namespace rob {

class hal_category_impl : public std::error_category
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
hal_category (
    void
) {
    static hal_category_impl instance;
    return instance;
}

}

std::error_condition
hal_category_impl::default_error_condition (
    int ev
) const noexcept {
    // Define equivalence relationships with std::errc
    switch (static_cast<hal_error>(ev)) {
      default:
        return std::error_condition(ev, *this);
    };
}

const char *
hal_category_impl::name (
    void
) const noexcept {
    return "hal_error";
}

std::string
hal_category_impl::message (
    int ev
) const {
    switch (static_cast<hal_error>(ev)) {
      case hal_error::success:
        return "Success.";
      case hal_error::peripheral_gpio:
        return "GPIO peripheral failure.";
      case hal_error::sys_clock:
        return "System clock failure.";
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
    return {static_cast<int>(e), hal_category()};
}

std::error_condition
nes::rob::make_error_condition (
    hal_error e
) {
    return {static_cast<int>(e), hal_category()};
}
